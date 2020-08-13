#pragma once

#include <SFML/Graphics.hpp>


#define WALL_REELING_DURATION 1.0f


class Wall {

    public:
        Wall(sf::Texture *,int );   // 0:Up - 1:Right - 2:Down - 3:Left
        ~Wall();
        void Update();
        void Draw(sf::RenderWindow &);
        void setReeling(bool );
        bool getReeling();



    private:
        sf::Sprite* sprite;
        bool isReeling;
        sf::Clock* reelingClock;
        float totalTime;
};