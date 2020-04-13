#pragma once
#include <SFML/Graphics.hpp>


class Labyrinth {

    private:
        sf::Sprite *leftWall;
        sf::Sprite *rightWall;
        sf::Sprite *topWall;
        sf::Sprite *bottomWall;
        bool isHit;


    public:
        Labyrinth(sf::Texture* texture);
        ~Labyrinth();
     //   void getHit();
        void Draw(sf::RenderWindow &);

};