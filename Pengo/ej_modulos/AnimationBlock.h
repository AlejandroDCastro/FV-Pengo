#pragma once

#include <SFML/Graphics.hpp>


#define BLOCK_SIZE 16


class AnimationBlock {
    
    public:
        AnimationBlock(sf::Texture *,sf::Vector2u );
        ~AnimationBlock();
        void Update(unsigned int ,float );
        sf::IntRect getUVRect();
        sf::Vector2f getOrigin();



    private:
        sf::IntRect* uvRect;
        float changeTime, totalTime;
        sf::Vector2u* actualCoord;   // Actual coordinates of rectangle
        sf::Vector2u* range;       // Block located on the tileset

};