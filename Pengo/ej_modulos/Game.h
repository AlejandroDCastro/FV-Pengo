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



class Game {

    public:
        static Game* getInstance();


    protected:
        Game();
        ~Game();
        void GameLoop();
        void EventsLoop();
        void Draw();


    private:
        static Game* gameInstance;
        sf::RenderWindow* window;
        Camera* camera;
        Labyrinth* labyrinth;
        Pengo* pengo;
        sf::Clock clock;
        float deltaTime;
        sf::Event event;
        sf::Texture spriteSheet;
        sf::Texture tileset;
        SnoBee *abeja;

};