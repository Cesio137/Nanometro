cmake_minimum_required(VERSION 3.28)

option(TARGET_SYSTEM "Target System" "")

# BUILD SDL2
execute_process(COMMAND cmake --preset ${TARGET_SYSTEM} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/SDL2)
execute_process(COMMAND cmake --build build/${TARGET_SYSTEM} --target install --config "Release"  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/SDL2)
#execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory build WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/SDL2)

# BUILD ZLIB
execute_process(COMMAND cmake --preset ${TARGET_SYSTEM} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/zlib)
execute_process(COMMAND cmake --build build/${TARGET_SYSTEM} --target install --config "Release"  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/zlib)
#execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory build WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/zlib)

# BUILD SDL Image
execute_process(COMMAND cmake --preset ${TARGET_SYSTEM} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/SDL_image)
execute_process(COMMAND cmake --build build/${TARGET_SYSTEM} --target install --config "Release"  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/SDL_image)
#execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory build WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/SDL_image)

# BUILD Jolt
execute_process(COMMAND cmake --preset ${TARGET_SYSTEM} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/JoltPhysics)
execute_process(COMMAND cmake --build build/${TARGET_SYSTEM} --target install --config "Release"  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/JoltPhysics)
#execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory build WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/JoltPhysics)

# BUILD Box2D
execute_process(COMMAND cmake --preset ${TARGET_SYSTEM} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Box2D)
execute_process(COMMAND cmake --build build/${TARGET_SYSTEM} --target install --config "Release"  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Box2D)
#execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory build WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Box2D)