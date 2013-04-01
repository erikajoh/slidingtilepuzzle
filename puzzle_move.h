#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include <functional>
#include "board.h"
#include "puzzle_heur.h"

/**
 * PuzzleMove objects store the starting and subsequent Boards of an A* search, as well as the tile that was moved to result in each subsequent Board */
class PuzzleMove
{
 public:
  /** Constructor for starting Board of an A* search */
  PuzzleMove(Board &b);

  /** Constructor for subsequent search boards 
   * (i.e. those returned by Board::potentialMoves() ) */
  PuzzleMove(int tile, Board *b, PuzzleMove *parent);

  /** Destructor */
  ~PuzzleMove();

  /** Compare to PuzzleMoves based on f score (needed for priority queue) */
  bool operator<(const PuzzleMove& p) const;
  /** Compare to PuzzleMoves based on f score (needed for priority queue) */
  bool operator>(const PuzzleMove& p) const;
  /** Compare to PuzzleMoves based on f score (needed for priority queue) */
  bool operator==(const PuzzleMove& p) const;

  /** Sets h score based on heuristic computation */
  void computeH(PuzzleHeuristic *ph);

 public:
  /** tile moved to reach the Board b */
  int tileMove_;
  /** Pointer to a board representing the updated state */
  Board *b_;
  /** distance from the starting board */
  int g_;
  /** heuristic distance to the goal */
  int h_;
  /** Pointer to parent PuzzleMove */
  PuzzleMove *prev_;
};


/** PuzzleMoveGreater defines how to compare PuzzleMove*'s */
struct PuzzleMoveGreater : 
  public std::binary_function<const PuzzleMove*, const PuzzleMove*,bool>
{
  /** Compares PuzzleMove*'s
   * @param m1 First PuzzleMove* to compare
   * @param m2 Second PuzzleMove* to compare
   * @return true if m1 is larger than m2, false otherwise */
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    return *m1 > *m2;
  }
};

#endif
