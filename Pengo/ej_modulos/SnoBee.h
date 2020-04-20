#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"


class SnoBee : public Character {

    private:
        sf::Vector2i* pengoPosition;
        int direction; // 0:Up - 1:Right - 2:Down - 3:Left
        bool isStatic;


    public:
        SnoBee(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i, sf::Vector2i* );
        ~SnoBee();
        void Update(float ,Labyrinth* );
};