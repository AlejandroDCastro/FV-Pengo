#include "SnoBees.h"



SnoBees::SnoBees(sf::Texture* texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2u position, sf::Vector2u *pengoPosition) : Character(texture, speed, changeTime, coordPj, position) {

    this->pengoPosition = pengoPosition;
}




SnoBees::~SnoBees() {
    delete animation;
    animation = NULL;
    delete body;
    body = NULL;
}




void SnoBees::Update(float deltaTime) {

}