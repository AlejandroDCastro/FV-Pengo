#include "Block.h"



Block::Block(sf::Texture* texture, unsigned int x, unsigned int y) {

    // Initial values
    direction  = -1;
    speed      = 250.0f;
    canCollide = false;
    position   = new sf::Vector2i(0, 0);
    

    // Building ice block
    block = new sf::Sprite(*texture);
    block->setTextureRect(sf::IntRect(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
    block->setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
    block->setPosition(16+x*BLOCK_SIZE, 40+y*BLOCK_SIZE);
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



int Block::getDirection() {
    return direction;
}



bool Block::getCanCollide() {
    return canCollide;
}



void Block::dontCollide() {
    canCollide = false;
}



void Block::setPosition(sf::Vector2i position) {
    this->position->x = position.x;
    this->position->y = position.y;
}



sf::Vector2i Block::getPosition() {
    return *position;
}



sf::Sprite* Block::getSprite() {
    return block;
}



sf::Vector2i Block::getNextPosition() {
    sf::Vector2i _next_position = *position;

    switch (direction) {
        case 0:
            _next_position.x--;
            break;
        case 1:
            _next_position.y++;
            break;
        case 2:
            _next_position.x++;
            break;
        case 3:
            _next_position.y--;
            break;
    }

    return _next_position;
}




float Block::getPath() {
    return path;
}