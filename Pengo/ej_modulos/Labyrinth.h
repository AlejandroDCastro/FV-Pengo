#pragma once
#include <SFML/Graphics.hpp>
#include "IceBlock.h"
#include "StarPlay.h"


#define TOTAL_DIAMOND_BLOCK 3


class Labyrinth {

    public:
        Labyrinth(sf::Texture *,int **);
        ~Labyrinth();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        bool checkPosition(sf::Vector2i );
        void pengoPush(sf::Vector2i ,int ,bool );
        Block* getBlock(unsigned int, unsigned int);
        sf::Vector2i getFreePosition();
        PlayState getPlayState();



    private:
        sf::Sprite *leftWall;
        sf::Sprite *rightWall;
        sf::Sprite *topWall;
        sf::Sprite *bottomWall;
        bool isHit;
        Block ***glacier;             // All blocks
        sf::Vector2u size;
        std::vector<Block*> icicles;  // Remains of ice blocks
        StarPlay *starPlay;
};