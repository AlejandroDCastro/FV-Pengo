#include "StaticAnimation.h"





StaticAnimation::StaticAnimation(sf::Texture *texture, float changeTime, sf::Vector2u range, sf::Vector2u size) {
    this->changeTime = changeTime;
    totalTime        = 0.0f;
    this->range      = range;
    uvRect           = new sf::IntRect(0, 0, texture->getSize().x/size.x, texture->getSize().y/size.y);
    actualCoord      = new sf::Vector2u(range.x, 0);
}





StaticAnimation::~StaticAnimation() {
    delete uvRect;
    delete actualCoord;
    actualCoord = NULL;
    uvRect      = NULL;
}




// Update animation block
void StaticAnimation::Update(unsigned int row, float deltaTime) {

    actualCoord->y = row;
    totalTime     += deltaTime;

    // Check if we need to restart animation or continue
    if (totalTime >= changeTime) {
        totalTime -= changeTime;
        actualCoord->x++;

        if (actualCoord->x > range.y)
            actualCoord->x = range.x;
    }

    uvRect->left = actualCoord->x * uvRect->width;
    uvRect->top  = actualCoord->y * uvRect->height;
}




sf::IntRect StaticAnimation::getUVRect() {
    return *uvRect;
}




sf::Vector2f StaticAnimation::getOrigin() {
    return sf::Vector2f(BLOCK_SIZE/2, BLOCK_SIZE/2);
}




void StaticAnimation::setRange(unsigned int x, unsigned int y) {
    range.x = x;
    range.y = y;
    actualCoord->x = (x == 1) ? x+1 : x;
}




void StaticAnimation::setChangeTime(float changeTime) {
    this->changeTime = changeTime;
    totalTime = 0;
}