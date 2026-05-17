#pragma once


#include <raylib.h>
class MysteryShip{
    public:
        MysteryShip();
        ~MysteryShip();
        void Draw();
        void Update();
        void Spawn();
        bool alive;
        Rectangle GetRect();

    private:
        Vector2 position;
        int speed;
        Texture2D image;
};
