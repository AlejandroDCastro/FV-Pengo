#include "Character.h"


Character::Character(sf::Texture *texture, int row, int column, float speed, float changeTime, sf::Vector2u coordPj) {

    // Initial values...
    this->row = row;
    this->column = column;
    this->speed = speed;

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
