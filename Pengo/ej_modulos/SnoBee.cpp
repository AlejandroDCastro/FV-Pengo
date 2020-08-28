#include "SnoBee.h"




SnoBee::SnoBee(sf::Texture* texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2i position) : Character(texture, speed, changeTime, coordPj, position) {
    direction = 2;
    isStatic  = false;
    bomb      = NULL;
    grownUp   = false;
    isDead    = false;
    stunClock = new sf::Clock();
    stunTime  = 0.0f;
    growthAnimation = new StaticAnimation(texture, .37f, sf::Vector2u(0, 5), sf::Vector2u(40, 18));
}




SnoBee::~SnoBee() {
    delete animation;
    delete body;
    delete stunClock;
    delete growthAnimation;
    stunClock       = NULL;
    animation       = NULL;
    body            = NULL;
    bomb            = NULL;
    pengo           = NULL;
    growthAnimation = NULL;
}




// IA SnoBees...
void SnoBee::Update(float deltaTime, Labyrinth *labyrinth, Pengo *pengo) {

    if (grownUp) {

        int _probabilities[10], _aux_direction, _counter = 0, _short_direction, _index = -1, _new_direction;
        sf::Vector2i _distance;
        std::vector<int> _directions; // Avaliable directions


        // Check avaliable positions
        if (!isWalking  &&  !isStatic  &&  bomb == NULL  &&  !isStunned) {


            // Save all avaliable positions
            if (labyrinth->checkLimit(sf::Vector2i(position.x-1, position.y)))
                _directions.push_back(0);
            if (labyrinth->checkLimit(sf::Vector2i(position.x, position.y+1)))
                _directions.push_back(1);
            if (labyrinth->checkLimit(sf::Vector2i(position.x+1, position.y)))
                _directions.push_back(2);
            if (labyrinth->checkLimit(sf::Vector2i(position.x, position.y-1)))
                _directions.push_back(3);


            // Check if all positions are avaliable
            if (_directions.size() == 4) {


                // Oriented position
                _aux_direction = direction;
                for (unsigned int i=0; i<HIGH_PROBABILITY; i++)
                    _probabilities[_counter++] = _aux_direction;


                // Calculate distance with Pengo
                _distance.x = pengo->getPosition().x-position.x;
                _distance.y = pengo->getPosition().y-position.y;

                // Set direction until Pengo with the long distance
                if (abs(_distance.x) > abs(_distance.y))
                    _aux_direction = (_distance.x > 0) ? 2 : 0;
                else
                    _aux_direction = (_distance.y > 0) ? 1 : 3;
                for (unsigned int i=0; i<MEDIUM_PROBABILITY; i++)
                    _probabilities[_counter++] = _aux_direction;


                // Set direction until Pengo with the short distance
                if (_aux_direction == 0  ||  _aux_direction == 2)
                    _aux_direction = (_distance.y > 0) ? 1 : 3;
                else
                    _aux_direction = (_distance.x > 0) ? 2 : 0;
                for (unsigned int i=0; i<LOW_PROBABILITY; i++)
                    _probabilities[_counter++] = _aux_direction;


                // Last probability is in opposite direction to Pengo
                _short_direction = (_aux_direction == 0  ||  _aux_direction == 1) ? _aux_direction+2 : _aux_direction-2;
                _probabilities[_counter++] = _short_direction;

                
                // Choose a direction
                _index         = rand()%10;
                _new_direction = _probabilities[_index];


            } else {    // SnoBee reaches a Wall and set direction randomly

                _index         = rand()%_directions.size();
                _new_direction = _directions[_index];

            }


            // If gets a new direction only stay static and change direction
            if (direction == _new_direction) {
                isStatic  = false;
                isWalking = true;

                // Save new position
                this->setPosition(direction);

            } else {
                isStatic  = true;
                isWalking = false;

                direction = _new_direction;
                this->setOrientation(direction);
            }


            // Break an ice block by the way of SnoBee
            if (labyrinth->snobeePush(position)) {
                row   = 2;
                speed = 15.f;
            } else {
                row   = 1;
                speed = 60.f;
            }
            
            
            _directions.clear();
        }



        // Move SnoBee...
        if (isStatic  ||  isWalking) {

            // Sno-Bee displacement...
            float _displacement = speed*deltaTime;

            // Calculate the displacement...
            if (path+_displacement >= TRAVEL_DISTANCE_OF_BLOCK) {
                _displacement = TRAVEL_DISTANCE_OF_BLOCK - path;
                isWalking     = false;
                isStatic      = false;
                path          = 0.0f;
                body->setPosition(16+position.y*TRAVEL_DISTANCE_OF_BLOCK, 40+position.x*TRAVEL_DISTANCE_OF_BLOCK);
            } else {
                path += _displacement;
            }

            if (isWalking  &&  !isStatic) {
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

        } else if (bomb) {
            sf::Vector2f _displacement(0.0f, 0.0f);
            sf::Vector2f _position;

            // Suffer the hit...
            if (bomb->getDirection() > -1) {

                // Direction movement when the block does not raise his limit
                if (labyrinth->checkPosition(bomb->getNextPosition())) {
                    switch (bomb->getDirection()) {
                        case 0:
                            column = 0;
                            _displacement.y = -9;
                            break;
                        case 1:
                            column = 2;
                            _displacement.x = +9;
                            break;
                        case 2:
                            column = 4;
                            _displacement.y = +9;
                            break;
                        case 3:
                            column = 6;
                            _displacement.x = -9;
                            break;
                    }
                } else {    // Direction movement when the block raises his limit
                    switch (bomb->getDirection()) {
                        case 0:
                            column = 1;
                            _displacement.y = -4;
                            break;
                        case 1:
                            column = 3;
                            _displacement.x = +4;
                            break;
                        case 2:
                            column = 5;
                            _displacement.y = +4;
                            break;
                        case 3:
                            column = 7;
                            _displacement.x = -4;
                            break;
                    }
                }
                

                // Set the clipping to the SnoBee suffering the one hit of a block
                if (row != 4) {
                    row = 4;
                    animation->Update(row, column, deltaTime);
                    body->setTextureRect(animation->getUVRect());
                }

                // Set his position next to the block
                _position = bomb->getSprite()->getPosition();
                body->setPosition(_position + _displacement);

            } else {

                isDead = true;
            }

        } else if (isStunned) {

            if (stunClock->getElapsedTime().asSeconds() >= stunTime) {
                row = 1;
                isStunned = false;
                this->restartPosition(deltaTime);
            }

            animation->Update(row, column, deltaTime);
            body->setTextureRect(animation->getUVRect());

        }
    
    } else {

        if (growthAnimation->finished()) {
            grownUp = true;
        } else {
            growthAnimation->Update(8, deltaTime);
            body->setTextureRect(growthAnimation->getUVRect());
        }

    }

}



void SnoBee::collideBlock(Block* block) {
    bomb      = block;
    isStatic  = false;
    isWalking = false;
}



bool SnoBee::getFree() {
    if (bomb)
        return false;
    else
        return true;
}




bool SnoBee::getDead() {
    return isDead;
}




void SnoBee::getKilled() {
    isDead = true;
}




bool SnoBee::getSmashed() {
    if (bomb)
        return true;
    else
        return false;
}




bool SnoBee::getGrownUp() {
    return grownUp;
}




void SnoBee::setOrientation(int dir) {
    switch (dir) {
        case 0:
            column = 4;
            break;
        case 1:
            column = 6;
            break;
        case 2:
            column = 0;
            break;
        case 3:
            column = 2;
            break;
    }
}





void SnoBee::setPosition(int dir) {
    switch (dir) {
        case 0:
            position.x--;
            break;
        case 1:
            position.y++;
            break;
        case 2:
            position.x++;
            break;
        case 3:
            position.y--;
            break;
    }
}





void SnoBee::stunSnoBee(float stunTime) {
    this->stunTime = stunTime;
    stunClock->restart();
    row = 0;  column = 6;
    isStatic  = false;
    isWalking = false;
    isStunned = true;
}