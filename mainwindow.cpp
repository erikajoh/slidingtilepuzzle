#include "mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QtGui>
#include <QRectF>

MainWindow::MainWindow()  {

    //We need a scene and a view to do graphics in QT
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    layout = new QVBoxLayout;
    row1 = new QHBoxLayout;
    row2 = new QHBoxLayout;
    row3 = new QHBoxLayout;
    row4 = new QHBoxLayout;
    row5 = new QHBoxLayout;

    start = new QPushButton("&Start");
    connect(start, SIGNAL(clicked()), this, SLOT(newGame()));
    quit = new QPushButton("&Quit");
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    input = new QFormLayout;
    size = new QLineEdit("");
    seed = new QLineEdit("");
    numMoves = new QLineEdit("");
    input->addRow("Size:", size);
    input->addRow("# of Moves:", numMoves);
    input->addRow("Seed:", seed);
    cheat = new QPushButton("&Cheat");
    cheat->setDisabled(1);
    connect(cheat, SIGNAL(clicked()), this, SLOT(getCheat()));

    //Heuristic selection
    manhat = new QRadioButton("&Manhattan Heuristic");
    manhat->setDisabled(1);
    oop = new QRadioButton("&Out-of-Place Heuristic");
    oop->setDisabled(1);

    potMoves = new QListView;
    potMoves->setFixedHeight(60);
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *item = new QStandardItem(QString("Need help? Try the 'Cheat' button!"));
    model->setItem(0,item);
    potMoves->setModel(model);
    potMoves->setDisabled(1);
    errors = new QTextEdit("You are currently error-free!");
    errors->setReadOnly(1);
    errors->setFixedHeight(60);
    errors->setDisabled(1);
    tiles_ = NULL;

    viewHeight = 300;
    view->setFixedHeight(viewHeight);

    w = new QWidget;

    w->setLayout(layout);
    row1->addWidget(start);
    row1->addWidget(quit);
    row2->addLayout(input);
    row3->addWidget(view);
    row4->addWidget(cheat);
    row4->addWidget(manhat);
    row4->addWidget(oop);
    row5->addWidget(potMoves);
    row5->addWidget(errors);
    layout->addLayout(row1);
    layout->addLayout(row2);
    layout->addLayout(row3);
    layout->addLayout(row4);
    layout->addLayout(row5);

    w->setWindowTitle("Graphical Tile Puzzle");

    timer = new QTimer(this);
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
    time = 0;

    tileMoving = false;
}

void MainWindow::newGame(){

  if (tiles_){
    for (int i=0; i<tiles_->whereAt(); i++){
      delete tiles_->getVal(i);
    }
    delete tiles_;
    tiles_ = NULL;
    errors->setText("You are currently error-free!");
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *item = new QStandardItem(QString("Need help? Try the 'Cheat' button!"));
    model->setItem(0,item);
    potMoves->setModel(model);
  }

  view->setEnabled(1);
  errors->setEnabled(1);
  cheat->setEnabled(1);
  manhat->setEnabled(1);
  oop->setEnabled(1);
  potMoves->setEnabled(1);
  errors->setText("You are currently error-free!");

  int sizeInput = (size->text()).toInt();
  int numMovesInput = (numMoves->text()).toInt();
  int seedInput = (seed->text()).toInt();


  //Handling of illegal options
  if(sizeInput != 9 && sizeInput != 16){
    errors->setText("Whoops! You gotta enter 9 or 16 for size.");
    return;
  }

  if(numMovesInput <= 0){
    errors->setText("Whoops! You didn't enter a valid # of initial moves.");
    return;
  }

  if(seedInput <= 0){
    errors->setText("Whoops! You didn't enter a valid seed value.");
    return;
  }

  b = new Board(sizeInput, numMovesInput, seedInput);
  tiles_ = new MyList<GUITile*>;

  double width = sqrt(sizeInput);
  int temp = width;
  double widthCheck = temp;
  if (width != widthCheck){
    errors->setText("Whoops! You gotta make the size a perfect square.");
    return;
  }

  double y=0;
  for (int i=0; i<width; i++){
    double x=0;
    for (int j=0; j<width; j++){
      tile = new GUITile(x,y,viewHeight/width-1,viewHeight/width-1,this);
      tiles_->pushBack(tile);
      scene->addItem(tile);
      x += viewHeight/width-1;
    }
    y += viewHeight/width-1;
  }

  for (int i=0; i<sizeInput; i++){
    tiles_->getVal(i)->setDisp(*(b->getTiles() + i));
    if (!(tiles_->getVal(i)->getID())){
      tiles_->getVal(i)->hide();
    }
  }

}

