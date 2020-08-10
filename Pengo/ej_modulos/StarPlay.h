#pragma once

#include <math.h>
#include "DiamondBlock.h"


#define TOTAL_DIAMOND_BLOCK 3


enum PlayState { inactive, half, active };

class StarPlay {

    public:
        StarPlay(DiamondBlock **);
        ~StarPlay();
        void Update();
        PlayState getPlayState();


    private:
        DiamondBlock **diamonds;
        PlayState state;
       // sf::Clock *clockColor;
        bool used;
        
};