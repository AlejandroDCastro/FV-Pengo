#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"



class DiamondBlock : public Block {

    public:
        DiamondBlock(sf::Texture* ,unsigned int ,unsigned int );
        ~DiamondBlock();
        void Update(float deltaTime);


    private:

};