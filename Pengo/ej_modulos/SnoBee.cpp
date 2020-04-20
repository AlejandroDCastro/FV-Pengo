#include "SnoBee.h"



SnoBee::SnoBee(sf::Texture* texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2i position, sf::Vector2i *pengoPosition) : Character(texture, speed, changeTime, coordPj, position) {

    this->pengoPosition = pengoPosition;
    direction           = 2;
}




SnoBee::~SnoBee() {
    pengoPosition = NULL;
    delete animation;
    animation = NULL;
    delete body;
    body = NULL;
}




// IA SnoBees...
void SnoBee::Update(float deltaTime, Labyrinth* labyrinth) {
    std::vector<sf::Vector2i> _movement;
    std::vector<int> _orientation;
    int _x = position.x, _y = position.y, _idx = 0, _total;
    int _odds[4];
    unsigned int _index;

    // Check the possible positions...
    if (labyrinth->checkPosition(sf::Vector2i(_x-1, _y))) {
        _movement.push_back(sf::Vector2i(_x-1, _y));
        _orientation.push_back(0);
        _odds[0] = 1;
    } else {
        _odds[0] = 0;
    }
    if (labyrinth->checkPosition(sf::Vector2i(_x, _y+1))) {
        _movement.push_back(sf::Vector2i(_x, _y+1));
        _orientation.push_back(1);
        _odds[1] = 1;
    } else {
        _odds[1] = 0;
    }
    if (labyrinth->checkPosition(sf::Vector2i(_x+1, _y))) {
        _movement.push_back(sf::Vector2i(_x+1, _y));
        _orientation.push_back(2);
        _odds[2] = 1;
    } else {
        _odds[2] = 0;
    }
    if (labyrinth->checkPosition(sf::Vector2i(_x, _y-1))) {
        _movement.push_back(sf::Vector2i(_x, _y-1));
        _orientation.push_back(3);
        _odds[3] = 1;
    } else {
        _odds[3] = 0;
    }

    if (_movement.size() > 0) {

        // Add points depending of the distance with Pengo...
        sf::Vector2i _distance = (*pengoPosition) - position;
        if (_distance.x < 0  &&  _odds[0] > 0) {
            _odds[0]++;
        }
        if (_distance.x > 0  &&  _odds[2] > 0) {
            _odds[2]++;
        }
        if (_distance.y > 0  &&  _odds[1] > 0) {
            _odds[1]++;
        }
        if (_distance.y < 0  &&  _odds[3] > 0) {
            _odds[3]++;
        }

        // Add points depending of the orientation...
        for (unsigned int i=0; i<4; i++) {
            if (_odds[i] > 0  &&  _orientation[_idx++] == direction) {
                _odds[i] += 2;
                break;
            }
        }
        _idx = 0;


        // Calculate the odds...
        float _percentage[_movement.size()];
        _total = _odds[0] + _odds[1] + _odds[2] + _odds[3];
        for (unsigned int i=0; i<3; i++) {
            if (_odds[i] > 0) {
                _percentage[_idx] = float(_odds[i]/_total);
                if (_idx > 0)
                    _percentage[_idx] += _percentage[_idx-1];
                _idx++;
            }
        }
        _percentage[_movement.size()-1] = 1.0f;
        _idx = 0;


        // Choose the next SnoBee position
        float _random = ( rand() % 100 ) / 100;
        for (unsigned int i=0; i<_movement.size(); i++) {
            if (i == 0) {
                if (_random >= 0.0f  &&  _random < _percentage[i]) {
                    _index = i;
                    break;
                }
            } else {
                if (_random >= _percentage[i-1]  &&  _random <= _percentage[i]) {
                    _index = i;
                    break;
                }
            }
        }

        // Set SnoBee position...
        position = _movement[_index];
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

    }

    _movement.clear();
    _orientation.clear();

}