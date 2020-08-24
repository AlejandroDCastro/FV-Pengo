#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "Character.h"
#include "Pengo.h"


#define TRAVEL_DISTANCE_OF_BLOCK 16.f
#define HIGH_PROBABILITY         3
#define MEDIUM_PROBABILITY       3
#define LOW_PROBABILITY          3



class SnoBee : public Character {

    public:
        SnoBee(sf::Texture *,float ,float ,sf::Vector2u ,sf::Vector2i );
        ~SnoBee();
        void Update(float ,Labyrinth *,Pengo *);
        void collideBlock(Block* );
        bool getFree();
        bool getDead();
        void getKilled();
        bool getSmashed();
        void setOrientation(int );
        void setPosition(int );
        void stunSnoBee(float ,float );


    private:
        int direction; // 0:Up - 1:Right - 2:Down - 3:Left
        bool isStatic;
        bool isDead;
        Block *bomb;
        Pengo *pengo;
        sf::Clock *stunClock;
        float stunTime;
};