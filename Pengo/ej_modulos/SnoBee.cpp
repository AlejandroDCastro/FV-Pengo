#include "SnoBee.h"
#include <iostream>


SnoBee::SnoBee(sf::Texture* texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2i position) : Character(texture, speed, changeTime, coordPj, position) {

  //  this->pengo = pengo;
    direction   = 2;
    isStatic    = false;
}




SnoBee::~SnoBee() {
    delete animation;
    animation = NULL;
    delete body;
    body = NULL;
}




// IA SnoBees...
void SnoBee::Update(float deltaTime, Labyrinth* labyrinth) {
    std::vector<sf::Vector2i> _movement;
    std::vector<int> _orientation;
    int _index = -1, _random;

    if (!isWalking  &&  !isStatic) {

        // Check avaliable positions
        if (labyrinth->checkPosition(sf::Vector2i(position.x-1, position.y))) {
            _movement.push_back(sf::Vector2i(position.x-1, position.y));
            _orientation.push_back(0);
            std::cout << "uno" << std::endl;
        }
        if (labyrinth->checkPosition(sf::Vector2i(position.x, position.y+1))) {
            _movement.push_back(sf::Vector2i(position.x, position.y+1));
            _orientation.push_back(1);
            std::cout << "dos" << std::endl;
        }
        if (labyrinth->checkPosition(sf::Vector2i(position.x+1, position.y))) {
            _movement.push_back(sf::Vector2i(position.x+1, position.y));
            _orientation.push_back(2);
            std::cout << "tres" << std::endl;
        }
        if (labyrinth->checkPosition(sf::Vector2i(position.x, position.y-1))) {
            _movement.push_back(sf::Vector2i(position.x, position.y-1));
            _orientation.push_back(3);
            std::cout << "cuatro" << std::endl;
        }

        if (_movement.size() > 0) {
            
            // Follow your way...
            for (unsigned int i=0; i<_orientation.size(); i++) {
                if (direction == _orientation[i]) {
                    _index = int(i);
                    position = _movement[i];
                }
            }

            // Turn to one direction...
            if (_index > -1) {
                isStatic  = false;
                isWalking = true;
            } else {
                _random = rand()%_movement.size();
                _index = _random;
                std::cout << "NUmero:" << _index << std::endl;

                direction = _orientation[_index];
                switch (_orientation[_index]) {
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

                isStatic  = true;
                isWalking = false;
            }

            _orientation.clear();
            _movement.clear();
        }

    }


    if (isStatic  ||  isWalking) {

        // Move Sno-Bee...
        float _displacement = speed*deltaTime;

        // Calculate the displacement...
        if (path+_displacement >= 16.0f) {
            _displacement = 16.0f - path;
            isWalking     = false;
            isStatic      = false;
            path          = 0.0f;
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
    }

    animation->Update(row, column, deltaTime);
    body->setTextureRect(animation->getUVRect());

}