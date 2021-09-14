#include "game.h"
#include "ui_game.h"
#include <QString>
#include <QIcon>
#include <QFile>


#include <QUrl>
Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    bgm.setSource(QUrl("qrc:/bgm.wav"));
    bgm.setLoopCount(QSoundEffect::Infinite);
    bgm.setVolume(0.5f);
    bgm.play();
}

Game::~Game()
{
    delete ui;
}





void Game::on_additionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    setupGame("add");
}


void Game::on_subtractionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    setupGame("sub");
}


void Game::on_multiplicationButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    setupGame("mul");
}


void Game::on_divisionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    setupGame("div");
}

void Game::changeLabel()
{
    ui->timer->setText(QString::number(timer->remainingTime()/1000).rightJustified(2,'0').prepend("0:"));
}

void Game::timeOut()
{
   wrongAnswer();
}

void Game::setupGame(QString sign){
    questions=new Questions(sign);
    ui->sign->setText(questions->getSign());
    score.resetScore();
    hearts.resetHearts();
    healthPotion.resetCooldown();
    timerPlus.resetCooldown();
    clue.resetCooldown();
    ui->healthItem->setDisabled(false);
    ui->timeItem->setDisabled(false);
    ui->clueItem->setDisabled(false);
    ui->gameOverScore->setText(QString::number(score.getScore()));
    round=0;
    ui->input1->setText("");
    ui->input2->setText("");
    ui->bonusLabel->setVisible(false);
    int score=this->score.getScore();
    ui->score->setText(QString::number(score));
    ui->Heart1->setVisible(true);
    ui->Heart2->setVisible(true);
    ui->Heart3->setVisible(true);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    labelTimer=new QTimer(this);
    connect(labelTimer,SIGNAL(timeout()),this,SLOT(changeLabel()));
    timer->start(10000);
    ui->timer->setText(QString::number(timer->remainingTime()/1000).rightJustified(2,'0').prepend("0:"));
    labelTimer->start(1000);
    nextRound();
}


void Game::on_healthItem_clicked()
{
    if(hearts.getHearts()<3){
        healthPotion.itemFeature(&hearts);
        changeHeartIcons();
        healthPotion.putOnCooldown();
        ui->healthItem->setDisabled(true);
    }
}

void Game::changeHeartIcons(){
    switch(hearts.getHearts()){
     case 3:
        ui->Heart1->setVisible(true);
        ui->Heart2->setVisible(true);
        ui->Heart3->setVisible(true);
        break;
     case 2:
        ui->Heart1->setVisible(true);
        ui->Heart2->setVisible(true);
        ui->Heart3->setVisible(false);
        break;
    case 1:
       ui->Heart1->setVisible(true);
       ui->Heart2->setVisible(false);
       ui->Heart3->setVisible(false);
       break;
    case 0:
       ui->Heart1->setVisible(false);
       ui->Heart2->setVisible(false);
       ui->Heart3->setVisible(false);
       break;
    }
}
void Game::endRound(){
    round+=1;
    if(round%5==0){
        ui->bonusLabel->setVisible(true);
    }
    else{
        ui->bonusLabel->setVisible(false);
    }
    if(healthPotion.getCooldown()>0){
        healthPotion.reduceCooldown();
        if(healthPotion.getCooldown()==0){
            ui->healthItem->setDisabled(false);
        }
    }
    if(timerPlus.getCooldown()>0){
        timerPlus.reduceCooldown();
        if(timerPlus.getCooldown()==0){
            ui->timeItem->setDisabled(false);
        }
    }
    if(clue.getCooldown()>0){
        clue.reduceCooldown();
        if(clue.getCooldown()==0){
            ui->clueItem->setDisabled(false);
        }
    }
}

void Game::nextRound()
{
    questions->generateQuestions();
    int* options;
    options=questions->getOptions();
    ui->option1->setText(QString::number(options[0]));
    ui->option2->setText(QString::number(options[1]));
    ui->option3->setText(QString::number(options[2]));
    ui->option4->setText(QString::number(options[3]));
    ui->option5->setText(QString::number(options[4]));
    ui->option6->setText(QString::number(options[5]));
    ui->answer->setText(QString::number(questions->getAnswer()));
    timer->setInterval(10000);
}

void Game::checkAnswer()
{
    if(!ui->input1->text().isEmpty()&&!ui->input2->text().isEmpty()){
        qInfo("hi");
        int input1=ui->input1->text().toInt();
        int input2=ui->input2->text().toInt();
        if(questions->getSign().compare("+")==0){
            if(input1+input2==questions->getAnswer()){
                correctAnswer();
            }
            else{
                wrongAnswer();
            }
        }
        else if(questions->getSign().compare("-")==0){
            if(input1-input2==questions->getAnswer()){
                correctAnswer();
            }
            else{
                wrongAnswer();
            }
        }
        else if(questions->getSign().compare("x")==0){
            if(input1*input2==questions->getAnswer()){
                correctAnswer();
            }
            else{
                wrongAnswer();
            }
        }
        else if(questions->getSign().compare("÷")==0){
            if(input1/input2==questions->getAnswer()){
                correctAnswer();
            }
            else{
                wrongAnswer();
            }
        }
    }
}

void Game::correctAnswer()
{
    sfx.setSource(QUrl("qrc:/correct.wav"));
    sfx.setVolume(1.0f);
    sfx.play();
    if(round%5==0&&round!=0){
        if(hearts.getHearts()==3){
           score.addScore(100);
        }
        else{
            hearts.addHearts();
            changeHeartIcons();
        }
    }
    else{
        score.addScore(50);
    }
    nextRound();
    ui->score->setText(QString::number(score.getScore()));
    ui->input1->setText("");
    ui->input2->setText("");
    endRound();
}

void Game::wrongAnswer()
{
    sfx.setSource(QUrl("qrc:/wrong.wav"));
    sfx.setVolume(1.0f);
    sfx.play();
    hearts.minusHearts();
    changeHeartIcons();
    if(hearts.getHearts()==0){
        ui->gameOverScore->setText(QString::number(score.getScore()));
        ui->stackedWidget->setCurrentIndex(2);
        timer->stop();
        labelTimer->stop();
        sfx.setSource(QUrl("qrc:/gameover.wav"));
        sfx.setVolume(1.0f);
        sfx.play();
    }
    else{
        nextRound();
        ui->input1->setText("");
        ui->input2->setText("");
        endRound();
    }

}

void Game::on_timeItem_clicked()
{
    timerPlus.itemFeature(timer);
    timerPlus.putOnCooldown();
    ui->timeItem->setDisabled(true);
}


void Game::on_clueItem_clicked()
{
    if(ui->input1->text().length()==0){
        ui->input1->setText(QString::number(questions->getOperand1()));
    }
    else if(ui->input2->text().length()==0){
        ui->input1->setText(QString::number(questions->getOperand2()));
    }
    clue.putOnCooldown();
    ui->clueItem->setDisabled(true);
}


void Game::on_input1_textChanged(const QString &arg1)
{
    checkAnswer();
}


void Game::on_input2_textChanged(const QString &arg1)
{
    checkAnswer();
}




void Game::on_mainMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    sfx.stop();
}

