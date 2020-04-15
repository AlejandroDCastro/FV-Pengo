#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"


class IceBlock : public Block {

    private:
        bool isBreaking;
        bool isBroke;
        sf::Clock clock;

    public:
        IceBlock(sf::Texture* texture, unsigned int x, unsigned int y);
        ~IceBlock();
        void Update(float deltaTime);
        void breakDown();
        bool getBroke();
        void setDirection(int direction);
};
