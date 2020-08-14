#pragma once

#include <SFML/Graphics.hpp>


#define WALL_REELING_DURATION 2.0f
#define WALL_REELING_CHANGE   0.15f


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