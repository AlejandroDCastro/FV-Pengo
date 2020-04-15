#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"


class Character {

    protected:
        float speed;
        unsigned int row;
        unsigned int column;
        Animation *animation;
        sf::Sprite *body;
        bool isWalking;
        bool isPushing;
        sf::Vector2u position;
        float path;


    public:
        Character(sf::Texture* texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2u position);
        virtual ~Character();
        virtual void Update(float deltaTime);
        void Draw(sf::RenderWindow &window);
};
