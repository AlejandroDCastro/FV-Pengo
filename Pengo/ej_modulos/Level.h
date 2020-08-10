#pragma once

#include <SFML/Graphics.hpp>
#include "Swarm.h"
#include "Labyrinth.h"
#include "MazeGenerator.h"



class Level {

    public:
        Level(sf::Texture *,sf::Texture *,Pengo *,sf::Clock *);
        ~Level();
        void Update(float );
        void Draw(sf::RenderWindow &);
        bool completed();
        void inputPlayer(int );
        void restart(float );


    private:
        Swarm* swarm;
        Labyrinth* labyrinth;
        Pengo* pengo;
        sf::Clock* restartClock;
        sf::Texture *spriteSheet, *tileset;
        int **map;  // Maze structure
};