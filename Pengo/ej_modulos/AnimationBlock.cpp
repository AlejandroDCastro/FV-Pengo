#include "AnimationBlock.h"





AnimationBlock::AnimationBlock(sf::Texture *texture, sf::Vector2u coordPj, float changeTime) {
    this->coordPj    = coordPj;
    this->changeTime = changeTime;

    uvRect.width  = texture->getSize().x / 14;
    uvRect.height = texture->getSize().y / 18;

    totalTime     = 0.0f;
    actualCoord.y = 0;
    actualCoord.x = 0;
}





AnimationBlock::~AnimationBlock() {

}