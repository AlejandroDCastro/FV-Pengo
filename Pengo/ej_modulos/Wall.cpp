#include "Wall.h"




Wall::Wall(sf::Texture *texture, sf::IntRect rectangle, sf::Vector2f position, sf::Vector2f origin) {
    sprite = new sf::Sprite(*texture);
    sprite->setTextureRect(rectangle);
    sprite->setPosition(position);
    sprite->setOrigin(origin);
}




Wall::~Wall() {
    delete sprite;
    sprite = NULL;
}