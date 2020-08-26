#pragma once

#include <SFML/Graphics.hpp>


#define BLOCK_SIZE 16


class StaticAnimation {     // Used for block and birth snobee animation
    
    public:
        StaticAnimation(sf::Texture *,float ,sf::Vector2u ,sf::Vector2u );
        ~StaticAnimation();
        void Update(unsigned int ,float );
        sf::IntRect getUVRect();
        sf::Vector2f getOrigin();
        void setRange(unsigned int ,unsigned int );
        void setChangeTime(float );



    private:
        sf::IntRect* uvRect;
        float changeTime, totalTime;
        sf::Vector2u *actualCoord;   // Actual coordinates of rectangle
        sf::Vector2u range;          // Block located on the tileset

};