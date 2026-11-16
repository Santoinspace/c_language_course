#ifndef COURSE_SCORE_H
#define COURSE_SCORE_H

/* 最高分存取模块的接口。
 * 这是一个多文件编程示例：函数声明放在 .h，实现放在 src/score.c。
 * 其他 .c 文件只要 #include "score.h" 就能调用这两个函数。
 */

/* 读取文件中的非负整数。文件不存在或内容非法时返回 0。 */
int LoadBestScore(const char *file_path);

/* 保存最高分。成功返回 1，失败返回 0。 */
int SaveBestScore(const char *file_path, int best_score);

/* TODO(STUDENT): 为你自己的业务模块新增头文件（如 include/game.h），
 * 头文件中只放函数声明、结构体类型和宏，实现写到对应的 .c 文件（放在 src/ 下）。 */

#endif
