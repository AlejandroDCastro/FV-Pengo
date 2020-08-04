#pragma once
#include <SFML/Graphics.hpp>
#include "IceBlock.h"
#include "MazeGenerator.h"



class Labyrinth {

    private:
        sf::Texture *texture;
        sf::Sprite *leftWall;
        sf::Sprite *rightWall;
        sf::Sprite *topWall;
        sf::Sprite *bottomWall;
        bool isHit;
        Block ***glacier;             // All blocks
        int **map;                    // Maze structure
        sf::Vector2u size;
        std::vector<Block*> icicles;  // Remains of ice blocks


    public:
        Labyrinth(sf::Texture *);
        ~Labyrinth();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        bool checkPosition(sf::Vector2i );
        void pengoPush(sf::Vector2i ,int ,bool );
        Block* getBlock(unsigned int, unsigned int);
        sf::Vector2i getFreePosition();
        void rebuild();
};