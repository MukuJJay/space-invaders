#pragma once
#include "alien.hpp"
#include "laser.hpp"
#include "mysteryship.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"
#include <raylib.h>
#include <vector>


class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();

    private:
        Spaceship spaceship;
        void DeleteInactiveLaser();
        std::vector<Obstacle> obstacles;
        void CreateObstacles();
        std::vector<Alien> aliens;
        void CreateAliens();
        int alienDirection;
        void MoveAliens();
        void MoveAliensDown(int distance);
        void AlienShootLaser();
        std::vector<Laser> alienLasers;
        constexpr static double alienLaserShootInterval = 0.35f;
        double lastAlienLaserShotAt;
        MysteryShip mysteryship;
        double mysteryShipSpawnInterval;
        double lastmysteryshipSpawnedAt;
        void MysteryshipManage();
};
