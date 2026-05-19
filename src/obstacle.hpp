#pragma once
#include "block.hpp"
#include <raylib.h>
#include <vector>


class Obstacle{
    public:
        Obstacle(Vector2 position);
        void Draw();
        static std::vector<std::vector<int>> grid;
        std::vector<Block> blocks;

    private:
        Vector2 position;
};
