#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Block.h"
#include "Character.h"
#include "Animation.h"
#include "IceBlock.h"
#include "Pengo.h"
#include "Labyrinth.h"
#include "Camera.h"
#include "SnoBee.h"
#include "Collision.h"



class Game {

    public:
        static Game* getInstance();


    protected:
        Game();
        ~Game();
        void GameLoop();
        void EventsLoop();
        void Draw();
        void addSwarm(int[15][13]);
        void addSnoBee();


    private:
        static Game* gameInstance;
        sf::RenderWindow* window;
        Camera* camera;
        Labyrinth* labyrinth1;
        Labyrinth* labyrinth2;
        Labyrinth* labyrinth;
        Pengo* pengo;
        sf::Clock clock;
     //   sf::Clock* levelClock;
        float deltaTime;
        sf::Event event;
        sf::Texture spriteSheet, tileset;
        sf::Vector2u size;
        std::vector<SnoBee*> swarm;
        unsigned int snoBeesPerLevel;
        Collision* collision;

};