#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"


#define TRAVEL_DISTANCE_OF_PENGO 16.f
#define INITIAL_POSITION_X_Y     6
#define BLOCK_SIZE               16


class Pengo : public Character {
    
    private:
        unsigned int lifes;
        sf::Clock auxClock;
        Animation *deadAnimation;
        bool isBlocked;
        bool push;
        bool godMode;
        float stunnedTime;

  
    public:
        Pengo(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i);
        ~Pengo();
        void Update(float ,Labyrinth* );
        void UpdateMovement(int, Labyrinth* );       // 0:Up - 1:Right - 2:Down - 3:Left - 4:Push
        bool loseLife();
        bool getDead();
        void restartInitialPosition();
        void restoreLifes();
        void changeGodMode(sf::RenderWindow* ,float );
        bool getGodMode();
        void restartPosition();
  
};
