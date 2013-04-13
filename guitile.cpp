#include "guitile.h"
#include "mainwindow.h"

/** @param nx Horizontal position of tile
 * @param ny Vertical position of tile
 * @param w Width of tile
 * @param h Height of tile
 * @param mw MainWindow pointer */
GUITile::GUITile(double nx, double ny, double w, double h, MainWindow *mw) :
  QGraphicsRectItem(nx, ny, w, h) {
    x = nx;
    y = ny;
    width = w;
    height = h;
    mwindow = mw;
    id = -1;
}

GUITile::~GUITile(){
  for (int i=0; i<dispList.whereAt(); i++){
    QGraphicsSimpleTextItem *temp = dispList[i];
    dispList.remove(dispList[i]);
    delete temp;
  } 
}

/** @param xpos New horizontal position for tile to move to
 * @param ypos New vertical position for tile to move to */
void GUITile::move( int xpos, int ypos ) {

  if (x == xpos){
    moveL = false;
    moveR = false;
    if (y < ypos){
      moveU = false;
      moveD = true;
    } else {
      moveU = true;
      moveD = false;
    }
  } else if (y == ypos){
    moveU = false;
    moveD = false;
    if (x < xpos){
      moveL = false;
      moveR = true;
    } else {
      moveL = true;
      moveR = false;
    }
  }

  if (moveR){
    x++;
  } else if (moveL){
    x--;
  } else if (moveU){
    y--;
  } else if (moveD){
    y++;
  }

    QPointF p( x, y );
    QRectF r( rect() );
    r.moveTo(p);
    setRect( r );

}

/** @return x Horizontal position of tile */
int GUITile::getX() {
    return x;
}

/** @return y Vertical position of tile */
int GUITile::getY() {
    return y;
}

/** @param nx New horizontal position of tile */
void GUITile::setX(int nx) {
    x = nx;
}

/** @param ny New vertical position of tile */
void GUITile::setY(int ny) {
    y = ny;
}

/** @param n Number of tile to be displayed on GUI screen */
void GUITile::setDisp(int n){
  for (int i=0; i<dispList.whereAt(); i++){
    if ((dispList[i]->text()).toInt() == n) {
      QGraphicsSimpleTextItem *temp = dispList[i];
      dispList.remove(dispList[i]);
      delete temp;
      }
  }
 if (n){
    QString disp;
    disp.setNum(n);
    tileDisp = new QGraphicsSimpleTextItem(disp,this);
    tileDisp->setScale(width/15);
    dispList.pushBack(tileDisp);
    if (n<10){
      tileDisp->setPos(x+width/4,y);
    } else {
      tileDisp->setPos(x+width/20,y);
    }
  }
  id = n;
}

/** @param event Pointer to QGraphicsSceneMouseEvent of mouse press */
void GUITile::mousePressEvent(QGraphicsSceneMouseEvent* event){
  event = event;
  if (!(mwindow->tileMoving)){
    mwindow->moveTile(id);
  }
}

/** @return id ID of tile that is displayed on the GUI screen */
int GUITile::getID(){
  return id;
}

/** @return width Width of tile */
int GUITile::getWidth(){
  return width;
}
