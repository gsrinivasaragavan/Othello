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

Move *Player::moveCount(vector<Move*> moves, Board *board){
	if (moves.size() == 0 ){
		return nullptr; 
	}
	//assign the weight of each move a value
	for (unsigned i = 0; i < moves.size(); i++)
	{
	
		//corners
		if ((moves[i]->getX() == 0 && moves[i]->getY() == 0) || (moves[i]->getX() == 0 && moves[i]->getY() == 7) || (moves[i]->getX() == 7 && moves[i]->getY() == 0) || (moves[i]->getX() == 7 && moves[i]->getY() == 7))
		{
			moves[i]->weight = 4;
		}
		else if ((2 < moves[i]->getX() && moves[i]->getX() < 0 && moves[i]->getY() == 0) || (2 < moves[i]->getX() && moves[i]->getX() < 5 && moves[i]->getY() == 7) || (moves[i]->getX() == 0 && 2 < moves[i]->getY() && moves[i]->getY() < 5) || (moves[i]->getX() == 7 && 2 < moves[i]->getY() && moves[i]->getY() < 5)){
			moves[i]->weight = 2;
		}
		else if  ((moves[i]->getX() == 0 && moves[i]->getY() ==1) || (moves[i]->getX() == 1 && moves[i]->getY()==0) || (moves[i]->getX() == 0 && moves[i]->getY()==6) || (moves[i]->getX() == 1 && moves[i]->getY()==7) || (moves[i]->getX() == 6 && moves[i]->getY()==0) || (moves[i]->getX() == 7 && moves[i]->getY()==1) || (moves[i]->getX() == 6 && moves[i]->getY()==7) || (moves[i]->getX() == 7 && moves[i]->getY()==6)){
			moves[i]->weight = -8;
		}
		else if ((moves[i]->getX() == 1 && moves[i]->getY()==1) || (moves[i]->getX() == 1 && moves[i]->getY()==6) || (moves[i]->getX() == 6 && moves[i]->getY()==6) || (moves[i]->getX() == 6 && moves[i]->getY()==1)){
			moves[i]->weight = -9;
		}
		else if ((2 < moves[i]->getX() && moves[i]->getX() < 0 && moves[i]->getY() == 1) || (2 < moves[i]->getX() && moves[i]->getX() < 5 && moves[i]->getY() == 6) || (moves[i]->getX() == 1 && 2 < moves[i]->getY() && moves[i]->getY() < 5) || (moves[i]->getX() == 6 && 2 < moves[i]->getY() && moves[i]->getY() < 5)){
			moves[i]->weight = -1;
		}
		else if ((moves[i]->getX() == 3 && moves[i]->getY() == 3) || (moves[i]->getX() == 3 && moves[i]->getY() == 4) || (moves[i]->getX() == 4 && moves[i]->getY() == 4) || (moves[i]->getX() == 4 && moves[i]->getY() == 3) || (moves[i]->getX() == 2 && moves[i]->getY() == 2) || (moves[i]->getX() == 5 && moves[i]->getY() == 2) || (moves[i]->getX() == 2 && moves[i]->getY() == 5) || (moves[i]->getX() == 5 && moves[i]->getY() == 5)){
			moves[i]->weight = 1;
		}
		else{
			moves[i]->weight = 0;
		}
	}
	//if move is a corner move automatically pick that move
	for (unsigned int i=0; i<moves.size(); i++){
		if (moves[i]->weight == 4){
			return moves[i]; 
		}
	}
	//check moves for otherside
	for (unsigned int k=0; k<moves.size(); k++){
		Board * newBoard = board->copy(); 
		vector<Move*> opponentsMove = getMoves(newBoard, otherSide); 
		for (unsigned int i=0; i<opponentsMove.size(); i++){
			if ((opponentsMove[i]->getX() == 0 && opponentsMove[i]->getY() == 0) || (opponentsMove[i]->getX() == 0 && opponentsMove[i]->getY() == 7) || (opponentsMove[i]->getX() == 7 && opponentsMove[i]->getY() == 0) || (opponentsMove[i]->getX() == 7 && opponentsMove[i]->getY() == 7))
			{
				opponentsMove[i]->weight = 4;
			}
			else{
				opponentsMove[i]->weight =-9; 
			}
		}
		//if opponent gets a corenr piece from doing our move, set that move to really low weight
		for (unsigned int j=0; j<opponentsMove.size(); j++){
			if (opponentsMove[j]->weight == 4){
				moves[k]->weight = -9; 
			}
		}
		delete newBoard; 
	}
			
	//We will calculate the amount of moves possible for the opponent after the current move is picked- want to minimize this
	//create a board, based on move we do, getmoves for opponent based on current board state. Not sure if we need to make board an argument to the 
	//function to do this, then have to switch all code that uses moveCount and add a board to its argument
	//find a way to weight the number of moves with respect to the weights of the board pieces. 
	
	Board* tempBoard = board->copy();
	//if the opponent has no moves return move with highest weight
	for (unsigned i = 0; i < moves.size(); i++)
	{
		tempBoard->doMove(moves[i], side);
		vector<Move*> oppvector = getMoves(tempBoard, otherSide);
		if (oppvector.size() == 0){
			Move * new_move = moves[0]; 
			for (unsigned int i=0; i<moves.size(); i++){
				if (moves[i]->weight > new_move->weight)
		        {
		            new_move = moves[i];
		        } 
			}
			return new_move;
		}
		moves[i]->oppmoves = oppvector.size();
	}
	
	//set heurestic score equal to the weight minus the amount of moves 

	for (unsigned i = 0; i < moves.size(); i++)
	{
		moves[i]->heurestic_score = moves[i]->weight - (2 * moves[i]->oppmoves );
	}

	Move* moveneeded = moves[0];
	for (unsigned i=0; i<moves.size(); i++)
    {
		//compares the weights 
        if (moves[i]->heurestic_score > moveneeded->heurestic_score)
        {
            moveneeded = moves[i];
        }
    }
    return moveneeded;
}

int Player::depthScore(Board *new_board, int depth, int max_depth){
	/*vector<Move*> opponents_moves;
	vector<Move*> our_move; 
	Move * oppMove;
	Move * ourMove;*/
	while(depth < max_depth){
		vector<Move*> opponents_moves= getMoves(new_board, otherSide); 
		Move * oppMove = moveCount(opponents_moves, new_board); //run hureustic on opponents moves
		new_board->doMove(oppMove, otherSide); //does opponents move 
		vector<Move*> our_move = getMoves(new_board, side); //get our moves  
		Move * ourMove = moveCount(our_move, new_board); 
		new_board->doMove(ourMove, side); //does our move  
		depth ++; //increment depth 
	}
	vector<Move*> opponents_moves = getMoves(new_board, otherSide); 
	Move * oppMove = moveCount(opponents_moves, new_board); 
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
		Move * nextMove = minimax(0, 14, moves, board);
		board->doMove(nextMove, side); //does next move 
		return nextMove; //returns next move 
		
    return nullptr; 
}
