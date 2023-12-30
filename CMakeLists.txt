cmake_minimum_required(VERSION 3.16.2)
project(hvi)

#set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Wall -Wextra -Wno-unused-parameter -Wcast-qual -Wfloat-equal -Woverloaded-virtual -pedantic -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
link_directories(libs)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(hvi src/Buffer.cpp src/CommandBar.cpp src/Cursor.cpp src/FontManager.cpp
               src/KeyHandler.cpp src/Main.cpp src/NormalModeHandler.cpp
               src/UserInput.cpp src/View.cpp src/Window.cpp src/WindowManager.cpp)

target_link_libraries(hvi Threads::Threads)
target_link_libraries(hvi HCLib)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(SFML_ROOT "~Library/Frameworks")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(hvi ${SFML_LIBRARIES})
endif ()

