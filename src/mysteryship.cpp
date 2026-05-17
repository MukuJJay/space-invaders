#include "mysteryship.hpp"
#include <raylib.h>


MysteryShip::MysteryShip(){
    image = LoadTexture("assets/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip(){
    UnloadTexture(image);
}

void MysteryShip::Spawn(){
    position.y = 50;
    int side = GetRandomValue(0, 1);

    if(side == 0){
        position.x = 0;
        speed = 3;
    }
    else if(side == 1){
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }

    alive = true;
}

void MysteryShip::Update(){
    if(alive){
        position.x += speed;

        if(position.x + image.width < 0 || position.x > GetScreenWidth()){
            alive = false;
        }
    }
}

void MysteryShip::Draw(){
    DrawTextureV(image, position, WHITE);
}

Rectangle MysteryShip::GetRect(){
    if(alive){
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else{
        return {position.x, position.y, 0, 0};
    }
}
