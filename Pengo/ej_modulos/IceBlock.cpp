#include "IceBlock.h"



IceBlock::IceBlock(sf::Texture* texture, unsigned int x, unsigned int y) {
    isBreaking = false;

    // Building ice block
    block = new sf::Sprite(*texture);
    block->setTextureRect(sf::IntRect(32, 32, 32, 32));
    block->setOrigin(16, 16);
    block->setPosition(32+x*32, 80+y*32);
}



IceBlock::~IceBlock() {

}



void IceBlock::pushed(int direction) {

}



void IceBlock::Draw(sf::RenderWindow &window) {
    window.draw(*block);
}