#include "score.h"

Score::Score()
{
    score=0;
}
void Score::addScore(int score){
    this->score+=score;
}
int Score::getScore(){
    return score;
}
void Score::resetScore(){
    score=0;
}
