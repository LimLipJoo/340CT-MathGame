#include "questions.h"
#include <QRandomGenerator>
#include <QDateTime>
Questions::Questions(QString sign)
{
    this->sign=sign;
    generateQuestions();
}
void Questions::generateQuestions(){
    QRandomGenerator rand(QDateTime::currentMSecsSinceEpoch()/1000);
    if(sign.compare("add")==0){
        for(int i=0;i<6;i++){
          options[i]=(int)rand.bounded(0,10);
        }
        operand1=options[(int)rand.bounded(0,5)];
        operand2=options[(int)rand.bounded(0,5)];
        answer=operand1+operand2;
    }
    else if(sign.compare("sub")==0){
        bool invalid=true;
        for(int i=0;i<6;i++){
          options[i]=(int)rand.bounded(0,10);
        }

        while(invalid){
            operand1=options[(int)rand.bounded(0,5)];
            operand2=options[(int)rand.bounded(0,5)];
            if(operand1>=operand2){
                invalid=false;
            }
        }

        answer=operand1-operand2;
    }
    else if(sign.compare("mul")==0){
        for(int i=0;i<6;i++){
          options[i]=(int)rand.bounded(0,10);
        }
        operand1=options[(int)rand.bounded(0,5)];
        operand2=options[(int)rand.bounded(0,5)];
        answer=operand1*operand2;
    }
    else if(sign.compare("div")==0){
        bool invalid=true;
        int temp1=(int)rand.bounded(1,10);
        int temp2=(int)rand.bounded(1,10);
        for(int i=0;i<6;i++){
          options[i]=(int)rand.bounded(1,100);
        }
        int index=(int)rand.bounded(0,5);
        options[index]=temp2;
        operand2=options[index];
        while(invalid){
            int indexTemp=(int)rand.bounded(0,5);
            if(indexTemp!=index){
                options[indexTemp]=temp1*temp2;
                operand2=options[indexTemp];
                invalid=false;
            }
        }
        answer=temp1;
    }
}

int Questions::getAnswer(){
    return answer;
}
int Questions::getOperand1(){
    return operand1;
}
int Questions::getOperand2(){
    return operand2;
}
int* Questions::getOptions(){
    return options;
}
QString Questions::getSign(){
    QString op;
    if(sign.compare("add")==0){
        op="+";
    }
    else if(sign.compare("sub")==0){
        op="-";
    }
    else if(sign.compare("mul")==0){
        op="x";
    }
    else if(sign.compare("div")==0){
        op="÷";
    }
    return op;
}
