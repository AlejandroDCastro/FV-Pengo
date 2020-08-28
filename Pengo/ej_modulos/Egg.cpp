#include "Egg.h"




Egg::Egg(sf::Texture *spriteSheet, sf::Texture *tileset, Labyrinth *labyrinth) {
    sprite    = new sf::Sprite(*tileset);
    animation = new StaticAnimation(tileset, .5f, sf::Vector2u(1, 4), sf::Vector2u(14, 18));
    snobee    = new SnoBee(spriteSheet, 60.f, 0.15f, sf::Vector2u(0, 2), labyrinth->getFreePosition());
}




Egg::~Egg() {

}




SnoBee* Egg::getSnoBee() {
    return snobee;
}