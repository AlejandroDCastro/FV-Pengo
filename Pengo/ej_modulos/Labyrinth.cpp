#include "Labyrinth.h"



Labyrinth::Labyrinth(sf::Texture *tileset, int **map) {
    DiamondBlock **_diamonds;
    int _cont = 0;

    isHit = false;

    // Build the walls and put them on screen...
    leftWall   = new Wall(tileset, 3);
    rightWall  = new Wall(tileset, 1);
    topWall    = new Wall(tileset, 0);
    bottomWall = new Wall(tileset, 2);

    // Reserve memory for block matrix...
    size.x = 15;  size.y = 13;
    glacier = new Block**[size.x];
    for (unsigned int i=0; i<size.x; i++)
        glacier[i] = new Block*[size.y];

    // Reserve memory for diamonds blocks...
    _diamonds = new DiamondBlock*[TOTAL_DIAMOND_BLOCK];
    
    // Put all the ice blocks as dynamic objects...
    DiamondBlock* diamond;
    for (unsigned int i=0; i<size.x; i++)
        for (unsigned int j=0; j<size.y; j++) {
            if (map[i][j] == 1) {
                glacier[i][j] = new IceBlock(tileset, j, i);
            } else if (map[i][j] == 2) {
                glacier[i][j] = new DiamondBlock(tileset, j, i);
                diamond = dynamic_cast<DiamondBlock*>(glacier[i][j]);
                _diamonds[_cont++] = diamond;
            } else {
                glacier[i][j] = NULL;
            }
        }

    // Important position...
    for (int i=0; i<int(size.x); i++)
        for (int j=0; j<int(size.y); j++)
            if (glacier[i][j])
                glacier[i][j]->setPosition(sf::Vector2i(i, j));

    // Create the star play of level
    starPlay = new StarPlay(_diamonds);

}



Labyrinth::~Labyrinth() {
    delete leftWall;
    delete rightWall;
    delete topWall;
    delete bottomWall;
    delete starPlay;
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
    starPlay   = NULL;
    glacier    = NULL;
}



void Labyrinth::Update(float deltaTime) {

    // Check diamonds position...
    starPlay->Update();


    // Update all walls
    leftWall->Update();
    rightWall->Update();
    topWall->Update();
    bottomWall->Update();
    

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

                // Change the block color for star play...
                if (starPlay->getPlayState() == active  &&  !glacier[i][j]->getActived())
                    glacier[i][j]->setActived(true);
                else if (starPlay->getPlayState() == inactive  &&  glacier[i][j]->getActived())
                    glacier[i][j]->setActived(false);

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
    leftWall->Draw(window);
    bottomWall->Draw(window);
    rightWall->Draw(window);
    topWall->Draw(window);
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
    if (this->checkLimit(position)) {
        if (!this->checkPosition(position)) {
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

    } else { // Push a wall...

        if (_x < 0  &&  !topWall->getReeling())
            topWall->setReeling(true);
        else if (_y < 0  &&  !leftWall->getReeling())
            leftWall->setReeling(true);
        else if (_x >= int(size.x)  &&  !bottomWall->getReeling())
            bottomWall->setReeling(true);
        else if (_y >= int(size.y)  &&  !rightWall->getReeling())
            rightWall->setReeling(true);
    }
}




// Return if can break the block
bool Labyrinth::snobeePush(sf::Vector2i position) {
    int _x = position.x, _y = position.y;
    bool _breakIt = false;

    if (_x >= 0  &&  _x < int(size.x)  &&  _y >= 0  &&  _y < int(size.y)  &&  glacier[_x][_y])
        if (IceBlock* ice = dynamic_cast<IceBlock*>(glacier[_x][_y])) {
            ice->breakDown();
            icicles.push_back(glacier[_x][_y]);
            glacier[_x][_y] = NULL;
            _breakIt = true;
        }

    return _breakIt;
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




PlayState Labyrinth::getPlayState() {
    return starPlay->getPlayState();
}




// True --> avaliable position
bool Labyrinth::checkLimit(sf::Vector2i position) {
    bool _avaliable = true;

    if (position.x < 0  ||  position.y < 0  ||  position.x >= int(size.x)  ||  position.y >= int(size.y))
        _avaliable = false;
    else if (DiamondBlock* diamond = dynamic_cast<DiamondBlock*>(glacier[position.x][position.y]))
        _avaliable = false;

    return _avaliable;
}