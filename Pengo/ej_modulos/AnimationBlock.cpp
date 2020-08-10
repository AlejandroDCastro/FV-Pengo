#include "AnimationBlock.h"





AnimationBlock::AnimationBlock(sf::Texture *texture, sf::Vector2u range) {
    this->range    = &range;

    changeTime  = 0.2f;
    totalTime   = 0.0f;
    uvRect      = new sf::IntRect(0, 0, texture->getSize().x/14, texture->getSize().y/18);
    actualCoord = new sf::Vector2u(0, 0);
}





AnimationBlock::~AnimationBlock() {
    delete actualCoord;
    delete range;
    delete uvRect;
    actualCoord = NULL;
    range       = NULL;
    uvRect      = NULL;
}




// Update animation block
void AnimationBlock::Update(unsigned int row, float deltaTime) {

    actualCoord->y = row;
    totalTime     += deltaTime;

    // Check if we need to restart animation or continue
    if (totalTime >= changeTime) {
        totalTime -= changeTime;
        actualCoord->x++;

        if (actualCoord->x > range->y)
            actualCoord->x = range->x;
    }

    uvRect->left = actualCoord->x * uvRect->width;
    uvRect->top  = actualCoord->y * uvRect->height;
}




sf::IntRect AnimationBlock::getUVRect() {
    return *uvRect;
}




sf::Vector2f AnimationBlock::getOrigin() {
    return sf::Vector2f(BLOCK_SIZE/2, BLOCK_SIZE/2);
}