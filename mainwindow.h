#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QGraphicsLayout>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QTextEdit>
#include <QFormLayout>
#include <QWidget>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "guitile.h"
#include "board.h"
#include "mylist.h"
#include "puzzle_heur.h"
#include "puzzle_move.h"
#include "pmminlist.h"
#include "puzzle_solver.h"

#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

class MainWindow : public QWidget {
    Q_OBJECT
    
public:
    explicit MainWindow();
    ~MainWindow();

    //void newRect();
    void show();
    void moveTile(int tile);

    bool tileMoving;


private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *timer;
    QVBoxLayout *layout;
    QHBoxLayout *row1, *row2, *row4, *row5;
    QHBoxLayout *row3;
    QPushButton *start, *quit, *cheat;
    QRadioButton *manhat, *oop;
    QFormLayout *input;
    QLineEdit *size, *seed, *numMoves;
    QTextEdit *errors;
    QListView *potMoves;
    GUITile *tile;
    MyList<GUITile*> *tiles_;
    QWidget *w;
    QGraphicsSimpleTextItem *tileNum;
    int viewHeight;
    Board *b;
    GUITile *tileToMove;
    int time, newX, newY, tileVal;

public slots:
    void newGame();
    void getCheat();
    void handleTimer();

};

#endif // MAINWINDOW_H
