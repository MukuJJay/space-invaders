#include "raylib.h"
#include "game.hpp"


int main()
{
    constexpr int screenWidth = 750;
    constexpr int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
