#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"


class Character {

    private:
        float speed;
        unsigned int row;
        unsigned int column;
        Animation *animation;
        sf::Sprite *body;


    public:
        Character(sf::Texture* texture, int row, int column, float speed, float changeTime, sf::Vector2u coordPj);
        ~Character();
        virtual void Update(float deltaTime);
        void Draw(sf::RenderWindow &window);
};
