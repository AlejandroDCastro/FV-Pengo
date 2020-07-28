#include "Swarm.h"



Swarm::Swarm(sf::Texture* texture, int level[MAP_ROWS][MAP_COLUMNS]) {

    this->texture = texture;

    // Create swarm with all SnoBees
    for (int i=0; i<MAP_ROWS; i++)
        for (int j=0; j<MAP_COLUMNS; j++)
            if (level[i][j] == 2)
                snobees.push_back(new SnoBee(texture, 45.0f, 0.2f, sf::Vector2u(0, 2), sf::Vector2i(i, j)));


}



Swarm::~Swarm() {
    for (SnoBee* snobee : snobees)
        delete snobee;
    snobees.clear();
}




void Swarm::Update(float deltaTime, Labyrinth* labyrinth) {

    for (SnoBee* snobee : snobees)
        if (snobee  &&  !snobee->getDead())
            snobee->Update(deltaTime, labyrinth);

}




void Swarm::addSnoBee(sf::Vector2i _new_position) {

    snobees.push_back(new SnoBee(texture, 45.0f, 0.2f, sf::Vector2u(0, 2), _new_position));
}