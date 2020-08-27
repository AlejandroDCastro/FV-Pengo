#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "IceBlock.h"
#include "StarPlay.h"
#include "Wall.h"


#define TOTAL_DIAMOND_BLOCK 3


class Labyrinth {

    public:
        Labyrinth(sf::Texture *,int **);
        ~Labyrinth();
        void Update(float );
        void Draw(sf::RenderWindow &);
        bool checkPosition(sf::Vector2i );
        void pengoPush(sf::Vector2i ,int ,bool );
        bool snobeePush(sf::Vector2i );
        Block* getBlock(unsigned int ,unsigned int );
        sf::Vector2i getFreePosition();
        PlayState getPlayState();
        bool checkLimit(sf::Vector2i );
        bool getStarPlayUsed();
        void setStarPlayState(int );
        int getWallReeling();



    private:
        Wall *leftWall, *rightWall, *topWall, *bottomWall;
        bool isHit;
        Block ***glacier;             // All blocks
        sf::Vector2u size;
        std::vector<Block*> icicles;  // Remains of ice blocks
        StarPlay *starPlay;
};