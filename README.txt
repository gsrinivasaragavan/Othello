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
- Checked to see if for a certain move, the opponent could do a move that gets a corner. Set that move to a low weight

Gokul: 
- Added to the heurestic algorithm by weighting the edge pieces,weighting the pieces adjacent to the corner pieces, and weighting the remaining pieces
	. Assigned edge pieces a weight of 5
	. Assigned pieces next to the corner pieces a weight of 1
	. Assigned the remaining pieces on the board a weight of 3
- Created the minimax function that did the following 
	. took in a copy of the board and performed our move on the copy
	. finds all possible moves for the opponent and finds our best move by running the depthScore function
	. performs the best move
- Made the weights a aprt of the Move class, as well as a new variable heurestic score into the Move class
- Found the number of moves an oppoenent can do based on the current move chosen, also made that a part of the Move class.

Improvements:
- Initially initialized the weights into an array, then assigned those values to each move. Then decided to make the weights a part of the move struct. This helped when we also made another variable in the struct called oppmoves, which tracked how many moves that the opponent would have based on the current move we did. We then  created another variable caled heureustic score which would be some sort of linear combo of the oppmoves subtracted from the weight of the move
- Initially, we just had the weights in our heurestic, Realized that it is also importnat to track opponent's moves.
- Initially had corners eighted 10, edges weighted 5, pieces close to corenres weighted one, and other peices weighted three. We redid weights to a better ratio. 
- Made the heurestic score equal to the oppmoves multiplied by 2 subtracted from the weight of the move. Had to play around with how much to weigh the oppmove until we got to this number 
- In the minimax function, made the depth being searched an input so that we could search to higher and higher depths
- Our strategy will work because it is able to go as deep as the user desires, and also uses a complex heurestic that takes into account the board placement of our current move, as well as how the current move will affect the opponent's very next move. 
- Some things that didn't work out was the fact that we did not originally account for the fact that if we made a move that we thought that the "best", the opponent could make a move that would flank a corner which would mean that it actully wasn't the best move. 
- Originally, when we implemented minimax, we tried to recursively call it within the function but it was not able to calculate the correct moevs at the given depth. Instead ended up using a while loop, that had the same effect but worked. 


