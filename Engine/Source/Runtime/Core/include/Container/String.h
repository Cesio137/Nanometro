#pragma once

#include <string>

namespace Nanometro
{
    class String : public std::string
    {
    public:
        String();
        String(const std::string& str);
        String(const char* str);

        std::string toUpper();
        std::string toLower();
    };
}