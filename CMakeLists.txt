cmake_minimum_required(VERSION 3.26)
project(osdev-libcppabi)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
        auxhelper.cc
        guard.cc
        new.h
        new.cpp
        vector.cpp
        cxxabi.h)

target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wall
        -ffreestanding
        -fno-exceptions
        -fno-rtti
        -fno-stack-protector
        -nostdlib
        -std=gnu++20
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "libstdc/include/arch/${ARCH}")

target_link_options(${PROJECT_NAME}
        PRIVATE
        -nostdlib
        -nodefaultlibs
)

add_subdirectory(libstdc)

target_link_libraries(${PROJECT_NAME} PRIVATE osdev-libstdc)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CXXRT_NO_EXCEPTIONS)