#pragma once

#include <SFML/Graphics.hpp>
#include "Swarm.h"




class Level {

    public:
        Level(int[15][13] );
        ~Level();
        void Update(float );

    private:
        Swarm swarm;
        Labyrinth* labyrinth;


};