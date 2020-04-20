#include "Block.h"



Block::Block(sf::Texture* texture, unsigned int x, unsigned int y) {

    // Initial values
    direction       = -1;
    speed           = 200.0f;
    canCollide      = false;
    

    // Building ice block
    block = new sf::Sprite(*texture);
    block->setTextureRect(sf::IntRect(16, 16, 16, 16));
    block->setOrigin(8, 8);
    block->setPosition(16+x*16, 40+y*16);
}



Block::~Block() {
    
}



void Block::Update(float deltaTime) {
    
}



void Block::Draw(sf::RenderWindow &window) {
    window.draw(*block);
}



void Block::setDirection(int direction) {
    this->direction = direction;
}



sf::Vector2i Block::getDirection() {
    sf::Vector2i position(0, 0);

    if (direction == 0) {
        position.x--;
    } else if (direction == 1) {
        position.y++;
    } else if (direction == 2) {
        position.x++;
    } else if (direction == 3) {
        position.y--;
    }

    return position;
}



bool Block::getCanCollide() {
    return canCollide;
}



void Block::dontCollide() {
    canCollide = false;
}