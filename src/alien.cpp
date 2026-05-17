#include "alien.hpp"
#include <raylib.h>


Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position): type(type), position(position){
    if(alienImages[type - 1].id == 0){
        switch (type){
            case 1:
                alienImages[type - 1] = LoadTexture("assets/alien_1.png");
                break;
            case 2:
                alienImages[type - 1] = LoadTexture("assets/alien_2.png");
                break;
            case 3:
                alienImages[type - 1] = LoadTexture("assets/alien_3.png");
                break;
            default:
                alienImages[0] = LoadTexture("assets/alien_1.png");
        }
    }
}

void Alien::Draw(){
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

void Alien::Update(int direction){
    position.x += direction;
}

void Alien::UnloadImages(){
    for (int i = 0; i < 3; i++){
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::GetRect(){
    return{
        position.x,
        position.y,
        float(alienImages[type - 1].width),
        float(alienImages[type - 1].height),
    };
}
