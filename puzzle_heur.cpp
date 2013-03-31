#include "puzzle_heur.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

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
