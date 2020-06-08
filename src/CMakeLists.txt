# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS
        "${HookLength_SOURCE_DIR}/include/hook-length/*.h"
        "${HookLength_SOURCE_DIR}/include/hook-length/*.hpp")

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "${HookLength_SOURCE_DIR}/src/*.h"
        "${HookLength_SOURCE_DIR}/src/*.hpp"
        "${HookLength_SOURCE_DIR}/src/*.cc"
        "${HookLength_SOURCE_DIR}/src/*.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(hook-length ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(hook-length PUBLIC ../include)

target_link_libraries(hook-length PRIVATE nlohmann_json)

# All users of this library will need at least C++11
target_compile_features(hook-length PUBLIC cxx_std_11)

# Cross-platform compiler lints
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(hook-length PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(hook-length PRIVATE
            /W3)
endif ()

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
