#pragma once
#include <SFML/Graphics.hpp>

class Animation {

    private:
        sf::IntRect uvRect;
        float changeTime;
        float totalTime;
        sf::Vector2u actualCoord;   // Actual coordinates of rectangle
        sf::Vector2u coordPj;       // Pj located on the texture
        sf::Vector2u range;         // Number of rectangle to draw


    public:
        Animation(sf::Texture *texture, sf::Vector2u coordPj, float changeTime, int numSprites);
        ~Animation();
        void Update(unsigned int row, unsigned int column, float deltaTime);
        sf::IntRect getUVRect();
        sf::Vector2f getOrigin();
        void setChangeTime(float changeTime);
};
