#include "puzzle_move.h"
#include <iostream>

PuzzleMove::PuzzleMove(Board &b)
{
  b_ = new Board(b);
  g_ = 0;
  h_ = 0;
  prev_ = NULL;
}

PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{
  g_ = parent->g_ + 1;
  h_ = 0;
  tileMove_ = tile;
  b_ = new Board(*b);
  prev_ = parent;
}

void PuzzleMove::computeH(PuzzleHeuristic *ph)
{
  h_ = ph->compute(b_->getTiles(), b_->getSize());
}

PuzzleMove::~PuzzleMove()
{
  delete b_;
}

// Compare to PuzzleMoves based on f distance (needed for priority queue)
bool PuzzleMove::operator<(const PuzzleMove& p) const
{
  if((g_ + h_) < (p.g_ + p.h_)){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ > p.g_)){
    return true;
  }
  else {
    return false;
  }
}

bool PuzzleMove::operator>(const PuzzleMove& p) const
{
  if( (g_ + h_) > (p.g_ + p.h_) ){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ < p.g_) ){
    return true;
  }
  else {
     return false;
  }
}

bool PuzzleMove::operator==(const PuzzleMove& p) const
{
  if( (g_ + h_) == (p.g_ + p.h_) ){
    return true;
  } else {
     return false;
  }
}
