#include "Swarm.h"




Swarm::Swarm(sf::Texture *spriteSheet, sf::Texture *tileset, Labyrinth *labyrinth) {
    sf::Vector2i _position;
    IceBlock *block = NULL;

    // Create swarm with all SnoBees
    for (int i=0; i<TOTAL_SNOWBEES; i++) {
        block = labyrinth->incubateEgg(tileset);
        blocks.push_back(block);
        if (i < 4) {
            labyrinth->breakIceBlock(block->getPosition());
            snobees.push_back(block->getEgg()->getSnoBee());
        }
    }

    texture = tileset;
}



Swarm::~Swarm() {
    for (SnoBee *snobee : snobees)
        delete snobee;
    snobees.clear();
    for (IceBlock *block : blocks)
        delete block;
    blocks.clear();
    texture = NULL;
}




void Swarm::Update(float deltaTime, Labyrinth* labyrinth, Pengo* pengo, sf::Clock* restartClock) {

    // Tambien hay que hacer que el snobee no rompa un hielo donde esta su hermano jejeje


    // Update all snobees...
    for (SnoBee* snobee : snobees) {
        if (snobee  &&  !snobee->getDead()) {
            snobee->Update(deltaTime, labyrinth, pengo);

            if (snobee->getGrownUp()) {

                if (snobee->getSmashed()) {

                    // If SnoBee get dead add other one on a free position
                    if (snobee->getDead()  &&  snobees.size() < TOTAL_SNOWBEES)
                        this->addNextSnoBee(labyrinth);

                } else {

                    // Check collision Snobee-Pengo
                    if (Collision::checkCollision(snobee->getSprite(), pengo->getSprite(), 10.0f)) {
                        
                        // If snobee is stunned then pengo kills him
                        if (snobee->getStunned()) {
                            snobee->getKilled();
                            if (snobees.size() < TOTAL_SNOWBEES)
                                this->addNextSnoBee(labyrinth);
                        } else {
                            pengo->loseLife();
                            restartClock->restart();    // Clock for restarting current level
                        }
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





void Swarm::stunSnoBees(float deltaTime, int side) {
    int _snobee_position, _reeling_position;

    for (SnoBee *snobee : snobees) {
        if (side == 4  &&  !snobee->getStunned()) {    // Stun all snobees...
            snobee->stunSnoBee(STAR_PLAY_STUN_TIME);
        } else {            // Stun snobee next to the wall
            if (side == 0) {
                _snobee_position  = snobee->getPosition().x;
                _reeling_position = 0;
            } else if (side == 1) {
                _snobee_position  = snobee->getPosition().y;
                _reeling_position = MAP_COLUMNS-1;
            } else if (side == 2) {
                _snobee_position  = snobee->getPosition().x;
                _reeling_position = MAP_ROWS-1;
            } else if (side == 3) {
                _snobee_position  = snobee->getPosition().y;
                _reeling_position = 0;
            }
            
            if (_snobee_position == _reeling_position  &&  !snobee->getStunned()  &&  snobee->getPath() == 0.0f)
                snobee->stunSnoBee(REELING_STUN_TIME);
        }
    }
}





void Swarm::addNextSnoBee(Labyrinth *labyrinth) {
    for (IceBlock *block : blocks)
        if (!block->getBroke()) {
            labyrinth->breakIceBlock(block->getPosition());
            snobees.push_back(block->getEgg()->getSnoBee());
            break;
        }
}