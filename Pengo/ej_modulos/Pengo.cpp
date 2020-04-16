#include "Pengo.h"



Pengo::Pengo(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2u position) : Character(texture, speed, changeTime, coordPj, position) {

    lifes = 3;
    deadAnimation = new Animation(texture, coordPj, 0.2f, 2);
    isStunned = false;
}



Pengo::~Pengo() {
    delete deadAnimation;
    deadAnimation = NULL;
    delete animation;
    animation = NULL;
    delete body;
    body = NULL;
}



void Pengo::Update(float deltaTime) {
    
    if (lifes > 0  &&  (!isWalking && !isPushing && !isStunned)) {
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
            auxClock.restart();
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

        if (auxClock.getElapsedTime().asSeconds() >= 0.4f) {
            isPushing = false;
            row--;
            animation->setChangeTime(0.2f);
        }
        animation->Update(row, column, deltaTime);
        body->setTextureRect(animation->getUVRect());

    } else if (isStunned) {

        if (auxClock.getElapsedTime().asSeconds() >= 2.5f) {
            isStunned = false;
            body->setTextureRect(animation->getUVRect());
            lifes--;
        } else {
            deadAnimation->Update(2, 0, deltaTime);
            body->setTextureRect(deadAnimation->getUVRect());
        }

    }
}



bool Pengo::loseLife() {
    if (lifes > 0) {
        auxClock.restart();
        isStunned = true;
        return true;
    } else {
        return false;
    }
}



bool Pengo::getDead() {
    if (lifes > 0) {
        return false;
    } else {
        return true;
    }
}