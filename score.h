#ifndef SCORE_H
#define SCORE_H


class Score
{
public:
    Score();
    void addScore(int);
    int getScore();
    void resetScore();
private:
    int score;
};

#endif // SCORE_H
