#pragma once
#include <SFML/Graphics.hpp>


class IceBlock {

    private:
        sf::Sprite *block;
        bool isBreaking;

    public:
        IceBlock(sf::Texture* texture, unsigned int x, unsigned int y);
        ~IceBlock();
        void pushed(int direction);
        void Draw(sf::RenderWindow &);
};