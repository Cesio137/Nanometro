cmake_minimum_required(VERSION 3.24)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Vulkan target include directories: ${Vulkan_INCLUDE_DIRS}")
    message(STATUS "Vulkan libraries directories: ${Vulkan_LIBRARIES}")
else()
    message(FATAL_ERROR "You have to install vulkan sdk from 'https://vulkan.lunarg.com/sdk/home'.")
endif()

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
    FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-2.28.5 #2.28.5
        GIT_PROGRESS TRUE
      )
  
    FetchContent_MakeAvailable(sdl2)
endif()

