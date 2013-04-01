#include "puzzle_heur.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

/** @param tiles Tiles in board to compute h score for
 * @param size Size of board to compute h score for
 * @return score based on Manhattan heuristic computation */
int ManhattanHeuristic::compute(int *tiles, int size)
{
  int x, y, score=0, width;
  width = sqrt(size);
  for (int i=0; i<size; i++){
    if (tiles[i] && tiles[i] != i){
      x = abs(i%width - (tiles[i])%width);
      y = abs(i/width - (tiles[i])/width);
      score += x + y;
    }
  }
  return score;
}

/** @param tiles Tiles in board to compute h score for
 * @param size Size of board to compute h score for
 * @return score based on out-of-place heuristic computation */
int OutOfPlaceHeuristic::compute(int *tiles, int size)
{
  int score=0;
  for (int i=0; i<size; i++){
    if (tiles[i] && tiles[i] != i){
      score++;
    }
  }
  return score;
}
