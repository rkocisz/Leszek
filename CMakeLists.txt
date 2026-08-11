cmake_minimum_required(VERSION 3.24)
project(Leszek CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# Flagi kompilatora (warningi)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

if(POLICY CMP0194)
    cmake_policy(SET CMP0194 NEW)
endif()

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)


file(GLOB_RECURSE LESZEK_SRC src/*)

add_executable(Leszek ${LESZEK_SRC})

target_include_directories(Leszek PRIVATE src)


target_link_libraries(Leszek PRIVATE 
    SDL3::SDL3
)