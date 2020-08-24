#include "Pengo.h"



Pengo::Pengo(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2i position) : Character(texture, speed, changeTime, coordPj, position) {

    lifes         = 3;
    deadAnimation = new Animation(texture, coordPj, 0.13f, 2);
    isBlocked     = false;
    push          = false;
    godMode       = false;
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

    if (isWalking) {
        float _displacement;

        // Calculate the displacement...
        if (path+speed*deltaTime >= TRAVEL_DISTANCE_OF_PENGO) {
            _displacement = TRAVEL_DISTANCE_OF_PENGO - path;
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

        if (pushClock.getElapsedTime().asSeconds() >= 0.4f) {
            isPushing = false;
            row = 0;
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

        deadAnimation->Update(2, 0, deltaTime);
        body->setTextureRect(deadAnimation->getUVRect());

    }
}



void Pengo::UpdateMovement(int direction, Labyrinth* labyrinth) {
    sf::Vector2i _auxPosition = position;

    if (lifes > 0  &&  (!isWalking && !isPushing && !isStunned)) {
        switch (direction)
        {
            case 0: // UP
                isWalking = true;
                column = 4;
                position.x--;
                break;
            case 1: // RIGHT
                isWalking = true;
                column = 6;
                position.y++;
                break;
            case 2: // DOWN
                isWalking = true;
                column = 0;
                position.x++;
                break;
            case 3: // LEFT
                isWalking = true;
                column = 2;
                position.y--;
                break;
            case 4: // PUSH
                isPushing = true;
                push      = true;
                animation->setChangeTime(0.13f);
                row = 1;
                pushClock.restart();
                break;
        }

        // Invalid positon...
        if (labyrinth->checkPosition(position)) {
            isBlocked = false;
        } else {
            isBlocked = true;
            position  = _auxPosition;
        }
    }
}



bool Pengo::loseLife() {
    if (lifes > 0) {
        if (!godMode)
            lifes--;
        isStunned = true;
        isWalking = false;
        isPushing = false;
        row       = 0;
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



// This method is used to locate Pengo in the initial position after being stunned by a SnoBee
void Pengo::restartInitialState(float deltaTime) {
    isStunned = false;
    animation->Update(0, 0, deltaTime);
    body->setTextureRect(animation->getUVRect());
    position.x = INITIAL_POSITION_X_Y;
    position.y = INITIAL_POSITION_X_Y;
    path       = 0.0f;
    body->setPosition(16+INITIAL_POSITION_X_Y*BLOCK_SIZE, 40+INITIAL_POSITION_X_Y*BLOCK_SIZE);
}



void Pengo::restoreLifes() {
    lifes = 3;
}



void Pengo::changeGodMode(sf::RenderWindow* window, float deltaTime) {
    if (godMode) {
        godMode     = false;
        stunnedTime = 2.5f;
        animation->setCoordPj(sf::Vector2u(0, 0));
        deadAnimation->setCoordPj(sf::Vector2u(0, 0));
    } else {
        godMode = true;
        stunnedTime = 1.2f;
        animation->setCoordPj(sf::Vector2u(2, 0));
        deadAnimation->setCoordPj(sf::Vector2u(2, 0));
    }
    animation->Update(row, column, deltaTime);
    body->setTextureRect(animation->getUVRect());
}



bool Pengo::getGodMode() {
    return godMode;
}