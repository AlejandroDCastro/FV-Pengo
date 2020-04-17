#pragma once
#include <SFML/Graphics.hpp>
#include "Pengo.h"
#include "Labyrinth.h"
#include "Camera.h"



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
        static Game* game;
        

};