#include "guitile.h"
#include "mainwindow.h"

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

void GUITile::move( int xpos, int ypos ) {

  while (x != xpos){
    x++;
  }
  while (y != ypos){
    y ++;
  }

    //Everything is good. Update the QRectF that is actually displayed.
    QPointF p( x, y );
    QRectF r( rect() );
    r.moveTo(p);
    setRect( r );

}

int GUITile::getX() {
    return x;
}

int GUITile::getY() {
    return y;
}

void GUITile::setX(int nx) {
    x = nx;
}

void GUITile::setY(int ny) {
    y = ny;
}

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

void GUITile::mousePressEvent(QGraphicsSceneMouseEvent* event){
  mwindow->moveTile(id);
}

int GUITile::getID(){
  return id;
}
