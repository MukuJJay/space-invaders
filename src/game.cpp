#include "game.hpp"
#include "alien.hpp"
#include "laser.hpp"
#include "obstacle.hpp"
#include <raylib.h>
#include <vector>


Game::Game(){
    alienDirection = 1;
    lastAlienLaserShotAt = 0.0;
    CreateAliens();

    CreateObstacles();

    lastmysteryshipSpawnedAt = 0.0;

    lives = 3;
    run = true;
}

Game::~Game(){
    Alien::UnloadImages();
}

void Game::Draw(){
    if(!run) return;

    spaceship.Draw();

    for (Laser& laser: spaceship.lasers){
        laser.Draw();
    }

    for (Obstacle& obstacle: obstacles){
        obstacle.Draw();
    }

    for (Alien& alien: aliens){
        alien.Draw();
    }

    for (Laser& laser: alienLasers){
        laser.Draw();
    }

    mysteryship.Draw();
}

void Game::Update(){
    if(!run) return;

    for (Laser& laser: spaceship.lasers){
        laser.Update();
    }

    MoveAliens();

    AlienShootLaser();

    for(Laser& laser: alienLasers){
        laser.Update();
    }

    DeleteInactiveLaser();

    MysteryshipManage();

    CheckCollisions();

    if(lives == 0){
        GameOver();
    }
}

void Game::HandleInput(){
    if (IsKeyDown(KEY_A)){
        spaceship.MoveLeft();
    }
    if (IsKeyDown(KEY_D)){
        spaceship.MoveRight();
    }
    if (IsKeyDown(KEY_SPACE)){
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLaser(){
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if(!it -> active){
            it = spaceship.lasers.erase(it);
        }
        else{
            ++it;
        }
    }

    for(auto it = alienLasers.begin(); it != alienLasers.end();){
        if(!it -> active){
            it = alienLasers.erase(it);
        }
        else{
            ++it;
        }
    }
}

void Game::CreateObstacles(){
    float obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - ( 4 * obstacleWidth )) / 5;

    for (int i = 0; i < 4; i++){
        float offsetX = ((i + 1) * gap) + ( i * obstacleWidth );
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 130)}));
    }
}

void Game::CreateAliens(){
    for (int row = 0; row < 5; row++){
        for (int col = 0; col < 11; col++){
            int alienType;

            if(row == 3 || row == 4){
                alienType = 1;
            }else if (row == 1 || row == 2) {
                alienType = 2;
            }else{
                alienType = 3;
            }

            float x = 75 + (55 * col);
            float y = 100 + (55 * row);

            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
}

void Game::MoveAliens(){
    for (Alien& alien : aliens){
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()){
            alienDirection = -1;
            MoveAliensDown(4);
        }
        else if(alien.position.x < 0){
            alienDirection = 1;
            MoveAliensDown(4);
        }

        alien.Update(alienDirection);
    }
}

void Game::MoveAliensDown(int distance){
    for (Alien& alien : aliens){
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser(){
    double t = GetTime() - lastAlienLaserShotAt;

    if(t <= alienLaserShootInterval || aliens.empty()) return;

    int randIndex = GetRandomValue(0, aliens.size() - 1);
    Alien& alien = aliens[randIndex];

    alienLasers.push_back(Laser({alien.position.x + (alien.alienImages[alien.type - 1].width / 2.0f), alien.position.y + alien.alienImages[alien.type - 1].height}, 6));

    lastAlienLaserShotAt = GetTime();
}


void Game::MysteryshipManage(){
    double currentTime = GetTime();
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    double timeDiff = currentTime - lastmysteryshipSpawnedAt;

    if(!mysteryship.alive && timeDiff >= mysteryShipSpawnInterval){
        mysteryship.Spawn();
        lastmysteryshipSpawnedAt = currentTime;
    }

    mysteryship.Update();
}

void Game::CheckCollisions(){
    //Spaceship laser collisions
    for(Laser& laser: spaceship.lasers){
        //Spaceship laser collision with aliens
        for(auto it = aliens.begin(); it != aliens.end();){
            if(CheckCollisionRecs(it -> GetRect(), laser.GetRect())){
                it = aliens.erase(it);
                laser.active = false;
            }
            else{
                ++it;
            }
        }

        //Spaceship laser collision with obstacles
        for(auto obs = obstacles.begin(); obs != obstacles.end(); ++obs){
            for(auto block = obs->blocks.begin(); block != obs->blocks.end();){
                if(CheckCollisionRecs(block -> GetRect(), laser.GetRect())){
                    block = obs->blocks.erase(block);
                    laser.active = false;
                }
                else{
                    ++block;
                }
            }
        }

        //Spaceship laser collision with mysteryship
        if(CheckCollisionRecs(laser.GetRect(), mysteryship.GetRect())){
            mysteryship.alive = false;
            laser.active = false;;
        }
    }

    //Alien laser collisions
    for(Laser& laser: alienLasers){
        //Collision with spaceship
        if(CheckCollisionRecs(laser.GetRect(), spaceship.GetRect())){
            laser.active = false;
            lives --;
        }

        //Collision with obstacles
        for(auto obs = obstacles.begin(); obs != obstacles.end(); ++obs){
            for(auto block = obs->blocks.begin(); block != obs->blocks.end();){
                if(CheckCollisionRecs(block -> GetRect(), laser.GetRect())){
                    block = obs->blocks.erase(block);
                    laser.active = false;
                }
                else{
                    ++block;
                }
            }
        }
    }

    //Alien Collisions
    for(Alien& alien: aliens){
        //Collision with spaceship
        if(CheckCollisionRecs(alien.GetRect(), spaceship.GetRect())){
            lives --;
        }

        //Collision with obstacles
        for(auto obs = obstacles.begin(); obs != obstacles.end(); ++obs){
            for(auto block = obs->blocks.begin(); block != obs->blocks.end();){
                if(CheckCollisionRecs(block -> GetRect(), alien.GetRect())){
                    block = obs->blocks.erase(block);
                }
                else{
                    ++block;
                }
            }
        }
    }
}

void Game::GameOver(){
    run = false;
}
