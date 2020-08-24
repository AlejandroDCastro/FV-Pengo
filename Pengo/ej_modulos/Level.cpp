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

    if (labyrinth->getPlayState() == active) {

        labyrinth->Update(deltaTime);

    } else {

        // When Pengo collides with a SnoBee all game gets frozen
        pengo->Update(deltaTime, labyrinth);
        if (!pengo->getStunned()  ||  (pengo->getGodMode() && pengo->getStunned())) { // In God Mode all game continue

            // Update all elements of functionality...
            labyrinth->Update(deltaTime);
            swarm->Update(deltaTime, labyrinth, pengo, restartClock);
        }

    }


    // Stun all Snobees after activating star play
    if (labyrinth->getPlayState() == active  &&  labyrinth->getStarPlayUsed()) {
        swarm->stunSnoBees(deltaTime, 4);
        labyrinth->setStarPlayState(0);
    } else if (labyrinth->getWallReeling() > -1) { // Stun using a wall
        swarm->stunSnoBees(deltaTime, labyrinth->getWallReeling());
    }
}



void Level::Draw(sf::RenderWindow &window) {
    labyrinth->Draw(window);
    swarm->Draw(window);
    pengo->Draw(window);
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
void Level::restart(float deltaTime) {
    delete labyrinth;
    delete swarm;

    labyrinth = new Labyrinth(tileset, map);
    swarm     = new Swarm(spriteSheet, labyrinth);
    pengo->restartInitialState(deltaTime);
}