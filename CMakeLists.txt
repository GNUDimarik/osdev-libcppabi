cmake_minimum_required(VERSION 3.26)
project(osdev-libcppabi)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
        new.h
        new.cpp
        vector.cpp
        cxxabi.h
        tests/test.cc
        guard.cpp
        stubs.cpp)

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

target_include_directories(${PROJECT_NAME} PUBLIC
        "libstdc/include/arch/${ARCH}"
        "libstdc/include/")

target_link_options(${PROJECT_NAME}
        PRIVATE
        -nostdlib
        -nodefaultlibs
)

add_subdirectory(libstdc)

target_link_libraries(${PROJECT_NAME} PUBLIC osdev-libstdc)

if (DEFINED ENABLE_TEST)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LIBCPPABI_TEST)
endif ()

if (DEFINED ENABLE_TEST)
    add_executable(test_vector1.pass
            tests/test_vector1.pass.cpp)

    target_link_libraries(test_vector1.pass PRIVATE
            osdev-libcppabi
            osdev-libstdc)
    target_compile_definitions(test_vector1.pass PUBLIC TEST_HAS_NO_EXCEPTIONS)
endif ()

if (DEFINED ENABLE_TEST)
    add_executable(licxxrt_test
            tests/test_guard.cc
            tests/test.cc
            guard.cpp)

    target_link_libraries(licxxrt_test PRIVATE
            osdev-libcppabi
            osdev-libstdc)
    target_include_directories(licxxrt_test PRIVATE
            "libstdc/include/arch/${ARCH}"
            "libstdc/include/")
    target_compile_definitions(licxxrt_test PUBLIC _CXXRT_NO_EXCEPTIONS)
endif ()

if (DEFINED ENABLE_TEST)
    add_executable(habr_test
            tests/habr_test.cpp
            tests/test.cc
            guard.cpp)

    target_link_libraries(habr_test PRIVATE
            osdev-libcppabi
            osdev-libstdc)
    target_include_directories(habr_test PRIVATE
            "libstdc/include/arch/${ARCH}"
            "libstdc/include/")
    target_compile_definitions(habr_test PUBLIC _CXXRT_NO_EXCEPTIONS HABR_TEST)
endif ()