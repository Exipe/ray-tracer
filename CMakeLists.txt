cmake_minimum_required(VERSION 3.19)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_PATH "C:/SDL2-2.0.16/x86_64-w64-mingw32")
set(SDL2_DIR "C:/SDL2-2.0.16/x86_64-w64-mingw32/lib/cmake/SDL2")

find_package(SDL2 REQUIRED)

add_executable(ray_tracer main.cpp Scene.cpp Scene.h Camera.cpp Camera.h Light.cpp Light.h Sphere.cpp Sphere.h)
target_include_directories(ray_tracer PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(ray_tracer ${SDL2_LIBRARIES})