#pragma once

#include <SFML/Graphics.hpp>
#include "SnoBee.h"



class Egg {

    public:
        Egg(sf::Texture *,sf::Texture *);
        ~Egg();


    private:
        sf::Sprite *sprite;
        StaticAnimation *birth, *increase;
        bool isHatched;
        SnoBee *snobee;

};