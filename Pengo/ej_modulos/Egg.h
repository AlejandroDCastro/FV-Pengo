#pragma once

#include <SFML/Graphics.hpp>
#include "SnoBee.h"



class Egg {

    public:
        Egg(sf::Texture *);
        ~Egg();


    private:
        sf::Sprite *sprite;
        StaticAnimation *animation;
        bool isHatched;
        SnoBee *snobee;

};