#include "Character.h"


Character::Character(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2u position) {

    // Initial values...
    this->row      = (coordPj.y > 1) ? 1 : 0;
    this->column   = 0;
    this->speed    = speed;
    isWalking      = false;
    path           = 0.0f;
    this->position = position;

    // Create the character...
    body = new sf::Sprite(*texture);
    animation = new Animation(texture, coordPj, changeTime, 2);
    body->setOrigin(animation->getOrigin());
    body->setPosition(32+position.x*32, 80+position.y*32);
}



Character::~Character() {
    delete body;
    body = NULL;
    delete animation;
    animation = NULL;
}



void Character::Draw(sf::RenderWindow &window) {
    window.draw(*body);
}
