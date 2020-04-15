#include "Pengo.h"



Pengo::Pengo(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2u position) : Character(texture, speed, changeTime, coordPj, position) {

}



Pengo::~Pengo() {
    delete body;
    body = NULL;
    delete animation;
    animation = NULL;
}



void Pengo::Update(float deltaTime) {
    
    if (!isWalking  &&  !isPushing) {
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
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            isPushing = true;
            animation->setChangeTime(0.13f);
            row++;
            pushClock.restart();
        }
    }

    if (isWalking) {
        float _displacement;

        // Calculate the displacement...
        path += speed*deltaTime;
        if (path >= 32.0f) {
            _displacement = path - 32.0f;
            isWalking     = false;
            path          = 0.0f;
        } else {
            _displacement = speed*deltaTime;
        }

        // Move Pengo...
        if (column == 4)
            body->move(0, -_displacement);
        else if (column == 6)
            body->move(_displacement, 0);
        else if (column == 0)
            body->move(0, _displacement);
        else if (column == 2)
            body->move(-_displacement, 0);

        animation->Update(row, column, deltaTime);
        body->setTextureRect(animation->getUVRect());

    } else if (isPushing) {

        if (pushClock.getElapsedTime().asSeconds() >= 0.4f) {
            isPushing = false;
            row--;
            animation->setChangeTime(0.2f);
        }
        animation->Update(row, column, deltaTime);
        body->setTextureRect(animation->getUVRect());
    }
}
