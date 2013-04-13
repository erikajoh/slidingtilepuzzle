#include <QtGui/QApplication>
#include "mainwindow.h"

/** @mainpage Erika Johnson's CS102 PA4: Qt Game Time 
* @section purpose Overview
* Implements GUI for gameplay for an 8- or 15- puzzle sliding tile game
* and uses an A* search algorithm to suggest moves if the user requests them.
* @section requirements Requirements
* User must enter all entries as positive integers, and size must be
* 9 or 16. When user clicks a tile to move, the tile movement must
* be a valid tile move (i.e. the tile to move must
* be adjacent to the blank space). Usage is entry in the appropriate spaces on
* the GUI. */

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
