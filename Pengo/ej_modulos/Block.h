#pragma once

#include <SFML/Graphics.hpp>
#include "StaticAnimation.h"


#define BLOCK_SIZE 16


class Block {

    public:
        Block(sf::Texture* ,unsigned int ,unsigned int );
        virtual ~Block();
        virtual void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        void setDirection(int direction);
        int getDirection();
        bool getCanCollide();
        void dontCollide();
        void setPosition(sf::Vector2i );
        sf::Vector2i getPosition();
        sf::Sprite* getSprite();
        sf::Vector2i getNextPosition();
        float getPath();
        virtual void setActived(bool );
        bool getActived();



    protected:
        sf::Sprite *block;
        float speed;            // Movement speed
        int direction;          // Displacement direction
        float path;
        bool canCollide;
        sf::Vector2i* position;
        StaticAnimation *animation;
        bool actived;           // For checking if star play has been activated
};
