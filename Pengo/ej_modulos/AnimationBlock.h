#pragma once

#include <SFML/Graphics.hpp>



class AnimationBlock {
    
    public:
        AnimationBlock(sf::Texture *,sf::Vector2u ,float );
        ~AnimationBlock();



    private:
        sf::IntRect uvRect;
        float changeTime, totalTime;
        sf::Vector2u actualCoord;   // Actual coordinates of rectangle
        sf::Vector2u coordPj;       // Block located on the tileset

};