#pragma once

#include <SFML/Graphics.hpp>
#include "SnoBee.h"
#include "Labyrinth.h"
#include "Pengo.h"
#include "Collision.h"


#define MAP_ROWS       15
#define MAP_COLUMNS    13
#define TOTAL_SNOWBEES 8
#define PLAY_SNOBEES   4


class Swarm {


    public:
        Swarm(sf::Texture *,Labyrinth *);
        ~Swarm();
        void Update(float ,Labyrinth *,Pengo *,sf::Clock *);
        void Draw(sf::RenderWindow &);
        int getDeadSnobees();



    private:
        std::vector<SnoBee*> snobees;     // All the SnoBee playing with Pengo
        sf::Texture* texture;             // Texture for adding new SnoBee in swarm


};