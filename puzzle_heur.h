#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H


class PuzzleHeuristic
{
 public:
  virtual int compute(int *tiles, int size) = 0;
};


// Define actual Heuristic Classes here

#endif
