#include "raylib.h"
#include "game.hpp"
#include <string>

std::string FormatWithLeadingZeros(int score, int width);


int main()
{
    int offset = 50;

    constexpr int screenWidth = 750;
    constexpr int screenHeight = 700;

    InitWindow(screenWidth + offset, screenHeight + (2 * offset), "Space Invaders");
    SetTargetFPS(60);

    Game game;
    Texture2D livesSpaceShip = LoadTexture("assets/spaceship.png");

    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        game.Draw();
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, YELLOW);
        DrawLineEx({25, 730}, {775, 730}, 3, YELLOW);

        if(game.run){
            DrawTextEx(GetFontDefault(), "LEVEL 01", {590, 740}, 30, 5, YELLOW);
        }
        else{
            DrawTextEx(GetFontDefault(), "GAME OVER", {560, 740}, 30, 5, YELLOW);
        }

        float x = 60.0f;
        for (int i = 0; i < game.lives; i++){
            DrawTextureV(livesSpaceShip, {x, 745}, YELLOW);
            x += 50;
        }

        DrawTextEx(GetFontDefault(), "SCORE", {70, 15}, 20, 5, YELLOW);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(GetFontDefault(), scoreText.c_str(), {70, 40}, 20, 5, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

std::string FormatWithLeadingZeros(int score, int width){
    std::string scoreText = std::to_string(score);
    int leadingZeros = width - scoreText.length();
    return std::string(leadingZeros, '0') + scoreText;
}
