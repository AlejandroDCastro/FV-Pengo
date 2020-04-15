#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"


class Pengo : public Character {
    
    private:
        
  
    public:
        Pengo(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2u position);
        ~Pengo();
        void Update(float deltaTime);
  
};
