#pragma once
#include <SFML/Graphics.hpp>


class Block {

    protected:
        sf::Sprite *block;
        float speed;            // Movement speed
        int direction;          // Displacement direction

    public:
        Block(sf::Texture* texture, unsigned int x, unsigned int y);
        virtual ~Block();
        virtual void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        void getPushed(int direction);
};
