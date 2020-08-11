#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"


class IceBlock : public Block {

    private:
        bool isBreaking;
        bool isBroke;
        sf::Clock clock;    // Clock for breaking animation

    public:
        IceBlock(sf::Texture* ,unsigned int ,unsigned int );
        ~IceBlock();
        void Update(float deltaTime);
        void breakDown();
        bool getBroke();
        bool getBreaking();
        void setActived(bool );
};
