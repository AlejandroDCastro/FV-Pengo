#pragma once

#include <SFML/Graphics.hpp>
#include "Swarm.h"




class Level {

    public:
        Level();
        ~Level();
        void Update(float );

    private:
        Swarm swarm;


};