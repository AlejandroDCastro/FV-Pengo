#include "Animation.h"


Animation::Animation(sf::Texture *texture, sf::Vector2u coordPj, float changeTime) {
    this->changeTime = changeTime;
    this->coordPj    = coordPj;

    // Height and Width of sprite...
    uvRect.width  = texture->getSize().x / 40;
    uvRect.height = texture->getSize().y / 18;

    // Initial values...
    change = false;
    totalTime = 0.0f;
    actualCoord.y = (coordPj.y > 1) ? 1 : 0;
    actualCoord.x = 0;
}


Animation::~Animation() {

}


void Animation::Update(unsigned int row, unsigned int column, float deltaTime) {

    // If pj change movement then change rectangle...
    if (actualCoord.y != row  ||  actualCoord.x != column) {
        actualCoord.y = row;
        actualCoord.x = column;
        changeTime = 0.0f;
    } else {

        // Count the time...
        totalTime += deltaTime;
    }

    // Next rectangle of the same animation...
    if (totalTime >= changeTime) {
        totalTime -= changeTime;
        actualCoord.x++;

        if (change) {
            actualCoord.x--;
            change = false;
        } else {
            change = true;
        }
    }

    uvRect.left = (coordPj.x*8*uvRect.width) + (actualCoord.x*uvRect.width);
    uvRect.top  = (coordPj.y*4*uvRect.height) + (actualCoord.y*uvRect.height);
}


sf::IntRect Animation::getUVRect() {
    return uvRect;
}


sf::Vector2f Animation::getOrigin() {
    return sf::Vector2f(uvRect.width/2, uvRect.height/2);
}