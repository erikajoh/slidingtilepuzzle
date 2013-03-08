#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "mylist.h"

class PuzzleSolver
{
 public:
  //*** Typedef for the closed-list set.  Declare your closed list variable as
  //***   BoardSet closedlist; 
  //*** when you write your code for the run() funciton
  typedef std::set<Board *, BoardLessThan> BoardSet;

  // Constructor (makes a copy of the Board and stores it in _b
  PuzzleSolver(const Board &b);

  // Destructor
  ~PuzzleSolver();

  // Run the A* search returning -1 if no solution exists or
  //  the number of moves in the solution
  int run(PuzzleHeuristic *ph);

  //**** Return the solution List
 

  // Return how many expansions were performed in the search
  int getNumExpansions();

 private:
  Board b_;
  int expansions_;
  //**** Declare a List to store your solutions sequence of tiles to move
};

#endif
