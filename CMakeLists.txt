cmake_minimum_required(VERSION 3.0.0)
project(Chip8Emulator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE "Debug")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Find clang executable and set it as compiler
find_program(Clang_P clang++ REQUIRED True)
set(CMAKE_CXX_COMPILER ${Clang_P})

find_program(Clang_C clang REQUIRED True)
set(CMAKE_C_COMPILER ${Clang_C})

# Use clang lld instead of gnu ld
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")

# lots of warnings and all warnings as errors
add_compile_options(-Wall -Wextra -pedantic -Werror
    -Wno-unused-variable
)

message("Building in ${CMAKE_BUILD_TYPE}")

# Enable clang ubsan when in debug mode
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Adding ubsan!")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=integer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=nullability")
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=implicit-conversion")
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=array-bounds")
    add_compile_options(-fno-omit-frame-pointer)

    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)

    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O0")

else()
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(vendor)
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(tools)
