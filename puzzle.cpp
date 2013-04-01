#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 4){
    cerr << "Usage: ./puzzle size initMoves seed" << endl;
    return 1;
  }

  int size, initMoves, seed;
  double width, widthCheck;

  size = atoi(argv[1]);

  width = sqrt(size);
  int temp = width;
  widthCheck = temp;
  if (width != widthCheck){
    cerr << "Invalid size: should be a perfect square" << endl;
    exit(0);
  }

  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);

  Board b(size,initMoves,seed);

  //** Implements the gameplay

  int tileToMove;

  cout << endl;

  while(!b.solved()){
    cout << b;
    cerr << "\nEnter tile number to move or -1 for a cheat: ";
    cin >> tileToMove;

    if (cin.fail()){
      cerr << "Invalid entry, please try again" << endl << endl;
      cin.clear();
      cin.ignore(256, '\n');
    } else if (tileToMove == -1){
      ManhattanHeuristic *h = new ManhattanHeuristic;
      //OutOfPlaceHeuristic *h = new OutOfPlaceHeuristic; //uncomment if desired
      PuzzleSolver *s = new PuzzleSolver(b);
      s->run(h);
      cout << "\nTry this sequence: ";
      for (int i=(s->getSolutions()).whereAt()-1; i>-1; i--){
	cout << (s->getSolutions()).getVal(i) << " ";
      }
      cout << endl;
      cout << "(Expansions = " << s->getNumExpansions() << ")" << endl << endl;
      delete h;
      delete s;
    } else if (tileToMove <= size) {
      b.move(tileToMove);
      cout << endl;
    } else {
      cerr << "Invalid entry, please try again" << endl << endl;
    }
  }

  cout << b << endl;
  cout << "Congrats, you solved it!" << endl;

  return 0;

}
