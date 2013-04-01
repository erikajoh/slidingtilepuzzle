#include "puzzle_move.h"
#include <iostream>

/** @param b Parent board to move from */
PuzzleMove::PuzzleMove(Board &b)
{
  b_ = new Board(b);
  g_ = 0;
  h_ = 0;
  prev_ = NULL;
}

/** @param tile tile that was moved to result in this board
 * @param b board that resulted from moving tile
 * @param parent Parent PuzzleMove that resulted in this PuzzleMove's board */
PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{
  g_ = parent->g_ + 1;
  h_ = 0;
  tileMove_ = tile;
  b_ = new Board(*b);
  prev_ = parent;
}

/** @param ph PuzzleHeuristic object to run compute() on */
void PuzzleMove::computeH(PuzzleHeuristic *ph)
{
  h_ = ph->compute(b_->getTiles(), b_->getSize());
}

/** Deletes copy of board that was made in constructor */
PuzzleMove::~PuzzleMove()
{
  delete b_;
}

/** @param p PuzzleMove object to compare to this one
 * @return true if this PuzzleMove object's f score is less than p's f score, false otherwise */
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

/** @param p PuzzleMove object to compare to this one
 * @return true if this PuzzleMove object's f score is greater than p's f score, false otherwise */
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

/** @param p PuzzleMove object to compare to this one 
 * @return true if this PuzzleMove object's f score is the same as p's f score, false otherwise */
bool PuzzleMove::operator==(const PuzzleMove& p) const
{
  if( (g_ + h_) == (p.g_ + p.h_) ){
    return true;
  } else {
     return false;
  }
}
