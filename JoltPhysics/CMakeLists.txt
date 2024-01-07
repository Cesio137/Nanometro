cmake_minimum_required(VERSION 3.24)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_GetProperties(joltphysics)
if(NOT joltphysics_POPULATED)
    FetchContent_Declare(
      joltphysics
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
        GIT_TAG        v4.0.2 #4.0.2
        GIT_PROGRESS TRUE
        SOURCE_SUBDIR  Build
      )
  
    FetchContent_MakeAvailable(joltphysics)
    if(WIN32)
      set_property(TARGET Jolt PROPERTY COMPILE_WARNING_AS_ERROR OFF)
      target_compile_options(Jolt PUBLIC /WX-)
    endif(WIN32)
endif()