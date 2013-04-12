#ifndef GUITILE_H
#define GUITILE_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "board.h"
#include "mylist.h"

class MainWindow;

/**
  This class maintains the location, size, and speed of a QGraphicsRectItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class GUITile : public QGraphicsRectItem {
public:
  GUITile(double nx, double ny, double w, double h, MainWindow *mwindow);
  ~GUITile();
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    void move(int xpos, int ypos);
    void setDisp(int n);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    int getID();

private:
    int x;
    int y;
    int width;
    int height;
    QGraphicsSimpleTextItem *tileDisp;
    MainWindow *mwindow;
    int id;
    MyList<QGraphicsSimpleTextItem*> dispList;
};

#endif // GUITILE_H
