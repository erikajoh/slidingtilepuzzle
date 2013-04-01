#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H

/** PuzzleHeuristic is an abstract class from which ManhattanHeuristic and OutOfPlaceHeuristic are dervied to compute heuristic scores for Boards */
class PuzzleHeuristic
{
 public:
  /** Virtual compute function to implement in derived ManhattanHeuristic and OutOfPlaceHeuristic classes */
  virtual int compute(int *tiles, int size) = 0;
};

/**
 * ManhattanHeuristic computes the h (heuristic) score of
 * a board based on the x- and y-distance of each tile from
 * its place in the solved board */
class ManhattanHeuristic : public PuzzleHeuristic
{
 public:
  /** Computes the Manhattan heuristic */
  int compute(int *tiles, int size);
};

/**
 * OutOfPlaceHeuristic computes the h (heuristic) score of
 * a board based on the number of tiles that are not in their
 * correct places in the solved board */
class OutOfPlaceHeuristic : public PuzzleHeuristic
{
 public:
  /** Computes the out-of-place heuristic */
  int compute(int *tiles, int size);
};

#endif
