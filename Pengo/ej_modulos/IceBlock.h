#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Egg.h"


class IceBlock : public Block {

    public:
        IceBlock(sf::Texture* ,unsigned int ,unsigned int );
        ~IceBlock();
        void Update(float deltaTime);
        void breakDown();
        bool getBroke();
        bool getBreaking();
        void setActived(bool );
        void incubateEgg(sf::Texture *,sf::Texture *,Labyrinth *);
        Egg* getEgg();


    private:
        bool isBreaking;
        bool isBroke;
        sf::Clock clock;    // Clock for breaking animation
        Egg *egg;
};
