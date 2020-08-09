#pragma once

#include <math.h>
#include "DiamondBlock.h"
#include "Labyrinth.h"


#define TOTAL_DIAMOND_BLOCK 3


enum PlayState { inactive, half, active };

class StarPlay {

    public:
        StarPlay(Labyrinth *);
        ~StarPlay();
        void Update();


    private:
        DiamondBlock **diamonds;
        PlayState state;
        sf::Clock *clockColor;
        bool used;
        
};