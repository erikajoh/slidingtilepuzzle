#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board &b)
{
  g_ = 0;
  prev_ = NULL;
  ManhattanHeuristic score;
  h_ = score.compute(b.getTiles(),b.getSize());
}

PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{
  g_=0;
  tileMove_ = tile;
  ManhattanHeuristic score;
  Board tempb(*b);
  tempb.move(tile);
  b_ = &tempb;
  h_ = score.compute(b_->getTiles(),b_->getSize());

  prev_ = parent;
  PuzzleMove *temp = prev_;
  while(prev_){
    g_++;
    temp = temp->prev_;
  }
}

PuzzleMove::~PuzzleMove()
{

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
