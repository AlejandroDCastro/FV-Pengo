#include "Block.h"



Block::Block(sf::Texture* texture, unsigned int x, unsigned int y) {

    // Initial values
    direction  = -1;
    speed      = 30.0f;

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



void Block::getPushed(int direction) {
    this->direction = direction;
}
