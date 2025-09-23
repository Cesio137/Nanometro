#include "framework/settings.h"
#include "opengl/render.h"
#include <algorithm>

using namespace runa::opengl;

namespace runa::framework {
    void user_settings_c::set_vsync(vsync_e value) {
        SDL_Window* win = render.get_backend().window_ptr;
        SDL_GL_SetSwapInterval((int)value);
    }

    vsync_e user_settings_c::get_vsync() {
        int value = 0;
        SDL_GL_GetSwapInterval(&value);
        return (vsync_e)value;
    }

    void user_settings_c::set_framerate_limit(uint16_t value) {
        if (value == 0) {
            framerate_limit = value;
            return;
        }

        framerate_limit = (uint16_t)std::clamp((int)value, 30, 512);
    }

    uint16_t user_settings_c::get_framerate_limit() {
        return framerate_limit;
    }
}


