/* TODO(STUDENT): 这是可以直接运行的示例程序，不是你的期末项目。
 * 期末项目请从零重写本文件，只保留 raylib 的主循环骨架：
 *   InitWindow → while (!WindowShouldClose()) → CloseWindow
 *
 * 重写时至少要做到：
 *   1. 换成你自己的游戏/应用逻辑，而不是“移动方块吃金币”；
 *   2. 用结构体保存核心数据，用数组保存多条数据或状态；
 *   3. 把业务逻辑拆到至少 2 个自己的 .c/.h 模块，并登记到 CMakeLists.txt；
 *   4. 需要保存数据时，参考 src/score.c 的文件读写写法。
 *
 * 具体要求见 docs/ASSIGNMENT.md，操作步骤见 docs/STUDENT_GUIDE.md。
 * ========================================================================== */
#include "raylib.h"
#include "score.h"

/* 示例程序：移动蓝色方块收集黄色金币。
 * 这里只使用入门阶段的 C 概念，方便你在修改前读懂整个程序。 */

/* 窗口与游戏对象的尺寸（像素）。 */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500
#define PLAYER_SIZE 34
#define COIN_SIZE 22

/* 最高分文件路径。相对路径以“运行程序时的当前目录”为准，
 * 因此必须在项目根目录运行，data/ 才能被找到。 */
#define DATA_PATH "data/best_score.txt"

/* 游戏的完整状态。把所有需要跨帧保存的数据放在一个结构体里，
 * 函数通过指针接收它，就能直接修改原对象。 */
typedef struct GameState {
    Rectangle player;   /* 玩家方块的位置和大小 */
    Rectangle coin;     /* 金币的位置和大小 */
    int score;          /* 本局得分 */
    int best_score;     /* 历史最高分，从文件读取 */
} GameState;

/* 在窗口内随机放置金币，并留出边距，避免金币贴着边缘。 */
static void PlaceCoin(GameState *game)
{
    game->coin.x = (float)GetRandomValue(35, SCREEN_WIDTH - COIN_SIZE - 35);
    game->coin.y = (float)GetRandomValue(100, SCREEN_HEIGHT - COIN_SIZE - 35);
    game->coin.width = (float)COIN_SIZE;
    game->coin.height = (float)COIN_SIZE;
}

/* 重置一局：玩家回到起点，本局分数归零，并重新放置金币。
 * 注意参数是指针，game->score 修改的是调用者传进来的结构体。 */
static void ResetGame(GameState *game)
{
    game->player = (Rectangle){60.0f, 150.0f, PLAYER_SIZE, PLAYER_SIZE};
    game->score = 0;
    PlaceCoin(game);
}

/* 每帧调用一次：处理键盘输入、边界限制、重开和碰撞计分。 */
static void UpdateGame(GameState *game)
{
    /* GetFrameTime() 返回上一帧耗时，乘上速度可让移动速度不受帧率影响。 */
    const float speed = 280.0f * GetFrameTime();

    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) game->player.x -= speed;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) game->player.x += speed;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) game->player.y -= speed;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) game->player.y += speed;

    /* 把玩家限制在窗口内；顶部 80 像素留给标题栏文字。 */
    if (game->player.x < 0) game->player.x = 0;
    if (game->player.x > SCREEN_WIDTH - PLAYER_SIZE)
        game->player.x = SCREEN_WIDTH - PLAYER_SIZE;
    if (game->player.y < 80) game->player.y = 80;
    if (game->player.y > SCREEN_HEIGHT - PLAYER_SIZE)
        game->player.y = SCREEN_HEIGHT - PLAYER_SIZE;

    /* 按 R 随时重开；IsKeyPressed 只在按下的那一帧返回 true。 */
    if (IsKeyPressed(KEY_R)) ResetGame(game);

    /* 玩家与金币的矩形发生重叠时计分，并立即放下一个金币。 */
    if (CheckCollisionRecs(game->player, game->coin)) {
        game->score++;
        if (game->score > game->best_score) {
            game->best_score = game->score;
            /* 保存失败不影响游戏继续；data/ 目录必须存在。 */
            (void)SaveBestScore(DATA_PATH, game->best_score);
        }
        PlaceCoin(game);
    }
}

/* 每帧调用一次：先 BeginDrawing，再画所有内容，最后 EndDrawing。
 * 所有 Draw* 调用都必须放在 BeginDrawing 和 EndDrawing 之间。 */
static void DrawGame(const GameState *game)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, SCREEN_WIDTH, 70, (Color){235, 241, 250, 255});
    DrawText("C99 + raylib | Collect the coins", 20, 12, 24, DARKBLUE);
    DrawText(TextFormat("Score: %d    Best: %d", game->score, game->best_score),
             20, 43, 19, DARKGRAY);
    DrawRectangleRec(game->player, BLUE);
    DrawRectangleRec(game->coin, GOLD);
    DrawText("Move: arrows or WASD | R: restart | ESC: quit",
             18, SCREEN_HEIGHT - 25, 17, GRAY);
    EndDrawing();
}

/* 程序入口：初始化窗口 → 读最高分 → 主循环 → 关闭窗口。 */
int main(void)
{
    GameState game = {0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Programming Final Project");
    SetTargetFPS(60);
    game.best_score = LoadBestScore(DATA_PATH);
    ResetGame(&game);

    /* WindowShouldClose 在按 Esc 或点窗口关闭按钮后返回 true。 */
    while (!WindowShouldClose()) {
        UpdateGame(&game);
        DrawGame(&game);
    }

    CloseWindow();
    return 0;
}
