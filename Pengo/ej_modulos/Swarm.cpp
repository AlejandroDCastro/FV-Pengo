#include "Swarm.h"



Swarm::Swarm(sf::Texture* texture, Labyrinth* labyrinth) {
    sf::Vector2i _position;

    // Create swarm with all SnoBees
    for (int i=0; i<PLAY_SNOBEES; i++) {
        do {
            _position = labyrinth->getFreePosition();
        } while (_position.x == 6  &&  _position.y == 6);
        snobees.push_back(new SnoBee(texture, 57.5f, 0.15f, sf::Vector2u(0, 2), _position));
    }

    this->texture = texture;
}



Swarm::~Swarm() {
    for (SnoBee* snobee : snobees)
        delete snobee;
    snobees.clear();
    texture = NULL;
}




void Swarm::Update(float deltaTime, Labyrinth* labyrinth, Pengo* pengo, sf::Clock* restartClock) {

    for (SnoBee* snobee : snobees) {
        if (snobee  &&  !snobee->getDead()) {
            snobee->Update(deltaTime, labyrinth, pengo);

            if (snobee->getSmashed()) {

                // If SnoBee get dead add other one on a free position
                if (snobee->getDead()  &&  snobees.size() < TOTAL_SNOWBEES)
                    snobees.push_back(new SnoBee(texture, 57.5f, 0.15f, sf::Vector2u(0, 2), labyrinth->getFreePosition()));

            } else {

                // Check collision Snobee-Pengo
                if (Collision::checkCollision(snobee->getSprite(), pengo->getSprite(), 10.0f)) {
                    pengo->loseLife();
                    restartClock->restart();    // Clock for restarting current level
                }

                // Check collision Snobee-block
                for (unsigned int i=0; i<MAP_ROWS; i++) {
                    Block* _block;
                    for (unsigned int j=0; j<MAP_COLUMNS; j++) {
                        _block = labyrinth->getBlock(i, j);

                        // Smash Sno-Bee
                        if (_block  &&  _block->getDirection() > -1  &&  snobee->getFree()  &&  Collision::checkCollision(_block->getSprite(), snobee->getSprite(), 20.f))
                            snobee->collideBlock(_block);
                        _block = NULL;
                    }
                }

            }
            
        }
    }

}




void Swarm::Draw(sf::RenderWindow &window) {
    for (SnoBee* snobee : snobees)
        if (snobee  &&  !snobee->getDead())
            snobee->Draw(window);
}



int Swarm::getDeadSnobees() {
    int _deaths = 0;

    if (snobees.size() == TOTAL_SNOWBEES)   // Check to optimize...
        for (SnoBee* snobee : snobees)
            if (snobee  &&  snobee->getDead())
                _deaths++;

    return _deaths;
}