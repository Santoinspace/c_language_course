/* TODO(STUDENT): 本文件是测试示例。请为自己的核心数据处理模块补充测试：
 *   1. 新建 tests/test_<模块>.c；
 *   2. 在 CMakeLists.txt 的 BUILD_TESTING 段增加测试可执行文件；
 *   3. 用 add_test 注册，确保 ctest 能运行到。
 * 测试不依赖 raylib，也不应打开窗口。 */
#include "score.h"
#include <stdio.h>

/* 断言辅助函数：条件不成立时打印 FAIL 并返回 0。
 * main 用 ok &= ... 累积结果；最后有任何失败就返回非 0，CTest 会判为失败。 */
static int Check(int condition, const char *description)
{
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", description);
        return 0;
    }
    printf("PASS: %s\n", description);
    return 1;
}

int main(void)
{
    /* 使用构建目录中的临时文件，测试结束时删除，避免污染 data/。 */
    const char *path = "test_best_score_tmp.txt";
    int ok = 1;
    FILE *file;
    (void)remove(path);

    /* 文件不存在时应返回 0，而不是崩溃。 */
    ok &= Check(LoadBestScore(path) == 0, "missing file is 0");
    /* 正常保存后应能读回同一个值。 */
    ok &= Check(SaveBestScore(path, 7) == 1, "save score");
    ok &= Check(LoadBestScore(path) == 7, "load score");
    /* 负数不是合法最高分：保存应失败，且不能覆盖原值。 */
    ok &= Check(SaveBestScore(path, -1) == 0, "reject negative score");
    ok &= Check(LoadBestScore(path) == 7, "rejected save keeps original value");

    /* 文件内容不是整数时，应按非法数据处理并返回 0。 */
    file = fopen(path, "w");
    if (file != NULL) {
        fputs("invalid\n", file);
        fclose(file);
        ok &= Check(LoadBestScore(path) == 0, "invalid file is 0");
    } else {
        ok &= Check(0, "create invalid file");
    }

    (void)remove(path);
    return ok ? 0 : 1;
}
