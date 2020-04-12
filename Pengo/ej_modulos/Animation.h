#pragma once
#include <SFML/Graphics.hpp>

class Animation {

    public:
        sf::IntRect uvRect;
        float changeTime;
        float totalTime;
        sf::Vector2u actualCoord;   // Actual coordinates of rectangle
        sf::Vector2u coordPj;       // Pj located on the texture
        bool change;                // Change the rectangle


    private:
        Animation(sf::Texture *texture, sf::Vector2u coordPj, float changeTime);
        ~Animation();
        void Update(unsigned int row, unsigned int column, float deltaTime);
        sf::IntRect getUVRect();
        sf::Vector2f getOrigin();
};
