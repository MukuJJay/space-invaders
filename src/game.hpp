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
        bool run;
        int lives;
        int score;

    private:
        void MysteryshipManage();
        void CheckCollisions();
        void DeleteInactiveLaser();
        void CreateObstacles();
        void CreateAliens();
        void MoveAliens();
        void MoveAliensDown(int distance);
        void AlienShootLaser();
        void Init();
        void Reset();
        void GameOver();
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        int alienDirection;
        std::vector<Laser> alienLasers;
        constexpr static double alienLaserShootInterval = 0.35f;
        double lastAlienLaserShotAt;
        MysteryShip mysteryship;
        double mysteryShipSpawnInterval;
        double lastmysteryshipSpawnedAt;
};
