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
}