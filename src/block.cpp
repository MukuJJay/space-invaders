#include "block.hpp"
#include <raylib.h>


Color OBSTACLE = {243, 216, 63, 255};

void Block::Draw(){
    DrawRectangle(position.x, position.y, 3, 3, OBSTACLE);
}

Rectangle Block::GetRect(){
    return {position.x, position.y, 3, 3};
}
