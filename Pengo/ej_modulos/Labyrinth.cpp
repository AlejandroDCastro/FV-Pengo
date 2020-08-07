#include "Labyrinth.h"



Labyrinth::Labyrinth(sf::Texture *tileset, int **map) {
    isHit = false;

    // Build the walls and put them on screen...
    leftWall   = new sf::Sprite(*tileset);
    rightWall  = new sf::Sprite(*tileset);
    topWall    = new sf::Sprite(*tileset);
    bottomWall = new sf::Sprite(*tileset);
    
    // Set the texture for each wall
    leftWall->setTextureRect(sf::IntRect(8, 16, 8, 256));
    rightWall->setTextureRect(sf::IntRect(8, 16, 8, 256));
    topWall->setTextureRect(sf::IntRect(0, 8, 224, 8));
    bottomWall->setTextureRect(sf::IntRect(0, 8, 224, 8));

    // Set their positions
    leftWall->setPosition(0, 24);
    leftWall->setOrigin(4, 0);
    leftWall->setScale(-1, 1);
    leftWall->setOrigin(8, 0);
    rightWall->setPosition(216, 24);
    topWall->setPosition(0, 24);
    topWall->setOrigin(0, 4);
    topWall->setScale(1, -1);
    topWall->setOrigin(0, 8);
    bottomWall->setPosition(0, 272);

    // Reserve momory for the matrix...
    size.x = 15;  size.y = 13;
    glacier = new Block**[size.x];
    for (unsigned int i=0; i<size.x; i++)
        glacier[i] = new Block*[size.y];
    
    // Put all the ice blocks as dynamic objects...
    for (unsigned int i=0; i<size.x; i++)
        for (unsigned int j=0; j<size.y; j++) {
            if (map[i][j] == 1)
                glacier[i][j] = new IceBlock(tileset, j, i);
            else if (map[i][j] == 2)
                glacier[i][j] = new DiamondBlock(tileset, j, i);
            else
                glacier[i][j] = NULL;
        }

    // Important position...
    for (int i=0; i<int(size.x); i++)
        for (int j=0; j<int(size.y); j++)
            if (glacier[i][j])
                glacier[i][j]->setPosition(sf::Vector2i(i, j));

}



Labyrinth::~Labyrinth() {
    delete leftWall;
    delete rightWall;
    delete topWall;
    delete bottomWall;
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (glacier[i][j])
                delete glacier[i][j];
        }
        delete[] glacier[i];
    }
    delete[] glacier;
    for (Block* block : icicles) {
        if (block != NULL) {
            delete block;
            block = NULL;
        }
    }
    icicles.clear();
    rightWall  = NULL;
    bottomWall = NULL;
    leftWall   = NULL;
    topWall    = NULL;
    glacier    = NULL;
}



void Labyrinth::Update(float deltaTime) {

    // Update the position for each block...
    for (int i=0; i<int(size.x); i++)
        for (int j=0; j<int(size.y); j++)
            if (glacier[i][j]  &&  glacier[i][j]->getCanCollide()) {
                sf::Vector2i _pos = glacier[i][j]->getPosition();
                int _x = _pos.x, _y = _pos.y;

                if (i != _x  ||  j != _y) {
                    glacier[_x][_y] = glacier[i][j];
                    glacier[i][j]   = NULL;
                }
                
            }


    // Update each block...
    for (unsigned int i=0; i<size.x; i++)
        for (unsigned int j=0; j<size.y; j++)
            if (glacier[i][j]) {

                if (glacier[i][j]->getCanCollide()) {
                    sf::Vector2i _pos = glacier[i][j]->getPosition();

                    this->pengoPush(_pos, glacier[i][j]->getDirection(), false);
                    glacier[i][j]->dontCollide();
                }
                glacier[i][j]->Update(deltaTime);
            }


    // Delete the ice block falling...
    for (Block* block : icicles) {
        if (block) {
            if (IceBlock* ice = dynamic_cast<IceBlock*>(block)) {
                if (ice->getBroke()) {
                 //   delete block;
                    block = NULL;
                } else {
                    block->Update(deltaTime);
                }
            }
        }
    }
}



void Labyrinth::Draw(sf::RenderWindow &window) {
    window.draw(*leftWall);
    window.draw(*rightWall);
    window.draw(*topWall);
    window.draw(*bottomWall);
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (glacier[i][j])
                glacier[i][j]->Draw(window);
        }
    }

    for (Block* block : icicles) {
        if (block) {
            if (IceBlock* ice = dynamic_cast<IceBlock*>(block))
                if (!ice->getBroke())
                    block->Draw(window);
        }
    }
}



bool Labyrinth::checkPosition(sf::Vector2i position) {
    bool _avaliable = false;
    int _x = position.x, _y = position.y;

    // Check the walls...
    if (_x >= 0  &&  _x < int(size.x)  &&  _y >= 0  &&  _y < int(size.y)) {
        if (glacier[_x][_y] == NULL) {
            _avaliable = true;
        }
    }

    return _avaliable;
}



void Labyrinth::pengoPush(sf::Vector2i position, int direction, bool breakIt) {
    int _x = position.x, _y = position.y;

    // Check a block position...
    if (!this->checkPosition(position)  &&  _x >= 0  &&  _x < int(size.x)  &&  _y >= 0  &&  _y < int(size.y)) {
        sf::Vector2i _next_position = position;

        // Calculate the following position from block...
        if (direction == 0)
            _next_position.x--;
        else if (direction == 1)
            _next_position.y++;
        else if (direction == 2)
            _next_position.x++;
        else if (direction == 3)
            _next_position.y--;

        // Move the block or break it if cotains ice or dont break it if contains diamond...
        if (this->checkPosition(_next_position)) {
            glacier[_x][_y]->setDirection(direction);
        } else {
            if (IceBlock* ice = dynamic_cast<IceBlock*>(glacier[_x][_y])) {
                if (breakIt) {
                    ice->breakDown();
                    icicles.push_back(glacier[_x][_y]);
                    glacier[_x][_y] = NULL;
                } else {
                    glacier[_x][_y]->setDirection(-1);
                }
            } else { // Its a diamond block
                glacier[_x][_y]->setDirection(-1);
            }
        }
    }
}




Block* Labyrinth::getBlock(unsigned int x, unsigned int y) {
    return glacier[x][y];
}




// Free position for including SnoBees into the map
sf::Vector2i Labyrinth::getFreePosition() {
    sf::Vector2i _free_position(0, 0);

    do {
        _free_position.x = rand()%15,
        _free_position.y = rand()%13;
    } while (!this->checkPosition(_free_position));

    return _free_position;
}




DiamondBlock** Labyrinth::getDiamondBlocks() {
    DiamondBlock **diamonds = new DiamondBlock*[TOTAL_DIAMOND_BLOCK];


}