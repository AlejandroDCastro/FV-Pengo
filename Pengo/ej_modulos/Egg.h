#pragma once
#include <SFML/Graphics.hpp>
#include "SnoBee.h"



class Egg {

    public:
        Egg(sf::Texture *,sf::Texture *,sf::Vector2i );
        ~Egg();
        SnoBee* getSnoBee();


    private:
        sf::Sprite *sprite;
        StaticAnimation *animation;
        bool isHatched;
        SnoBee *snobee;

};