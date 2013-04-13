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

/** MainWindow class defines and implements the window that is displayed on
 * the GUI screen for gameplay */
class MainWindow : public QWidget {
    Q_OBJECT
    
public:
  /** MainWindow constructor */
    explicit MainWindow();
  /** MainWindow deconstructor */
    ~MainWindow();

    /** Shows the window on the GUI screen */
    void show();
    /** Moves the tile with the specified display ID */
    void moveTile(int tile);
    /** Used to check if tile is moving to prevent another tile from moving
     * while the current tile is still moving */
    bool tileMoving;


private:
    /** Pointer to QGraphicsScene for tile display */
    QGraphicsScene *scene;
    /** Pointer to QGraphicsView for tile display */
    QGraphicsView *view;
    /** Pointer to QTimer for tile animation */
    QTimer *timer;
    /** Pointer to layout of GUI screen */
    QVBoxLayout *layout;
    /** Pointers to each row to be used in layout */
    QHBoxLayout *row1, *row2, *row3, *row4, *row5;
    /** Pointers to start, quit, and cheat QPushButtons */
    QPushButton *start, *quit, *cheat;
    /** Pointers to QRadioButtons for heuristic selection */
    QRadioButton *manhat, *oop;
    /** Pointer to form for user input */
    QFormLayout *input;
    /** Pointers to size, seed, and number of initial moves input areas */
    QLineEdit *size, *seed, *numMoves;
    /** Pointer to error display area */
    QTextEdit *errors;
    /** Pointer to suggested solutions display area */
    QListView *potMoves;
    /** Pointer to GUITile to be created */
    GUITile *tile;
    /** Pointer to list that stores all displayed tiles */
    MyList<GUITile*> *tiles_;
    /** Pointer to widget */
    QWidget *w;
    /** Pointer to QGraphicsSimpleTextItem that displays the tile's ID */
    QGraphicsSimpleTextItem *tileNum;
    /** Height of the view (area containing the tiles) */
    int viewHeight;
    /** Pointer to board for back-end operations */
    Board *b;
    /** Pointer to GUITile to be moved */ 
    GUITile *tileToMove;
    /** Integers time, new x position, new y position, and tileVal for moving tile and tile animation */
    int time, newX, newY, tileVal;

public slots:
    /** Starts a new game */
    void newGame();
    /** Gets cheat by implementing A* algorithm with the user's selected
     * heuristic and displays the resulting solutions to the user */
    void getCheat();
    /** Handles timer for tile animation */
    void handleTimer();

};

#endif // MAINWINDOW_H
