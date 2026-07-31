cmake_minimum_required(VERSION 3.16)
project(Leszek CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Włącz optymalizacje w trybie Release (ważne przy mnożeniu macierzy - bez tego będzie WOLNO)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
 
# Trochę warningów, żeby łapać głupie błędy
# (MSVC i GCC/Clang mają różną składnię flag, więc trzeba to rozróżnić)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

file(GLOB_RECURSE LESZEK_SRC src/*)

add_executable(Leszek ${LESZEK_SRC})

target_include_directories(Leszek PRIVATE src)

# --- SDL3 (na później - narazie NIE włączone) ---
# Gdy przyjdzie czas na rysowanie cyfr myszką, odkomentuj poniższe
# i doinstaluj SDL3 (np. przez vcpkg albo find_package jeśli masz zainstalowane systemowo):
#
# find_package(SDL3 REQUIRED CONFIG)
# target_link_libraries(Leszek PRIVATE SDL3::SDL3)
