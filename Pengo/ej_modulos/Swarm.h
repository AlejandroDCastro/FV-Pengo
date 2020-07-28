#pragma once

#include <SFML/Graphics.hpp>
#include "SnoBee.h"
#include "Labyrinth.h"
#include "Pengo.h"


#define MAP_ROWS    15
#define MAP_COLUMNS 13


class Swarm {


    public:
        Swarm(sf::Texture* ,int[MAP_ROWS][MAP_COLUMNS] );
        ~Swarm();
        void Update(float ,Labyrinth* );
        void addSnoBee(sf::Vector2i );   // The new free position...



    private:
        std::vector<SnoBee*> snobees;     // All the SnoBee playing with Pengo
        sf::Texture* texture;           // Texture for addinn new SnoBee in swarm


};