#pragma once

#include "DiamondBlock.h"


#define TOTAL_DIAMOND_BLOCK 3


class StarPlay {

    public:
        StarPlay();
        ~StarPlay();


    private:
        DiamondBlock **diamonds;
        
};