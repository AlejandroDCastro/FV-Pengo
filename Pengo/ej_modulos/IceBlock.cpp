#include "IceBlock.h"



IceBlock::IceBlock(sf::Texture* texture, unsigned int x, unsigned int y) : Block(texture, x, y) {

    // Initial values
    block->setTextureRect(sf::IntRect(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
    isBreaking = false;
    isBroke    = false;
    path       = 0.0f;
    egg        = NULL;
}



IceBlock::~IceBlock() {
    delete block;
    delete position;
    delete animation;
    delete egg;
    block     = NULL;
    position  = NULL;
    animation = NULL;
    egg       = NULL;
}



void IceBlock::Update(float deltaTime) {
    if (!isBroke  &&  !isBreaking) {

        if (direction > -1) {
            float _displacement = speed*deltaTime;

            // Calculate the block position
            if (_displacement+path >= BLOCK_SIZE) {
                _displacement  = BLOCK_SIZE - path;
                path           = 0.0f;
                canCollide     = true;

                if (direction == 0)
                    position->x--;
                else if (direction == 1)
                    position->y++;
                else if (direction == 2)
                    position->x++;
                else if (direction == 3)
                    position->y--;

            } else {
                path += _displacement;
                canCollide = false;
            }

            switch (direction) {
                case 0:
                    block->move(0, -_displacement);
                    break;
                case 1:
                    block->move(_displacement, 0);
                    break;
                case 2:
                    block->move(0, _displacement);
                    break;
                case 3:
                    block->move(-_displacement, 0);
                    break;
            }
        }
    } else if (isBreaking) {
        if (clock.getElapsedTime().asSeconds() > 0.05f) {
            sf::IntRect _clipping = block->getTextureRect();
            _clipping.left += 16;
            if (_clipping.left <= 160) {
                block->setTextureRect(_clipping);
            } else {
                isBreaking = false;
                isBroke    = true;
            }
            clock.restart();
        }
    }


    // Star play actived so change the block color
    if (actived) {
        animation->Update(2, deltaTime);
        block->setTextureRect(animation->getUVRect());
    }
}



void IceBlock::breakDown() {
    isBreaking = true;
}



bool IceBlock::getBroke() {
    return isBroke;
}



bool IceBlock::getBreaking() {
    return isBreaking;
}



// Change the color because of the star play
void IceBlock::setActived(bool actived) {
    this->actived = actived;
    if (!actived)
        block->setTextureRect(sf::IntRect(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
}




// Incubate a Egg inside the ice block for hatching after killing a SnoBee
void IceBlock::incubateEgg(sf::Texture *spriteSheet, sf::Texture *tileset, sf::Vector2i pos) {
    egg = new Egg(spriteSheet, tileset, pos);
}




Egg* IceBlock::getEgg() {
    return egg;
}