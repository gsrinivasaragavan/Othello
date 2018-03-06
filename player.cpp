#include "player.hpp"
#include <vector>
#include <iostream>
#include <unistd.h>
using namespace std; 

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = side; 
    board = new Board; 

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board; //deletes board
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
 
 /* Outline
  * 
  * recieves oppenents move 
  * goes through all possible moves
  * chooses the best move 
  * plays the move
  * updates the board
  * returns the move it played. 
  */
  
Move *Player::moveCount(vector<Move*> moves){
	cerr<<"Next Move"<<endl; 
	int weights[8][8]; 
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			if ((i==0 && j==0) || (i==0 && j==7) || (i==7 && j==0) || (i==7 && j==7)){
				weights[i][j] = 10; 
			}
            else if ((2 < i && i < 5 && j ==0) || (2 < i && i < 5 && j == 7) || (i == 0 && 2 < j && j < 5) || (i == 7 && 2 < j && j < 5))
            {
                weights[i][j] = 5;
            }
            else if ((i == 0 && j ==1) || (i == 1 && j==0) || (i == 1 && j==1) || (i == 0 && j==6) || (i == 1 && j==6) || (i == 1 && j==7) || (i == 6 && j==0) || (i == 6 && j==1) || (i == 7 && j==1) || (i == 6 && j==7) || (i == 6 && j==6) || (i == 7 && j==6)){
                weights[i][j] = 1;
            }
			else{
				weights[i][j]=3; //can create weights in constructor
			}
		}
	}
    Move* moveneeded = moves[0];
    for (unsigned i=0; i<moves.size(); i++)
    {
        if (weights[moves[i]->getX()][moves[i]->getY()] > weights[moveneeded->getX()][moveneeded->getY()])
        {
            moveneeded = moves[i];
        }
    }
    return moveneeded;
}
	/*int counter = 0;
    for (int i=0; i<moves.size(); i++){
		cerr<<"("<<moves[i]->getX()<<", "<<moves[i]->getY()<<")"<<endl;
		if (moves[i]->getX() == 0 && moves[i]->getY()==0){
			cerr<<"yesss"<<endl; 
			return moves[i];  
		}
		if (moves[i]->getX() == 0 && moves[i]->getY()==7){
			cerr<<"yesss"<<endl; 
			return moves[i]; 
		}
		if (moves[i]->getX() == 7 && moves[i]->getY()==0){
			cerr<<"yesss"<<endl; 
			return moves[i]; 
		}
		if (moves[i]->getX() == 7 && moves[i]->getY()==7){
			cerr<<"yesss"<<endl; 
			return moves[i];
		} 
		if ((moves[i]->getX() == 0 && moves[i]->getY()==1) || (moves[i]->getX() == 1 && moves[i]->getY()==0) || (moves[i]->getX() == 1 && moves[i]->getY()==1) || (moves[i]->getX() == 0 && moves[i]->getY()==6) || (moves[i]->getX() == 1 && moves[i]->getY()==6) || (moves[i]->getX() == 1 && moves[i]->getY()==7) || (moves[i]->getX() == 6 && moves[i]->getY()==0) || (moves[i]->getX() == 6 && moves[i]->getY()==1) || (moves[i]->getX() == 7 && moves[i]->getY()==1) || (moves[i]->getX() == 6 && moves[i]->getY()==7) || (moves[i]->getX() == 6 && moves[i]->getY()==6) || (moves[i]->getX() == 7 && moves[i]->getY()==6)){
			cerr<<"skip!!!!"<<endl; 
            if (i==0){
                if(counter != moves.size()){
                moves.push_back(moves[i]);
                moves.erase(moves.begin());
                i -= 1;
                counter += 1;
                cerr<< "erasing" << moves[0]->getX() << moves[0]->getY() <<endl;
            }

            }
			continue; 
		}
	}
    cerr<<moves[0]->getX() << moves[0]->getY() <<endl;
	return moves[0]; 
    //42-50
}*/
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
	*/
	Side notColor; 
	//sets opposing team's color 
	if (side == BLACK){
		notColor = WHITE; 
	}
	else {
		notColor = BLACK; 
	}
	
    //This will be the only function that actually plays the game. But we will make additional helper functions for our algorithm
	
	board->doMove(opponentsMove, notColor); //does opponent's move
	vector<Move*> moves; //creates a vector of moves
	if (board->hasMoves(side)){
		for (int i=0; i < 8; i++){
			for (int j=0; j < 8; j++){
				Move * current_grid = new Move(i, j); //creates new move 
				if (board->checkMove(current_grid, side)){//checks if move is valid
					moves.push_back(current_grid); //pushes valid move to vector of moves
				}
				else{
					delete current_grid; 
				}
			}
		}
		Move * nextMove = moveCount(moves); 
		board->doMove(nextMove, side); //does move
		return nextMove; //returns move 
	}
    return nullptr; 
}
