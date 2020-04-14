#pragma once
#include <SFML/Graphics.hpp>


class IceBlock {

    private:
        sf::Sprite *block;
        bool isBreaking;
        bool isBroke;
        float speed;            // Speed of movement
        int direction;          // Direction of displacement
        sf::Clock clock;

    public:
        IceBlock(sf::Texture* texture, unsigned int x, unsigned int y);
        ~IceBlock();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        void breakDown();
        bool getBroke();
        void setDirection(int direction);
};