#include "Egg.h"




Egg::Egg(sf::Texture *spriteSheet, sf::Texture *tileset, sf::Vector2i position) {
    sprite    = new sf::Sprite(*tileset);
    animation = new StaticAnimation(tileset, .5f, sf::Vector2u(1, 4), sf::Vector2u(14, 18));
    snobee    = new SnoBee(spriteSheet, 60.f, 0.13f, sf::Vector2u(0, 2), position);
    isHatched = false;
}




Egg::~Egg() {
    delete sprite;
    delete animation;
    delete snobee;
    sprite    = NULL;
    animation = NULL;
    snobee    = NULL;
}




SnoBee* Egg::getSnoBee() {
    return snobee;
}