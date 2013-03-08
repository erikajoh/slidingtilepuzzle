#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std;



int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}
