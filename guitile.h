#ifndef GUITILE_H
#define GUITILE_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "board.h"
#include "mylist.h"

/** Prototypes the MainWindow that will be included for use in guitile.cpp */
class MainWindow;

/** GUITile stores the size, position, mainwindow, and ID (i.e. what is
 * displayed on the GUI screen) of a tile in the puzzle. It is derived from
 * the QGraphicsRectItem class */
class GUITile : public QGraphicsRectItem {
public:
/** GUITile constructor */
  GUITile(double nx, double ny, double w, double h, MainWindow *mwindow);
/** GUITile deconstructor deletes all text items that were applied to display
 * the tile's ID on the GUI screen */
  ~GUITile();
/** Sets the horizontal position of the tile */
    void setX(int x);
/** Sets the vertical position of the tile */
    void setY(int y);
/** Returns the horizontal position of the tile */
    int getX();
/** Returns the vertical position of the tile */
    int getY();
/** Moves the tile one pixel closer to where it should end up after being
 * clicked by the user */
    void move(int xpos, int ypos);
/** Puts display on the tile on the GUI screen */
    void setDisp(int n);
/** Handles a click on the tile by moving it unless a tile is already moving */
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
/** Returns the ID of the tile that is displayed on the GUI screen */
    int getID();
/** Returns the width (which is also height) of the tile */
    int getWidth();

private:
    /** Horizontal position of the tile */
    int x;
    /** Vertical position of the tile */
    int y;
    /** Width of the tile */
    int width;
    /** Height of the tile */
    int height;
    /** Qt simple text item to display on tile in MainWindow */
    QGraphicsSimpleTextItem *tileDisp;
    /** Pointer to MainWindow class */
    MainWindow *mwindow;
    /** ID to display on tile in MainWindow */
    int id;
    /** List to store previous simple text items for deletion later */
    MyList<QGraphicsSimpleTextItem*> dispList;
    /** Bools to determine which direction tile should move */
    bool moveL, moveR, moveU, moveD;
};

#endif // GUITILE_H
