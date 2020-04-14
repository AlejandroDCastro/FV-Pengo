#pragma once
#include <SFML/Graphics.hpp>
#include "IceBlock.h"


class Labyrinth {

    private:
        sf::Sprite *leftWall;
        sf::Sprite *rightWall;
        sf::Sprite *topWall;
        sf::Sprite *bottomWall;
        bool isHit;
        IceBlock ***glacier;        // All blocks
        sf::Vector2u size;


    public:
        Labyrinth(sf::Texture* texture);
        ~Labyrinth();
     //   void getHit();
        void Draw(sf::RenderWindow &);

};