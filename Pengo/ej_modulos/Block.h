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
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        //void breakDown();
       // bool getBroke();
        void setDirection(int direction);
};