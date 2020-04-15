#pragma once
#include <SFML/Graphics.hpp>


class Block {

    private:
        sf::Sprite *block;
        float speed;            // Movement speed
        int direction;          // Displacement direction

    public:
        Block(sf::Texture* texture, unsigned int x, unsigned int y);
        ~Block();
        virtual void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        void getPushed(int direction);
};
