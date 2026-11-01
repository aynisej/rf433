cmake_minimum_required(VERSION 3.28)

project(RF433 LANGUAGES CXX)

option(RF433_BUILD_APP "Build the Qt Widgets desktop shell" OFF)

add_library(rf433_core STATIC
    src/core/action_policy.cpp
    src/core/key_metadata.cpp
    src/core/name_policy.cpp
    src/core/session_state.cpp
)

target_include_directories(rf433_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(rf433_core PUBLIC cxx_std_20)
set_target_properties(rf433_core PROPERTIES CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(rf433_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(RF433_BUILD_APP)
    find_package(Qt6 6.12.0 EXACT REQUIRED COMPONENTS Widgets)

    add_executable(rf433_app
        src/app/main.cpp
        src/app/main_window.cpp
    )

    target_link_libraries(rf433_app
        PRIVATE
            rf433_core
            Qt6::Widgets
    )

    target_compile_features(rf433_app PRIVATE cxx_std_20)
    set_target_properties(rf433_app PROPERTIES CXX_EXTENSIONS OFF)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(rf433_app PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
