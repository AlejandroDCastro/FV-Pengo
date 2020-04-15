#include "Character.h"


Character::Character(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj) {

    // Initial values...
    this->row    = (coordPj.y > 1) ? 1 : 0;
    this->column = 0;
    this->speed  = speed;
    isWalking    = false;

    body = new sf::Sprite(*texture);
    animation = new Animation(texture, coordPj, changeTime, 2);
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
