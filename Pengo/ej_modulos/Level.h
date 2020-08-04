#pragma once

#include <SFML/Graphics.hpp>
#include "Swarm.h"
#include "Labyrinth.h"


class Level {

    public:
        Level(sf::Texture *,sf::Texture *,Pengo *,sf::Clock *);
        ~Level();
        void Update(float );
        void Draw(sf::RenderWindow &);
        bool completed();
        void inputPlayer(int );
        void restart();


    private:
        Swarm* swarm;
        Labyrinth* labyrinth;
        Pengo* pengo;
        sf::Clock* restartClock;
};