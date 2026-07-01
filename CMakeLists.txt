cmake_minimum_required(VERSION 3.26)
project(osdev-libcppabi)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
        auxhelper.cc
        guard.cc
        new.h
        new.cpp
        vector.cpp
        cxxabi.h
        tests/testing.h)

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
        "libstdc/include/arch/${ARCH}"
        "libstdc/include/")

target_link_options(${PROJECT_NAME}
        PRIVATE
        -nostdlib
        -nodefaultlibs
)

add_subdirectory(libstdc)

target_link_libraries(${PROJECT_NAME} PRIVATE osdev-libstdc)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CXXRT_NO_EXCEPTIONS)

if(DEFINED ENABLE_TEST)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LIBCPPABI_TEST)
endif ()

if(DEFINED ENABLE_TEST)
    add_executable(test_vector1.pass
            tests/test_vector1.pass.cpp
            tests/testing.h)

    target_link_libraries(test_vector1.pass PRIVATE
            osdev-libcppabi
            osdev-libstdc)
    target_compile_definitions(test_vector1.pass PUBLIC TEST_HAS_NO_EXCEPTIONS)
endif()