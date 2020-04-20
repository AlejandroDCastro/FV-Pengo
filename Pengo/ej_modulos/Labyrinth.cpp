#include "Labyrinth.h"
#include <iostream>


Labyrinth::Labyrinth(sf::Texture* texture) {
    isHit = false;

    // Build the walls and put them on screen...
    leftWall   = new sf::Sprite(*texture);
    rightWall  = new sf::Sprite(*texture);
    topWall    = new sf::Sprite(*texture);
    bottomWall = new sf::Sprite(*texture);

    leftWall->setTextureRect(sf::IntRect(8, 16, 8, 256));
    rightWall->setTextureRect(sf::IntRect(8, 16, 8, 256));
    topWall->setTextureRect(sf::IntRect(0, 8, 224, 8));
    bottomWall->setTextureRect(sf::IntRect(0, 8, 224, 8));

    leftWall->setPosition(0, 24);
    leftWall->setOrigin(4, 0);
    leftWall->setScale(-1, 1);
    leftWall->setOrigin(8, 0);
    rightWall->setPosition(216, 24);
    topWall->setPosition(0, 24);
    topWall->setOrigin(0, 4);
    topWall->setScale(1, -1);
    topWall->setOrigin(0, 8);
    bottomWall->setPosition(0, 272);


    // Reserve momory for the matrix...
    size.x = 15;  size.y = 13;
    glacier = new Block**[size.x];
    for (unsigned int i=0; i<size.x; i++) {
        glacier[i] = new Block*[size.y];
    }

    int alex[15][13] = {
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}
    };
    
    // Put all the ice blocks...
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (alex[i][j] == 1) {
                glacier[i][j] = new IceBlock(texture, j, i);
            } else {
                glacier[i][j] = NULL;
            }
        }
    }

}



Labyrinth::~Labyrinth() {
    delete leftWall;
    leftWall = NULL;
    delete rightWall;
    rightWall = NULL;
    delete topWall;
    topWall = NULL;
    delete bottomWall;
    bottomWall = NULL;
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (glacier[i][j])
                delete glacier[i][j];
        }
        delete[] glacier[i];
    }
    delete[] glacier;
    glacier = NULL;
    for (Block* block : icicles) {
        if (block != NULL) {
            delete block;
            block = NULL;
        }
    }
}



void Labyrinth::Update(float deltaTime) {


    for (int i=0; i<int(size.x); i++)
        for (int j=0; j<int(size.y); j++)
            if (glacier[i][j] != NULL) {
                if (glacier[i][j]->getCanCollide()) {
                    sf::Vector2i _pos = glacier[i][j]->getDirection();
                    int _x, _y;
std::cout << "holaaasssssssssssssssss" << std::endl;
std::cout << i << " " << j << std::endl;
std::cout << _pos.x+i << " " << _pos.y+j << std::endl;
std::cout << _pos.x*2+i << " " << _pos.y*2+j << std::endl;
                    glacier[i][j]->dontCollide();
                    glacier[_pos.x+i][_pos.y+j] = glacier[i][j];
                    glacier[i][j] = NULL;
                    
                    _pos *= 2;
                    _x = _pos.x;
                    _y = _pos.y;
                    //if (_x < 0  ||  _x >= int(size.x-1)  ||  _y < 0  ||  _y >= int(size.y-1)) {
                    if (!this->checkPosition(_pos)) {
                        glacier[_x/2+i][_y/2+j]->setDirection(-1);
                        std::cout << "holaaa" << std::endl;
                    }
                    std::cout << "curiosos:" << int(size.x) << " "  << int(size.y) << std::endl;
                }
            }


    // Update each block...
    for (unsigned int i=0; i<size.x; i++)
        for (unsigned int j=0; j<size.y; j++)
            if (glacier[i][j]) {

                if (IceBlock* ice = dynamic_cast<IceBlock*>(glacier[i][j])) {
                    if (ice->getBreaking()) {
                        icicles.push_back(glacier[i][j]);
                        glacier[i][j] = NULL;
                    } else {
                        glacier[i][j]->Update(deltaTime);
                    }
                } else {
                    glacier[i][j]->Update(deltaTime);
                }
            }
/*
    for (unsigned int i=0; i<size.x; i++)
        for (unsigned int j=0; j<size.y; j++)
            if (glacier[i][j]) {
                sf::Vector2i _pos = glacier[i][j]->getPosition();

                // Set his position on labyrinth...
                if (_pos.x != int(i)  ||  _pos.y != int(j)) {
                    glacier[_pos.x][_pos.y] = glacier[i][j];
                //    glacier[i][j]           = NULL;
                }
            }*/

    // Delete the ice block falling...
    for (Block* block : icicles) {
        if (block != NULL) {
            if (IceBlock* ice = dynamic_cast<IceBlock*>(block)) {
                if (ice->getBroke()) {
                //    delete block;
                    block = NULL;
                } else {
                    block->Update(deltaTime);
                }
            }
        }
    }
}



void Labyrinth::Draw(sf::RenderWindow &window) {
    window.draw(*leftWall);
    window.draw(*rightWall);
    window.draw(*topWall);
    window.draw(*bottomWall);
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (glacier[i][j] != NULL)
                glacier[i][j]->Draw(window);
        }
    }

    for (Block* block : icicles) {
        if (block != NULL) {
            block->Draw(window);
        }
    }
}



bool Labyrinth::checkPosition(sf::Vector2i position) {
    bool _avaliable = false;
    int _x = position.x, _y = position.y;

    // Check the walls...
    if (_x >= 0  &&  _x < int(size.x)  &&  _y >= 0  &&  _y < int(size.y)) {
        if (glacier[_x][_y] == NULL) {
            _avaliable = true;
        }
    }

    return _avaliable;
}



void Labyrinth::pengoPush(sf::Vector2i position, int direction) {
    int _x = position.x, _y = position.y;

    // Check a block position...
    if (!this->checkPosition(position)  &&  _x >= 0  &&  _x < int(size.x)  &&  _y >= 0  &&  _y < int(size.y)) {
        sf::Vector2i _nextPosition = position;

        // Calculate the following position from block...
        if (direction == 0)
            _nextPosition.x--;
        else if (direction == 1)
            _nextPosition.y++;
        else if (direction == 2)
            _nextPosition.x++;
        else if (direction == 3)
            _nextPosition.y--;

        // Move the block or break it if cotains ice...
        if (this->checkPosition(_nextPosition)) {
            glacier[_x][_y]->setDirection(direction);
        } else if (IceBlock* ice = dynamic_cast<IceBlock*>(glacier[_x][_y])) {
            ice->breakDown();
        }
    }
}
