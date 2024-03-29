#include "StarPlay.h"




StarPlay::StarPlay(DiamondBlock **blocks) {
    diamonds   = blocks;
    state      = inactive;
    used       = false;
    colorClock = new sf::Clock();
}




StarPlay::~StarPlay() {
    for (unsigned int i=0; i<TOTAL_DIAMOND_BLOCK; i++)
        diamonds[i] = NULL;
    delete[] diamonds;
    delete colorClock;
    colorClock = NULL;
}




// Check if the blocks are continuous to activate star play
void StarPlay::Update() {
    int _distance[3][2];
    DiamondBlock *_block1, *_block2;
    sf::Vector2i _pos1, _pos2, _sum_distance;

    if (!used) {

        // Only needed three checks between blocks
        for (unsigned int i=0; i<3; i++) {
            _block1 = (i == 2) ? diamonds[1] : diamonds[0];
            _block2 = (i == 0) ? diamonds[1] : diamonds[2];
            _pos1   = _block1->getPosition();
            _pos2   = _block2->getPosition();

            _distance[i][0] = abs(_pos1.x - _pos2.x);
            _distance[i][1] = abs(_pos1.y - _pos2.y);
        }

        _sum_distance.x = _distance[0][0] + _distance[1][0] + _distance[2][0];
        _sum_distance.y = _distance[0][1] + _distance[1][1] + _distance[2][1];


        if (diamonds[0]->getDirection() == -1  &&  diamonds[1]->getDirection() == -1  &&  diamonds[2]->getDirection() == -1  &&  state != active) {

            // Check if whe active the play
            if ((_sum_distance.x == 4 && _sum_distance.y == 0)  ||  (_sum_distance.x == 0 && _sum_distance.y == 4)) {
                state = active;

                // Desacivate blocks before activating star play
                for (unsigned int i=0; i<TOTAL_DIAMOND_BLOCK; i++)
                    diamonds[i]->preActivateBlock(false);

            // If there are two continuous blocks
            } else if ((_distance[0][0]==0 && _distance[0][1]==1)  ||  (_distance[0][0]==1 && _distance[0][1]==0)  ||  (_distance[1][0]==0 && _distance[1][1]==1)  ||  (_distance[1][0]==1 && _distance[1][1]==0)  ||  (_distance[2][0]==0 && _distance[2][1]==1)  ||  (_distance[2][0]==1 && _distance[2][1]==0)) {
                colorClock->restart();
                state = half;

            // Inactive play...
            } else {
                state = inactive;
            }
        }


        // Set the play state...
        switch (state) {
            case active:

                // Star Play duration...
                if (colorClock->getElapsedTime().asSeconds() >= STAR_PLAY_DURATION)
                    used  = true;
                break;

            case half:
                for (unsigned int i=0; i<TOTAL_DIAMOND_BLOCK; i++)
                    if (!diamonds[i]->getActived())
                        diamonds[i]->preActivateBlock(true);
                break;

            case inactive:
                for (unsigned int i=0; i<TOTAL_DIAMOND_BLOCK; i++)
                    if (diamonds[i]->getActived())
                        diamonds[i]->preActivateBlock(false);
                break;
        }
    }

    _block1 = NULL;
    _block2 = NULL;
}





PlayState StarPlay::getPlayState() {
    return state;
}





bool StarPlay::getUsed() {
    return used;
}




void StarPlay::setState(int state) {
    this->state = (PlayState) state;
}