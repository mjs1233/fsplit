cmake_minimum_required(VERSION 4.1)
project(fsplit C)

set(CMAKE_C_STANDARD 11)

add_executable(fsplit)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            /WX
            /Za
            /Zc:preprocessor
    )
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall
            -Wextra
            -Werror
            -pedantic
    )
endif()

add_subdirectory(source)
