#include "UDPClient.h"

namespace Nanometro {
    void UDPClient::send(const std::string &message)
    {
        if (!pool || !isConnected())
            return;
            
        asio::post(*pool, [this, message]() {
            std::vector<char> buffer(message.begin(), message.end());
            if (buffer.back() != '\0')
                buffer.push_back('\0');
            package_buffer(buffer);
        });
    }

    void UDPClient::sendRaw(const std::vector<char> &buffer)
    {
        if (!pool || !isConnected())
            return;

        asio::post(*pool, [this, buffer]() {
            package_buffer(buffer);
        });
    }

    void UDPClient::connect()
    {
        if (!pool)
			return;

		asio::post(*pool, [this]() {
		    runContextThread();
		});
    }

    void UDPClient::runContextThread()
    {
        mutexIO.lock();
        udp.context.restart();
        udp.resolver.async_resolve(asio::ip::udp::v4(), host, service,
            std::bind(&UDPClient::resolve, this, asio::placeholders::error, asio::placeholders::results)
        );
        udp.context.run();
        mutexIO.unlock();
    }

    void UDPClient::resolve(std::error_code error, asio::ip::udp::resolver::results_type results)
    {
        if (error) {
            if (onConnectionError)
                onConnectionError(error.value(), error.message());
            return;
        }
        udp.endpoints = *results;
        udp.socket.async_connect(udp.endpoints,
            std::bind(&UDPClient::conn, this, asio::placeholders::error)
        );
    }

    void UDPClient::conn(std::error_code error)
    {
        if (error) {
            if (onConnectionError)
                onConnectionError(error.value(), error.message());
            return;
        }
        udp.socket.async_receive_from(asio::buffer(rbuffer.message, 1024), udp.endpoints,
            std::bind(&UDPClient::receive_from, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
        );
        if (onConnected)
            onConnected();
    }

    void UDPClient::package_buffer(const std::vector<char> &buffer)
    {
        mutexBuffer.lock();
        if (buffer.size() <= 1024) {
            udp.socket.async_send_to(asio::buffer(buffer.data(), buffer.size()), udp.endpoints,
                std::bind(&UDPClient::send_to, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            );
            mutexBuffer.unlock();
            return;
        }
        size_t buffer_offset = 0;
        const size_t max_size = 1023;
        while (buffer_offset < buffer.size()) {
            size_t package_size = std::min(max_size, buffer.size() - buffer_offset);
            std::vector<char> sbuffer = std::vector<char>(buffer.begin() + buffer_offset, buffer.begin() + buffer_offset + package_size);
            if (sbuffer.back() != '\0')
                sbuffer.push_back('\0');
            udp.socket.async_send_to(asio::buffer(sbuffer.data(), sbuffer.size()), udp.endpoints,
                std::bind(&UDPClient::send_to, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            );
            buffer_offset += package_size;
        }
        mutexBuffer.unlock();
    }

    void UDPClient::send_to(std::error_code error, std::size_t bytes_sent)
    {
        if (error) {
            if (onMessageSentError)
                onMessageSentError(error.value(), error.message());
            return;
        }
        if (onMessageSent)
            onMessageSent(bytes_sent);
    }

    void UDPClient::receive_from(std::error_code error, std::size_t bytes_recvd)
    {
        if (error) {
            if (onMessageReceivedError)
                onMessageReceivedError(error.value(), error.message());
                
            return;
        }
        rbuffer.size = bytes_recvd;
        if (onMessageReceived)
            onMessageReceived(bytes_recvd, rbuffer);
        udp.socket.async_receive_from(asio::buffer(rbuffer.message, 1024), udp.endpoints,
            std::bind(&UDPClient::receive_from, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
        ); 
    }
} // Nanometro