#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 3){
    cerr << "Usage: ./puzzle size initMoves seed" << endl;
    return 1;
  }

  int size, initMoves, seed;

  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);

  Board b(size,initMoves,seed);

  //**** Implement the gameplay here

  int tileToMove;

  while(!b.solved()){
    cout << b;
    cout << "Enter tile number to move or -1 for a cheat: ";
    cin >> tileToMove;
    b.move(tileToMove);
    cout << endl;
  }

  cout << b << endl;
  cout << "Congrats! Ya solved it!" << endl;

  return 0;
}