void MainWindow::moveTile(int tile) {

  bool check = b->move(tile);

  if (check){
    errors->setText("You are currently error-free!");
  } else {
    errors->setText("Whoops! You can't move that tile.");
    return;
  }

  int origTile=-1, blankTile=-1, origX=-1, origY=-1;
  for (int i=0; i<tiles_->whereAt(); i++){
    if (tiles_->getVal(i)->getID() == tile){
      origTile = i;
      origX = tiles_->getVal(i)->getX();
      origY = tiles_->getVal(i)->getY();
    }
    if (!(tiles_->getVal(i)->getID())){
      blankTile = i;
      newX = tiles_->getVal(i)->getX();
      newY = tiles_->getVal(i)->getY();
    }
  }

  for (int i=0; i<tiles_->getVal(blankTile)->getWidth(); i++){
    tiles_->getVal(blankTile)->move(origX,origY);
  }

  tileToMove = tiles_->getVal(origTile);

  timer->start();
  tileMoving = true;
  //tiles_->getVal(origTile)->move(newX,newY);

  tileVal = tiles_->getVal(origTile)->getID();
  //tiles_->getVal(origTile)->setDisp(tiles_->getVal(origTile)->getID());

  GUITile *temp = tiles_->getVal(origTile);
  tiles_->getVal(origTile) = tiles_->getVal(blankTile);
  tiles_->getVal(blankTile) = temp;

  if (b->solved()){
    errors->setText("You solved it! Way to go!!");
    view->setDisabled(1);
    cheat->setDisabled(1);
    manhat->setDisabled(1);
    oop->setDisabled(1);
    potMoves->setDisabled(1);
  }

}

//Execution of A* algorithm
void MainWindow::getCheat(){
  Board n(*b);
  int solution=0;
  PuzzleSolver *s = new PuzzleSolver(n);
  if (manhat->isChecked()){
    ManhattanHeuristic *h = new ManhattanHeuristic;
    solution = s->run(h);
    delete h;
  } else if (oop->isChecked()){
    OutOfPlaceHeuristic *h = new OutOfPlaceHeuristic;
    solution = s->run(h);
    delete h;
  } else {
    errors->setText("Whoops! You gotta choose a heuristic.");
    return;
  }
  if (solution == -1){
    errors->setText("Oh no! There is no solution!");
  } else {
    int row=0;
    QStandardItemModel *model = new QStandardItemModel();
    for (int i=(s->getSolutions()).whereAt()-1; i>-1; i--){
      int val = (s->getSolutions()).getVal(i);
      QString sol;
      sol.setNum(val);
      QStandardItem *item = new QStandardItem(sol);
      model->setItem(row++,item);
    }
    potMoves->setModel(model);
    delete s;
  }
}

void MainWindow::show() {
    //This is how we get our view displayed.
    w->show();
}

void MainWindow::handleTimer(){
  if (time++ < tileToMove->getWidth()){
    tileToMove->move(newX,newY);
    tileToMove->setDisp(tileVal);
  } else {
    time = 0;
    timer->stop();
    tileMoving = false;
  }

}

MainWindow::~MainWindow()
{
    delete timer;
    delete start;
    delete quit;
}

