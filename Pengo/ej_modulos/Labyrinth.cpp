#include "Labyrinth.h"



Labyrinth::Labyrinth(sf::Texture* texture) {
    isHit = false;

    // Build the walls and put them on screen...
    leftWall   = new sf::Sprite(*texture);
    rightWall  = new sf::Sprite(*texture);
    topWall    = new sf::Sprite(*texture);
    bottomWall = new sf::Sprite(*texture);

    leftWall->setTextureRect(sf::IntRect(16, 32, 16, 512));
    rightWall->setTextureRect(sf::IntRect(16, 32, 16, 512));
    topWall->setTextureRect(sf::IntRect(0, 16, 448, 16));
    bottomWall->setTextureRect(sf::IntRect(0, 16, 448, 16));

    leftWall->setPosition(0, 48);
    leftWall->setOrigin(8, 0);
    leftWall->setScale(-1, 1);
    leftWall->setOrigin(16, 0);
    rightWall->setPosition(432, 48);
    topWall->setPosition(0, 48);
    topWall->setOrigin(0, 8);
    topWall->setScale(1, -1);
    topWall->setOrigin(0, 16);
    bottomWall->setPosition(0, 544);


    // Reserve momory for the matrix...
    size.x = 13;  size.y = 15;
    glacier = new IceBlock**[size.x];
    for (unsigned int i=0; i<size.x; i++) {
        glacier[i] = new IceBlock*[size.y];
    }

    int alex[size.y][size.x] = {
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
            if (alex[j][i] == 1) {
                glacier[i][j] = new IceBlock(texture, i, j);
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
}


/*
void Labyrinth::getHit() {

    if (!isHit) {

    }
}
*/


void Labyrinth::Draw(sf::RenderWindow &window) {
    window.draw(*leftWall);
    window.draw(*rightWall);
    window.draw(*topWall);
    window.draw(*bottomWall);
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (glacier[i][j])
                glacier[i][j]->Draw(window);
        }
    }
}