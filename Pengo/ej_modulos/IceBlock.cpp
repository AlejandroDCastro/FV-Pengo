#include "IceBlock.h"



IceBlock::IceBlock(sf::Texture* texture, unsigned int x, unsigned int y) {

    // Initial values
    isBreaking = false;
    isBroke    = false;
    direction  = -1;
    speed      = 30.0f;

    // Building ice block
    block = new sf::Sprite(*texture);
    block->setTextureRect(sf::IntRect(32, 32, 32, 32));
    block->setOrigin(16, 16);
    block->setPosition(32+x*32, 80+y*32);
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
            _cutout.left += 32;
            if (_cutout.left <= 288) {
                block->setTextureRect(_cutout);
            } else {
                isBreaking = false;
                isBroke    = true;
            }
            clock.restart();
        }
    }
}



void IceBlock::Draw(sf::RenderWindow &window) {
    window.draw(*block);
}



void IceBlock::breakDown() {
    isBreaking = true;
}



bool IceBlock::getBroke() {
    return isBroke;
}



void IceBlock::setDirection(int direction) {
    this->direction = direction;
}