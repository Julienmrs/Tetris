cmake_minimum_required(VERSION 3.20)

project(Tetris3D LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_executable(Tetris3d
    main.cpp
    shader.h shader.cpp
    cube.h cube.cpp
    camera.h camera.cpp
    plateau.h plateau.cpp
    tetromino.h tetromino.cpp
    game.h game.cpp


)

include_directories(
    ${CMAKE_SOURCE_DIR}/biblio/glfw/include
    ${CMAKE_SOURCE_DIR}/biblio/glm
    ${CMAKE_SOURCE_DIR}/biblio/glew/include

)

target_link_libraries(Tetris3d
    glfw
    GLEW
    OpenGL::GL

)
