#pragma once
#include <SFML/Graphics.hpp>



class Block {

    protected:
        sf::Sprite *block;
        float speed;            // Movement speed
        int direction;          // Displacement direction
        float path;
        bool canCollide;


    public:
        Block(sf::Texture* ,unsigned int ,unsigned int );
        virtual ~Block();
        virtual void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        void setDirection(int direction);
        sf::Vector2i getDirection();
        bool getCanCollide();
        void dontCollide();
};
