cmake_minimum_required(VERSION 3.24)
project(CFinalProject LANGUAGES C)

# Course requirements: C99, GCC / MinGW-w64, CMake and mingw32-make.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Always build raylib as a static library. This avoids a separate raylib DLL.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Build raylib games" FORCE)

# Option A (offline): teacher supplies the complete raylib 6.0 source tree.
# Option B (online): CMake downloads the fixed Git tag on first configure.
if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/raylib/CMakeLists.txt")
    message(STATUS "raylib source: third_party/raylib (offline)")
    add_subdirectory(third_party/raylib "${CMAKE_BINARY_DIR}/raylib-local-build")
else()
    include(FetchContent)
    # Do not check remote updates once raylib has been fetched successfully.
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Offline after initial download")
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    message(STATUS "raylib source: fixed Git tag 6.0 (initial download requires network)")
    FetchContent_MakeAvailable(raylib)
endif()

# TODO: Students must ADD each new .c file to this explicit list.
add_executable(c_final_project
    src/main.c
    src/score.c
)

target_include_directories(c_final_project PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(c_final_project PRIVATE raylib)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(c_final_project PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Pure C standard-library tests: no window and no raylib are needed.
include(CTest)
if(BUILD_TESTING)
    add_executable(score_tests tests/test_score.c src/score.c)
    target_include_directories(score_tests PRIVATE "${CMAKE_SOURCE_DIR}/include")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        target_compile_options(score_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME score_storage COMMAND score_tests)
endif()
