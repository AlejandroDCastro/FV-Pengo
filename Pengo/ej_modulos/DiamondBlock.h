#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"


#define TOTAL_DIAMOND_BLOCK



class DiamondBlock : public Block {

    public:
        DiamondBlock(sf::Texture* ,unsigned int ,unsigned int );
        ~DiamondBlock();
        void Update(float deltaTime);


    private:

};