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
    if (side == BLACK){
		this->otherSide = WHITE; 
	}
	else{
		this->otherSide = BLACK; 
	}
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
	delete this->board; //deletes board
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
	int weights[8][8]; //2D array of weights
	//loop through 2D array 
	if (moves.size() == 0){
		return nullptr; 
	}
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			//corner pieces 
			if ((i==0 && j==0) || (i==0 && j==7) || (i==7 && j==0) || (i==7 && j==7)){
				weights[i][j] = 10; 
			}
			//edge pieces
            else if ((2 < i && i < 5 && j ==0) || (2 < i && i < 5 && j == 7) || (i == 0 && 2 < j && j < 5) || (i == 7 && 2 < j && j < 5))
            {
                weights[i][j] = 5;
            }
            //pieces next adjacent to the corner
            else if ((i == 0 && j ==1) || (i == 1 && j==0) || (i == 1 && j==1) || (i == 0 && j==6) || (i == 1 && j==6) || (i == 1 && j==7) || (i == 6 && j==0) || (i == 6 && j==1) || (i == 7 && j==1) || (i == 6 && j==7) || (i == 6 && j==6) || (i == 7 && j==6)){
                weights[i][j] = 1;
            }
            //remaining pieces 
			else{
				weights[i][j]=3; //can create weights in constructor
			}
		}
	}
    Move* moveneeded = moves[0];
    for (unsigned i=0; i<moves.size(); i++)
    {
		//compares the weights 
        if (weights[moves[i]->getX()][moves[i]->getY()] > weights[moveneeded->getX()][moveneeded->getY()])
        {
            moveneeded = moves[i];
        }
    }
    //returns best move 
    return moveneeded;
}
//Function will get the Moves a player can do based on the board
vector<Move*> Player::getMoves(Board *board, Side side){
	vector<Move*> next_moves; //create vector for next move
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			Move * current_grid = new Move(i, j, 0); //create new move with iterators and score 0
			if (board->checkMove(current_grid, side)){ //if move if possible add the moves vector
				next_moves.push_back(current_grid); 
			}
		}
	}
	return next_moves; 
}
int Player::depthScore(Board *new_board, int depth, int max_depth){
	/*vector<Move*> opponents_moves;
	vector<Move*> our_move; 
	Move * oppMove;
	Move * ourMove;*/
	while(depth < max_depth){
		vector<Move*> opponents_moves= getMoves(new_board, otherSide); 
		Move * oppMove = moveCount(opponents_moves); //run hureustic on opponents moves
		new_board->doMove(oppMove, otherSide); //does opponents move 
		vector<Move*> our_move = getMoves(new_board, side); //get our moves  
		Move * ourMove = moveCount(our_move); 
		new_board->doMove(ourMove, side); //does our move 
		depth ++; //increment depth 
	}
	vector<Move*> opponents_moves = getMoves(new_board, otherSide); 
	Move * oppMove = moveCount(opponents_moves); 
	new_board->doMove(oppMove, otherSide);//do opponents move
	int chosenScore; 
	//calculates score 
	if (side == BLACK){
		chosenScore = new_board->countBlack() - new_board->countWhite(); 
	}
	else{
		chosenScore = new_board->countWhite() - new_board->countBlack(); 
	}
	//returns score 
	return chosenScore; 
			
}
Move *Player::minimax(int depth, int max_depth, vector<Move*> moves, Board *board){
	//if no possible moves exist
	if (moves.size() ==0){
		return nullptr; 
	} 
	for (unsigned int i=0; i<moves.size(); i++){
		//copies board
		Board *new_board = board->copy();  
		new_board->doMove(moves[i], side);//does our move
		vector<Move*> opponents_moves= getMoves(new_board, otherSide); //finds possible moves 
		if (opponents_moves.size() ==0){//then we want to make this move 
			return moves[i]; 
		}
		moves[i]->score = depthScore(new_board, depth+2, max_depth); 
	}
	int bestScore = moves[0]->score; 
	Move * bestMove = moves[0]; 
	//finds move with highest score 
	for (unsigned int i=0; i<moves.size(); i++){
		if (moves[i]->score > bestScore){
			bestScore = moves[i]->score; 
			bestMove = moves[i]; 
		}
	}
	return bestMove; 
	
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
	*/
	
    //This will be the only function that actually plays the game. But we will make additional helper functions for our algorithm
	
	board->doMove(opponentsMove, this->otherSide); //does opponent's move
	vector<Move*> moves = this->getMoves(board, side); //creates a vector of moves
		Move * nextMove = minimax(0, 2, moves, board); 
		board->doMove(nextMove, side); //does next move 
		return nextMove; //returns next move 
		
    return nullptr; 
}
