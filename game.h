#ifndef GAME_H
#define GAME_H
#include "score.h"
#include "items.h"
#include "hearts.h"
#include "questions.h"
#include <QTimer>
#include <QMainWindow>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    void setupGame(QString);
    void changeHeartIcons();
    void endRound();
    void nextRound();
    void checkAnswer();
    void correctAnswer();
    void wrongAnswer();
private slots:


    void on_additionButton_clicked();

    void on_subtractionButton_clicked();

    void on_multiplicationButton_clicked();

    void on_divisionButton_clicked();

    void on_healthItem_clicked();

    void on_timeItem_clicked();

    void on_clueItem_clicked();

    void on_input1_textChanged(const QString &arg1);

    void on_input2_textChanged(const QString &arg1);


    void on_mainMenu_clicked();

public slots:
    void changeLabel();
    void timeOut();

private:
    Ui::Game *ui;
    class HealthPotion : public Items{
        public:
        void itemFeature(Hearts *hearts){
            if(getCooldown()==0)
                hearts->addHearts();
        }

    };
    class TimerPlus : public Items{
        public:
        void itemFeature(QTimer* timer){
            if(getCooldown()==0)
                timer->setInterval(timer->remainingTime()+5000);
        }

    };
    class Clue : public Items{
        public:
        void itemFeature(){

        }

    };
    Score score;
    Hearts hearts;
    HealthPotion healthPotion;
    TimerPlus timerPlus;
    Clue clue;
    QTimer *timer;
    QTimer *labelTimer;
    int round;
    Questions *questions;
    QSoundEffect bgm;
    QSoundEffect sfx;
};
#endif // GAME_H
