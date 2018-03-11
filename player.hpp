#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    int depthScore(Board *board, int depth, int max_depth);
    vector<Move*> getMoves(Board *board, Side side);
    Move *minimax(int depth, int max_depth, vector<Move*> moves, Board *board);
	Move *moveCount(vector<Move *> moves, Board * board);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Side side; 
    Side otherSide; 
    Board * board; 
};

#endif
