cmake_minimum_required(VERSION 3.23)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(vendor/SDL2)
add_subdirectory(vendor/GLAD)


add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC vendor/SDL2/include
        PUBLIC vendor/GLAD/include
        )

find_package(OpenGL REQUIRED)
if (WIN32)


    target_link_directories(${PROJECT_NAME} PUBLIC
            cmake-build-debug-clang14/vendor/SDL2
            )
    target_link_libraries(${PROJECT_NAME} SDL2-staticd winmm setupapi imm32 version glad  OpenGL::GL )
else ()

    target_link_directories(${PROJECT_NAME} PUBLIC
            cmake-build-debug-wsl/vendor/SDL2
            )
    target_link_libraries(${PROJECT_NAME} SDL2d dl pthread OpenGL::GL glad)
endif ()
