#include "mysteryship.hpp"
#include <raylib.h>


MysteryShip::MysteryShip(){
    image = LoadTexture("assets/mystery.png");
    alive = false;
    position = {0.0f, 0.0f};
    speed = 0;
}

MysteryShip::~MysteryShip(){
    UnloadTexture(image);
}

void MysteryShip::Spawn(){
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if(side == 0){
        position.x = 25;
        speed = 3;
    }
    else if(side == 1){
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }

    alive = true;
}

void MysteryShip::Update(){
    if(alive){
        position.x += speed;

        if(position.x + image.width < 25 || position.x > GetScreenWidth() - 25){
            alive = false;
        }
    }
}

void MysteryShip::Draw(){
    if(alive){
        float leftLimit = 25.0f;
        float rightLimit = GetScreenWidth() - 25.0f;
        float shipLeft = position.x;
        float shipRight = position.x + image.width;
        float visibleLeft = shipLeft < leftLimit ? leftLimit : shipLeft;
        float visibleRight = shipRight > rightLimit ? rightLimit : shipRight;
        float visibleWidth = visibleRight - visibleLeft;

        if(visibleWidth > 0.0f){
            Rectangle source = {visibleLeft - shipLeft, 0.0f, visibleWidth, float(image.height)};
            Vector2 drawPosition = {visibleLeft, position.y};

            DrawTextureRec(image, source, drawPosition, WHITE);
        }
    }
}

Rectangle MysteryShip::GetRect(){
    if(alive){
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else{
        return {position.x, position.y, 0, 0};
    }
}
