#include "Level.h"



Level::Level(sf::Texture* spriteSheet, sf::Texture* tileset, Pengo* pengo, sf::Clock* restartClock) {

    // Generate the random maze
    map = new int*[MAP_ROWS];
    for (unsigned int i=0; i<MAP_ROWS; i++)
        map[i] = new int[MAP_COLUMNS];
    MazeGenerator::generateRandomMaze(map);

    // Create whole level
    labyrinth          = new Labyrinth(tileset, map);
    swarm              = new Swarm(spriteSheet, labyrinth);
    this->pengo        = pengo;
    this->restartClock = restartClock;
    this->spriteSheet  = spriteSheet;
    this->tileset      = tileset;
}



Level::~Level() {
    for (unsigned int i=0; i<MAP_ROWS; i++)
        delete[] map[i];
    delete[] map;
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
    if (!pengo->getStunned()  ||  (pengo->getGodMode() && pengo->getStunned())) { // In God Mode all game continues

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




// Restart all level structure less the Snobees position
void Level::restart() {
    delete labyrinth;
    delete swarm;

    labyrinth = new Labyrinth(tileset, map);
    swarm     = new Swarm(spriteSheet, labyrinth);
}