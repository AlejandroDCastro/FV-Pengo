#pragma once
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
        
};