#pragma once

#include <SFML/Graphics.hpp>





class Wall {

    public:
        Wall(sf::Texture *,sf::IntRect ,sf::Vector2f ,sf::Vector2f );
        ~Wall();



    private:
        sf::Sprite* sprite;

};