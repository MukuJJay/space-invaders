#include "raylib.h"
#include "game.hpp"


int main()
{
    int offset = 50;

    constexpr int screenWidth = 750;
    constexpr int screenHeight = 700;

    InitWindow(screenWidth + offset, screenHeight + (2 * offset), "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        game.Draw();
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
