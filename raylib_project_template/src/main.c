#include "raylib.h"
#include "score.h"

/* Starter demonstration: move the blue square and collect yellow coins.
 * The example intentionally uses only introductory C concepts. */

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500
#define PLAYER_SIZE 34
#define COIN_SIZE 22
#define DATA_PATH "data/best_score.txt"

typedef struct GameState {
    Rectangle player;
    Rectangle coin;
    int score;
    int best_score;
} GameState;

static void PlaceCoin(GameState *game)
{
    game->coin.x = (float)GetRandomValue(35, SCREEN_WIDTH - COIN_SIZE - 35);
    game->coin.y = (float)GetRandomValue(100, SCREEN_HEIGHT - COIN_SIZE - 35);
    game->coin.width = (float)COIN_SIZE;
    game->coin.height = (float)COIN_SIZE;
}

static void ResetGame(GameState *game)
{
    game->player = (Rectangle){60.0f, 150.0f, PLAYER_SIZE, PLAYER_SIZE};
    game->score = 0;
    PlaceCoin(game);
}

static void UpdateGame(GameState *game)
{
    const float speed = 280.0f * GetFrameTime();

    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) game->player.x -= speed;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) game->player.x += speed;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) game->player.y -= speed;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) game->player.y += speed;

    if (game->player.x < 0) game->player.x = 0;
    if (game->player.x > SCREEN_WIDTH - PLAYER_SIZE)
        game->player.x = SCREEN_WIDTH - PLAYER_SIZE;
    if (game->player.y < 80) game->player.y = 80;
    if (game->player.y > SCREEN_HEIGHT - PLAYER_SIZE)
        game->player.y = SCREEN_HEIGHT - PLAYER_SIZE;

    if (IsKeyPressed(KEY_R)) ResetGame(game);

    if (CheckCollisionRecs(game->player, game->coin)) {
        game->score++;
        if (game->score > game->best_score) {
            game->best_score = game->score;
            /* Folder 'data' exists in the template; failed saves are harmless. */
            (void)SaveBestScore(DATA_PATH, game->best_score);
        }
        PlaceCoin(game);
    }
}

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

int main(void)
{
    GameState game = {0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Programming Final Project");
    SetTargetFPS(60);
    game.best_score = LoadBestScore(DATA_PATH);
    ResetGame(&game);

    while (!WindowShouldClose()) {
        UpdateGame(&game);
        DrawGame(&game);
    }

    CloseWindow();
    return 0;
}
