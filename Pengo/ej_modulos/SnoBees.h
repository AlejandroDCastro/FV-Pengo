#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"


class SnoBees : public Character {

    private:
        sf::Vector2u* pengoPosition;


    public:
        SnoBees(sf::Texture*, float, float, sf::Vector2u, sf::Vector2u, sf::Vector2u*);
        ~SnoBees();
        void Update(float);
};