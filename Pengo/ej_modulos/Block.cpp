#include "Block.h"



Block::Block(sf::Texture* texture, unsigned int x, unsigned int y) {

    // Initial values
    direction  = -1;
    speed      = 30.0f;

    // Building ice block
    block = new sf::Sprite(*texture);
    block->setTextureRect(sf::IntRect(32, 32, 32, 32));
    block->setOrigin(16, 16);
    block->setPosition(32+x*32, 80+y*32);
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
