#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"


class Pengo : public Character {
    
    private:
        unsigned int lifes;
        sf::Clock auxClock;
        Animation *deadAnimation;
        bool isStunned;

  
    public:
        Pengo(sf::Texture*, float, float, sf::Vector2u, sf::Vector2u);
        ~Pengo();
        void Update(float deltaTime);
        bool loseLife();
        bool getDead();
  
};
