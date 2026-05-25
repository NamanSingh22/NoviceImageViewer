cmake_minimum_required(VERSION 3.20)

project(IMAGEVIEWER LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/x64)

add_executable(IMAGEVIEWER main.cpp app.cpp)

target_link_libraries(IMAGEVIEWER PRIVATE
    SDL3
    User32.lib
    Gdi32.lib
    Shell32.lib
    Winmm.lib
)


add_custom_command(TARGET IMAGEVIEWER POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/bin/SDL3.dll"
    $<TARGET_FILE_DIR:IMAGEVIEWER>    
)