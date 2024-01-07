cmake_minimum_required(VERSION 3.24)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_GetProperties(sdl_image)
if(NOT sdl_image_POPULATED)
    FetchContent_Declare(
        sdl_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG        release-2.8.2 #2.8.2
        GIT_PROGRESS TRUE
      )
  
    FetchContent_MakeAvailable(sdl_image)
endif()