# ============================================================================
# C 语言程序设计基础 · 期末项目统一工程模板
# 构建系统：CMake + MinGW Makefiles（GCC / mingw32-make）
# 说明：学生通常只需要修改下面标有 TODO 的地方；其余构建配置保持原样。
# ============================================================================
cmake_minimum_required(VERSION 3.24)
project(CFinalProject LANGUAGES C)

# 课程统一使用 C99；C_STANDARD_REQUIRED 防止编译器回退到旧标准。
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
# 生成 compile_commands.json，供 VS Code 的 C/C++ 扩展做代码补全。
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# raylib 以静态库方式链接：最终只生成 .exe，不需要额外携带 raylib.dll。
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Build raylib games" FORCE)

# raylib 来源二选一，下面的 if 会自动判断：
#   A. 离线：把官方 raylib 6.0 源码放到 third_party/raylib/
#      （raylib 的 CMakeLists.txt 必须直接位于该目录）。
#   B. 联网：首次配置时由 FetchContent 下载固定标签 6.0 到 build/_deps/。
# 注意：GIT_TAG 固定为课程版本 6.0，不要改成其他版本。
if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/raylib/CMakeLists.txt")
    message(STATUS "raylib source: third_party/raylib (offline)")
    add_subdirectory(third_party/raylib "${CMAKE_BINARY_DIR}/raylib-local-build")
else()
    include(FetchContent)
    # 下载成功一次后不再检查远端更新，避免每次配置都访问网络。
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

# 可执行程序 c_final_project 的源文件列表。
# 注意：tools\run.cmd 和课程文档都按 c_final_project.exe 查找产物，不要随意改目标名。
# TODO(STUDENT): 每新增一个业务 .c 文件，都必须加到下面的列表里；否则该文件
#               不会参与编译，常见现象是 undefined reference。头文件 .h 不用加。
add_executable(c_final_project
    src/main.c
    src/score.c
    # TODO(STUDENT): 在这里添加你自己的源文件，例如：
    # src/game.c
    # src/storage.c
)

# 把 include/ 加入头文件搜索路径，main.c 才能写 #include "score.h"。
target_include_directories(c_final_project PRIVATE "${CMAKE_SOURCE_DIR}/include")
# raylib 静态库由上面的 FetchContent / add_subdirectory 提供。
target_link_libraries(c_final_project PRIVATE raylib)

# 打开常见警告，尽早发现未初始化变量、类型不匹配等问题。
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(c_final_project PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ----------------------------------------------------------------------------
# 纯 C 标准库测试：不依赖 raylib，也不会打开窗口。
# 运行方式：ctest --test-dir build --output-on-failure
# ----------------------------------------------------------------------------
include(CTest)
if(BUILD_TESTING)
    add_executable(score_tests tests/test_score.c src/score.c)
    target_include_directories(score_tests PRIVATE "${CMAKE_SOURCE_DIR}/include")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        target_compile_options(score_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME score_storage COMMAND score_tests)

    # TODO(STUDENT): 为自己的核心数据处理模块增加测试程序，并像上面一样用
    #               add_test 注册；测试应能在不打开窗口的情况下运行。
endif()
