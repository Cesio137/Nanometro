#pragma once
#include <cstdint>

namespace runa::framework {
    enum window_mode_e : uint8_t {
        fullscreen = 0,
        windowed = 1
    };

    enum vsync_e : int8_t {
        adaptative = -1,
        disable = 0,
        enable = 1
    };
    
    class user_settings_c {
    public:
        user_settings_c();
        ~user_settings_c();

        void set_vsync(vsync_e value);
        vsync_e get_vsync();
        
        void set_framerate_limit(uint16_t value);
        uint16_t get_framerate_limit();
    private:
        uint16_t framerate_limit = 0;
    };

    inline extern user_settings_c user_settings = user_settings_c();
}