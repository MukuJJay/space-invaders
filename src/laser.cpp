#include "laser.hpp"
#include <raylib.h>


Color LASER = {243, 216, 63, 255};


void Laser::Draw(){
    if(active)
        DrawRectangle(position.x, position.y, 4, 15, LASER);
}

void Laser::Update(){
    position.y += speed;
    if (active){
        if(position.y > GetScreenHeight() || position.y < 0){
            active = false;
        }
    }
}

Rectangle Laser::GetRect(){
    return {position.x, position.y, 4, 15};
}
