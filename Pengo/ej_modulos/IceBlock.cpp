#include "IceBlock.h"



IceBlock::IceBlock(sf::Texture* texture, unsigned int x, unsigned int y) : Block(texture, x, y) {

    // Initial values
    isBreaking = false;
    isBroke    = false;
}



IceBlock::~IceBlock() {
    delete block;
    block = NULL;
}



void IceBlock::Update(float deltaTime) {
    if (!isBroke  &&  !isBreaking) {
        switch (direction) {
            case 0:
                block->move(0, -speed*deltaTime);
                break;
            case 1:
                block->move(speed*deltaTime, 0);
                break;
            case 2:
                block->move(0, speed*deltaTime);
                break;
            case 3:
                block->move(-speed*deltaTime, 0);
                break;
        }
    } else if (isBreaking) {
        if (clock.getElapsedTime().asSeconds() > 0.1f) {
            sf::IntRect _cutout = block->getTextureRect();
            _cutout.left += 16;
            if (_cutout.left <= 144) {
                block->setTextureRect(_cutout);
            } else {
                isBreaking = false;
                isBroke    = true;
            }
            clock.restart();
        }
    }
}



void IceBlock::breakDown() {
    isBreaking = true;
}



bool IceBlock::getBroke() {
    return isBroke;
}

