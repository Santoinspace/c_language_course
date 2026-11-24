#include "score.h"
#include <stdio.h>

/* 示例模块：把最高分保存到文本文件。
 * 你可以参考这里的 fopen/fscanf/fprintf/fclose 写法，实现自己的数据持久化。 */

/* 读取最高分。
 * 返回值：文件不存在、打开失败、内容不是整数或为负数时统一返回 0。
 * 这样调用方不需要区分“第一次运行”和“数据损坏”。 */
int LoadBestScore(const char *file_path)
{
    FILE *fp; // C 标准库中用于描述文件流的类型
    int value = 0;
    if (file_path == NULL) return 0; // 检查文件路径

    fp = fopen(file_path, "r"); // read
    if (fp == NULL) return 0;
    if (fscanf(fp, "%d", &value) != 1 || value < 0) value = 0;
    fclose(fp);
    return value;
}

/* 保存最高分。
 * 返回值：1 表示成功，0 表示失败（路径为空、分数为负、打开/写入/关闭失败）。
 * 调用方可以选择忽略失败（示例程序就是这么做的），但正式项目应处理错误。 */
int SaveBestScore(const char *file_path, int best_score)
{
    FILE *fp;
    int ok;
    if (file_path == NULL || best_score < 0) return 0;

    fp = fopen(file_path, "w"); // write
    if (fp == NULL) return 0;
    ok = (fprintf(fp, "%d\n", best_score) > 0);
    if (fclose(fp) != 0) ok = 0;
    return ok;
}
