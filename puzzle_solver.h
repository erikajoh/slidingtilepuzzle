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
#include "pmminlist.h"

/**
 * PuzzleSolver implements the A* algorithm to solve the puzzle from
 * a given starting Board to the solved state */
class PuzzleSolver
{
 public:
  /** Typedef for the closed-list set */
  typedef std::set<Board *, BoardLessThan> BoardSet;

  /** Constructor (makes a copy of the Board and stores it in _b) */
  PuzzleSolver(const Board &b);

  /** Destructor */
  ~PuzzleSolver();

  /** Runs the A* search returning -1 if no solution exists or the number of moves in the solution */
  int run(PuzzleHeuristic *ph);

  /** Returns the solution list */
  MyList<int>& getSolutions();

  /** Returns how many expansions were performed in the search */
  int getNumExpansions();

 private:
  Board *b_;
  int expansions_;
  //**** Declare a List to store your solutions sequence of tiles to move
  MyList<int> solutions_;
  PMMinList openList_;
  BoardSet closedList_;
  vector<PuzzleMove*> garbageList_;

};

#endif
