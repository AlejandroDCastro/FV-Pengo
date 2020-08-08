#include "StarPlay.h"




StarPlay::StarPlay(Labyrinth *labyrinth) {
    diamonds = labyrinth->getDiamondBlocks();
    state    = inactive;
}




StarPlay::~StarPlay() {
    for (unsigned int i=0; i<TOTAL_DIAMOND_BLOCK; i++)
        diamonds[i] = NULL;
    delete[] diamonds;
}




// Check if the blocks are continuous to activate star play
void StarPlay::Update() {
    int _distance[3][2];
    DiamondBlock *_block1, *_block2;
    sf::Vector2i _pos1, _pos2, _sum_distance;

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

    // Check if whe active the play
    if ((_sum_distance.x == 3 && _sum_distance.y == 0)  ||  (_sum_distance.x == 0 && _sum_distance.y == 3)) {
        state = active;
    }

    _block1 = NULL;
    _block2 = NULL;
}