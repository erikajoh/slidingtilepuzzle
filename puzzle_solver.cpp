#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b)
{
  b_ = new Board(b);
  expansions_ = 0;
}

PuzzleSolver::~PuzzleSolver()
{
  delete b_;
}

int PuzzleSolver::run(PuzzleHeuristic *ph)
{
  PuzzleMove *move = new PuzzleMove(*b_);
  openList_.push(move);
  closedList_.insert(b_);
  garbageList_.push_back(move);

  while(!openList_.empty() && !b_->solved()){
    move = openList_.top();
    move->computeH(ph);
    openList_.pop();
    if (move->b_->solved()){
      while(move->prev_){
	solutions_.pushBack(move->tileMove_);
	move = move->prev_;
      }
      for (unsigned int i=0; i<garbageList_.size(); i++){
	delete garbageList_[i];
      }
      return solutions_.whereAt();
    }
    map<int, Board*> pmap = move->b_->potentialMoves();
    map<int, Board*>::iterator it;
    for (it = pmap.begin(); it!=pmap.end(); ++it){
      PuzzleMove *successor = new PuzzleMove(it->first, it->second, move);
      successor->computeH(ph);
      if (closedList_.find(successor->b_) == closedList_.end()){
	closedList_.insert(successor->b_);
	openList_.push(successor);
	expansions_++;
      }
      garbageList_.push_back(successor);
      delete it->second;
    }
  }
  delete move;
  return -1;
}

MyList<int>& PuzzleSolver::getSolutions()
{
  return solutions_;
}

int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}
