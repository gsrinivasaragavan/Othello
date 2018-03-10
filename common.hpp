#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y, score, heurestic_score, weight;
    Move(int x, int y, int score) {
        this->x = x;
        this->y = y;  
        this->score = score;
        this->heurestic_score = heurestic_score; 
        this->weight = weight;      
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }
    int getScore() {return score;}
    int getHeurestic_score() { return heurestic_score;}
    int getweight() { return weight; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setScore(int score) { this->score = score;}
    void setHeurestic_score(int heurestic_score) {this-> heurestic_score = heurestic_score;}
    void setweight(int weight) { this->weight = weight; }
};

#endif
