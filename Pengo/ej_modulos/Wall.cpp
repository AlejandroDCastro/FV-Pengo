#include "Wall.h"




Wall::Wall(sf::Texture *texture, int side) {
    sprite       = new sf::Sprite(*texture);
    reelingClock = new sf::Clock();
    isReeling    = false;
    totalTime    = 0.0f;

    switch (side) {
        case 0:
            sprite->setTextureRect(sf::IntRect(0, 8, 224, 8));
            sprite->setPosition(0, 24);
            sprite->setOrigin(0, 4);
            sprite->setScale(1, -1);
            sprite->setOrigin(0, 8);
        //    sprite->setTextureRect(sf::IntRect(0, 0, 224, 8));
            break;

        case 1:
            sprite->setTextureRect(sf::IntRect(8, 16, 8, 256));
            sprite->setPosition(216, 24);
        //    sprite->setTextureRect(sf::IntRect(0, 16, 8, 256));
            break;

        case 2:
            sprite->setTextureRect(sf::IntRect(0, 8, 224, 8));
            sprite->setPosition(0, 272);
        //    sprite->setTextureRect(sf::IntRect(0, 0, 224, 8));
            break;
        
        default:
            sprite->setTextureRect(sf::IntRect(8, 16, 8, 256));
            sprite->setPosition(0, 24);
            sprite->setOrigin(4, 0);
            sprite->setScale(-1, 1);
            sprite->setOrigin(8, 0);
        //    sprite->setTextureRect(sf::IntRect(0, 16, 8, 256));
            break;
    }
}




Wall::~Wall() {
    delete sprite;
    delete reelingClock;
    sprite       = NULL;
    reelingClock = NULL;
}




void Wall::Update() {
    sf::IntRect _rectangle = sprite->getTextureRect();

    if (isReeling) {
        totalTime += reelingClock->getElapsedTime().asSeconds();

        // Animation ends...
        if (totalTime >= WALL_REELING_DURATION) {
            totalTime = 0.0f;
            this->setReeling(false);
        }

        // Set orientation to give a sensation of movement
        if (reelingClock->getElapsedTime().asSeconds() >= .2f) {
            if (_rectangle.top == 16)
                sprite->setScale(-1, 1);
            else
                sprite->setScale(1, -1);
        }
    }
}




void Wall::Draw(sf::RenderWindow &window) {
    window.draw(*sprite);
}




void Wall::setReeling(bool reeling) {
    sf::IntRect _rectangle = sprite->getTextureRect();

    if (reeling) {
        reelingClock->restart();
        if (_rectangle.left == 8)
            _rectangle.left = 0;
        else
            _rectangle.top = 0;
    } else {
        if (_rectangle.top == 16)
            _rectangle.left = 8;
        else
            _rectangle.top = 8;
    }

    sprite->setTextureRect(_rectangle);
    isReeling = reeling;
}





bool Wall::getReeling() {
    return isReeling;
}