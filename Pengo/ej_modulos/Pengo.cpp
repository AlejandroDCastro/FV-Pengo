#include "Pengo.h"
#include <iostream>


Pengo::Pengo(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2i position) : Character(texture, speed, changeTime, coordPj, position) {

    lifes         = 3;
    deadAnimation = new Animation(texture, coordPj, 0.2f, 2);
    isBlocked     = false;
    push          = false;
    column        = 0;
}



Pengo::~Pengo() {
    delete deadAnimation;
    deadAnimation = NULL;
    delete animation;
    animation = NULL;
    delete body;
    body = NULL;
}



void Pengo::Update(float deltaTime, Labyrinth* labyrinth) {
    sf::Vector2i _auxPosition = position;
    
    if (lifes > 0  &&  (!isWalking && !isPushing && !isStunned)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            isWalking = true;
            column = 4;
            position.x--;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            isWalking = true;
            column = 6;
            position.y++;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            isWalking = true;
            column = 0;
            position.x++;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            isWalking = true;
            column = 2;
            position.y--;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            isPushing = true;
            push      = true;
            animation->setChangeTime(0.13f);
            row++;
            auxClock.restart();
        }
        
        // Invalid positon...
        if (labyrinth->checkPosition(position)) {
            isBlocked = false;
        } else {
            isBlocked = true;
            position  = _auxPosition;
        }
    }

    if (isWalking) {
        float _displacement;

        // Calculate the displacement...
        if (path+speed*deltaTime >= 16.0f) {
            _displacement = 16.0f - path;
            isWalking     = false;
            path          = 0.0f;
        } else {
            path += speed*deltaTime;
            _displacement = speed*deltaTime;
        }

        // Move Pengo...
        if (!isBlocked) {
            if (column == 4)
                body->move(0, -_displacement);
            else if (column == 6)
                body->move(_displacement, 0);
            else if (column == 0)
                body->move(0, _displacement);
            else if (column == 2)
                body->move(-_displacement, 0);
        }

        animation->Update(row, column, deltaTime);
        body->setTextureRect(animation->getUVRect());

    } else if (isPushing) {

        if (auxClock.getElapsedTime().asSeconds() >= 0.4f) {
            isPushing = false;
            row--;
            animation->setChangeTime(0.2f);
        }

        // Push a block...
        if (push) {
            if (column == 4)
                labyrinth->pengoPush(sf::Vector2i(position.x-1, position.y), 0, true);
            else if (column == 6)
                labyrinth->pengoPush(sf::Vector2i(position.x, position.y+1), 1, true);
            else if (column == 0)
                labyrinth->pengoPush(sf::Vector2i(position.x+1, position.y), 2, true);
            else if (column == 2)
                labyrinth->pengoPush(sf::Vector2i(position.x, position.y-1), 3, true);
            push = false;
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