#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"


class Pengo : public Character {
    
    private:
        unsigned int lifes;
        sf::Clock auxClock;
        Animation *deadAnimation;
        bool isBlocked;

  
    public:
        Pengo(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i);
        ~Pengo();
        void Update(float ,Labyrinth* );
        bool loseLife();
        bool getDead();
  
};
