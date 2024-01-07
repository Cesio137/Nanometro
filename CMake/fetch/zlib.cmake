FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
    FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG        v1.3 #1.3
        GIT_PROGRESS TRUE
      )
  
    FetchContent_MakeAvailable(zlib)
endif()