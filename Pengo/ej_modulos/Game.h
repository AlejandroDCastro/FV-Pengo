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
#include "Swarm.h"
#include "Level.h"


#define TOTAL_LEVELS            16
#define RESTART_TRANSITION_TIME 2.5f



///////////////////////   EXECUTE ALL COMMANDS AT THE SAME TIME   //////////////////////
/**
 * alias do="cmake -H. -Bbuild && cd build/ && make && mv Pengo .. && cd .. && ./Pengo"
 * do
 **/



// States during the game
enum State { play, stun, next };



class Game {    // Control the level change

    public:
        static Game* getInstance();


    protected:
        Game();
        ~Game();
        void GameLoop();
        void EventsLoop();
        void Render();


    private:
        static Game* gameInstance;
        sf::RenderWindow* window;
        sf::Texture tileset, spriteSheet;
        sf::Clock* restartLevelClock;
        State state;
        Camera* camera;
        Pengo* pengo;
        sf::Clock clock;
        sf::Clock levelClock;
        float deltaTime;
        sf::Event event;
        Level* level;
        std::vector<Level*> levels;      // In the same game levels are the same
        unsigned int currentLevel;

};