#ifndef QUESTIONS_H
#define QUESTIONS_H
#include <QString>

class Questions
{
public:
    Questions(QString);
    int getAnswer();
    int getOperand1();
    int getOperand2();
    int* getOptions();
    QString getSign();
    void generateQuestions();
private:
    QString sign;
    int answer;
    int operand1;
    int operand2;
    int options[6];
};

#endif // QUESTIONS_H
