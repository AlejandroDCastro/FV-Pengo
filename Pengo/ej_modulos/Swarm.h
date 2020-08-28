#pragma once
#include <SFML/Graphics.hpp>
#include "SnoBee.h"
#include "Labyrinth.h"
#include "Pengo.h"
#include "Collision.h"


#define MAP_ROWS            15
#define MAP_COLUMNS         13
#define TOTAL_SNOWBEES      8
#define PLAY_SNOBEES        4
#define STAR_PLAY_STUN_TIME 6.5f
#define REELING_STUN_TIME   4.5f


class Swarm {


    public:
        Swarm(sf::Texture *,sf::Texture *,Labyrinth *);
        ~Swarm();
        void Update(float ,Labyrinth *,Pengo *,sf::Clock *);
        void Draw(sf::RenderWindow &);
        int getDeadSnobees();
        void stunSnoBees(float ,int ); // Direction of stun
        void addNextSnoBee(Labyrinth *);



    private:
        std::vector<SnoBee*> snobees;     // All the SnoBee playing with Pengo
        sf::Texture *texture;             // Texture for adding new SnoBee in swarm
        std::vector<IceBlock*> blocks;    // Ice Blocks that contains the SnoBee eggs

};