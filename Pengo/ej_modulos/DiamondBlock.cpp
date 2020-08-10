#include "DiamondBlock.h"





DiamondBlock::DiamondBlock(sf::Texture* texture, unsigned int x, unsigned int y) : Block(texture, x, y) {
    block->setTextureRect(sf::IntRect(BLOCK_SIZE, BLOCK_SIZE*3, BLOCK_SIZE, BLOCK_SIZE));
    path = 0.0f;
}




DiamondBlock::~DiamondBlock() {
    delete block;
    delete position;
    delete animation;
    block     = NULL;
    position  = NULL;
    animation = NULL;
}




void DiamondBlock::Update(float deltaTime) {
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


    // Star play actived so change the block color
    if (actived) {
        animation->Update(3, deltaTime);
        block->setTextureRect(animation->getUVRect());
    }
}