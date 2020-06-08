file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "${HookLength_SOURCE_DIR}/tests/*.h"
        "${HookLength_SOURCE_DIR}/tests/*.hpp"
        "${HookLength_SOURCE_DIR}/tests/*.cc"
        "${HookLength_SOURCE_DIR}/tests/*.cpp")

# This target runs all of the tests.
# Make sure CATCH_CONFIG_MAIN is only defined in one test file.
add_executable(test-hook-length ${SOURCE_LIST})

# We're using C++17 in the test
target_compile_features(test-hook-length PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(test-hook-length PRIVATE hook-length catch2 nlohmann_json)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME test-hook-length COMMAND test-hook-length) # Command can be a target

# Add folders
set_target_properties(test-hook-length PROPERTIES FOLDER cs126)

# Cross-platform compiler lints
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(test-hook-length PRIVATE
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
    target_compile_options(test-hook-length PRIVATE
            /W3)
endif ()


add_custom_command(
        TARGET test-hook-length
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -DSRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" -DDEST_DIR="${CMAKE_CURRENT_BINARY_DIR}/data" -P "${CMAKE_SOURCE_DIR}/cmake/configure_files.cmake"
)

