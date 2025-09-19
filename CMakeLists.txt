cmake_minimum_required(VERSION 3.31)
project(WallPaper)

set(CMAKE_CXX_STANDARD 20)

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/SDL EXCLUDE_FROM_ALL)

aux_source_directory(src SOURCE)


add_executable(WallPaper
        src/KeyboardEvent/MinHookDLL.h
        src/KeyboardEvent/EventManager.cpp
        src/render/IRender.cpp
        src/render/IRender.h
        src/KeyboardEvent/EventManager.h
        src/KeyboardEvent/Hook.cpp
        src/main.cpp
        src/KeyboardEvent/Hook.h
        ${SOURCE}
        src/render/Render.cpp
        src/render/Render.h
        src/KeyboardEvent/EventDef.h
)

target_include_directories(WallPaper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/MinHook/include
)
target_include_directories(WallPaper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL/include/SDL3)
target_link_libraries(WallPaper PRIVATE SDL3::SDL3)