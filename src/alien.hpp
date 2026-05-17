#pragma once
#include <raylib.h>


class Alien{
    public:
        Alien(int type, Vector2 position);
        void Draw();
        void Update(int direction);
        static void UnloadImages();
        Vector2 position;
        static Texture2D alienImages[3];
        int type;
        Rectangle GetRect();

    private:
};
