Contributions from Group:
Netra:
- Wrote a working algorithm that was able to play against Simple Player.
	. Created the Player constructor that initialized the side, otherside, and board. 
	. Created the Player destructor that deleted the board
	. Updated the code for doMove that updated the internal board state based on the given opponent's move and then calculated and retured a valid move. 
- Added to the heurestic algorithm by prioritizing corner pieces 
	. Initialized a 2D array of weights that assigned corner pieces a weight of 10
- Created the depthScore function that returned the best move we could perform given a certain depth 
	. For each depth level, the algorithm runs the opponents move and then our move using the heuriestic algorithm we created earlier 
	. After it has gone through each depth level, it runs the opponents move and counts the number of black and white tokens are on the board
	. returns the difference in black and white tokens, depending on which color we are playing as

Gokul: 
- Added to the heurestic algorithm by weighting the edge pieces,weighting the pieces adjacent to the corner pieces, and weighting the remaining pieces
	. Assigned edge pieces a weight of 5
	. Assigned pieces next to the corner pieces a weight of 1
	. Assigned the remaining pieces on the board a weight of 3
- Created the minimax function that did the following 
	. took in a copy of the board and performed our move on the copy
	. finds all possible moves for the opponent and finds our best move by running the depthScore function
	. performs the best move


