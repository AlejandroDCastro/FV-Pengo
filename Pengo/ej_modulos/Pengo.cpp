#include "Pengo.h"



Pengo::Pengo(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2u position) : Character(texture, speed, changeTime, coordPj, position) {

    // All for superclass Character

}



Pengo::~Pengo() {
    
}



void Pengo::Update(float deltaTime) {
    
    if (!isWalking) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            isWalking = true;
            column = 4;
            position.y--;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            isWalking = true;
            column = 6;
            position.x++;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            isWalking = true;
            column = 0;
            position.y++;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            isWalking = true;
            column = 2;
            position.x--;
        }
    }

    if (isWalking) {
        sf::Vector2f movement(0.0f, 0.0f);
        float displacement;

        path += speed*deltaTime;
        if (path >= 32.0f) {
            displacement = path - 32.0f;
            isWalking    = false;
            path         = 0.0f;
        } else {
            displacement = speed*deltaTime;
        }
        if (column == 4)
            movement.y -= displacement;
        else if (column == 6)
            movement.x += displacement;
        else if (column == 0)
            movement.y += displacement;
        else if (column == 2)
            movement.x -= displacement;

        animation->Update(row, column, deltaTime);
        body->setTextureRect(animation->getUVRect());
    }
}
