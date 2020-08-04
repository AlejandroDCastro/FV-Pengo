#include "Level.h"



Level::Level(sf::Texture* spriteSheet, sf::Texture* tileset, Pengo* pengo, sf::Clock* restartClock) {

    labyrinth          = new Labyrinth(tileset);
    swarm              = new Swarm(spriteSheet, labyrinth);
    this->pengo        = pengo;
    this->restartClock = restartClock;
}



Level::~Level() {
    delete swarm;
    delete labyrinth;
    swarm        = NULL;
    labyrinth    = NULL;
    pengo        = NULL;
    restartClock = NULL;
}



void Level::Update(float deltaTime) {

    // When Pengo collides with a SnoBee all game gets frozen
    pengo->Update(deltaTime, labyrinth);
    if (!pengo->getStunned()) {

        // Update all elements of functionality...
        labyrinth->Update(deltaTime);
        swarm->Update(deltaTime, labyrinth, pengo, restartClock);
    }
}



void Level::Draw(sf::RenderWindow &window) {
    pengo->Draw(window);
    labyrinth->Draw(window);
    swarm->Draw(window);
}




bool Level::completed() {

    if (swarm->getDeadSnobees() == TOTAL_SNOWBEES)
        return true;
    else
        return false;
}




// Set Pengo direction
void Level::inputPlayer(int direction) {
    pengo->UpdateMovement(direction, labyrinth);
}




void Level::restart() {
    delete swarm;
    swarm = NULL;
    swarm = new Swarm();
}