#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;

/** @param size Number of tiles for the game.  \
 *  Should be a perfect square (4, 16, 25)
 *  @param numInitMoves Number of tile moves to attempt to scramble the board
 *  @param seed Use to seed the random number generator (srand) 
 */
Board::Board(int size, int numInitMoves, int seed )
{
  size_ = size;
  tiles_ = new int[size_];
  int dim = static_cast<int>(sqrt(size_));
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  for(int i=0; i < numInitMoves; i++){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
    }
  }
}

Board::Board()
{
  size_ = 4;
  tiles_ = new int[size_];
  for (int i=0; i<size_; i++){
    tiles_[i] = i;
  }
}

/** Copy constructor */
Board::Board(const Board &b)
{
  size_ = b.size_;
  tiles_ = new int[size_];
  for (int i=0; i<size_; i++){
    tiles_[i] = b.tiles_[i];
  }
}

/** @param tiles Array of tiles to be copied
 * @param size Size of board to be copied */
Board::Board(int *tiles, int size)
{
  size_ = size;
  tiles_ = new int[size_];
  for (int i=0; i<size_; i++){
    tiles_[i] = tiles[i];
  }
}

Board::~Board()
{
  delete [] tiles_;
}

/** @param tile Value of tile to swap with the blank */
bool Board::move(int tile)
{
  int width = sqrt(size_);
  int tileLoc=-1, zeroLoc=-1;
  for (int i=0; i<size_; i++){
    if (tiles_[i] == 0){
      zeroLoc = i;
    }
    if (tiles_[i] == tile){
      tileLoc = i;
    }
  }
  if (tileLoc-width == zeroLoc || tileLoc+width == zeroLoc || (zeroLoc%width != 0 && tileLoc+1 == zeroLoc) || (tileLoc%width != 0 && tileLoc-1 == zeroLoc)){
    tiles_[zeroLoc] = tile;
    tiles_[tileLoc] = 0;
  } else {
    //cout << "Invalid tile move, please try again" << endl;
    return false;
  }
  return true;
}

/** @return map of new boards with Key=tile, Value=Ptr to corresponding Board */
map<int, Board*> Board::potentialMoves()
{
  int width = sqrt(size_);
  int zeroLoc=-1, up=-1, down=-1, left=-1, right=-1;
  for (int i=0; i<size_; i++){
    if (tiles_[i] == 0){
      zeroLoc = i;
      break;
    }
  }

  up = zeroLoc-width;
  down = zeroLoc+width;
  left = zeroLoc-1;
  right = zeroLoc+1;

  if (up >= 0){
    newBoard_ = new Board(*this);
    newBoard_->move(tiles_[up]);
    boardMap_[tiles_[up]] = newBoard_;
  }

  if (down < size_){
    newBoard_ = new Board(*this);
    newBoard_->move(tiles_[down]);
    boardMap_[tiles_[down]] = newBoard_;
  }

  if (zeroLoc%width != 0){
    newBoard_ = new Board(*this);
    newBoard_->move(tiles_[left]);
    boardMap_[tiles_[left]] = newBoard_;
  }

  if (zeroLoc%width != width-1){
    newBoard_ = new Board(*this);
    newBoard_->move(tiles_[right]);
    boardMap_[tiles_[right]] = newBoard_;
  }

  return boardMap_;

}

/** @return true if the board is solved, false otherwise */
bool Board::solved()
{
  for (int i=0; i<size_; i++){
    if (tiles_[i] != i){
      return false;
    }
  }
    return true;
}

/** @param os ostream to contain the board in printable format
 * @param b board to be written to ostream in printable format
 * @return ostream containing the board in printable format */
ostream& operator<<(ostream &os, const Board &b)
{
  int width = sqrt(b.size_);
  int rowNum = width;
  int j;
  if (b.size_ >= 16){
    j = 3;
  } else {
    j = 2;
  }
  for (int i=0; i<b.size_; i++){
    if (i<rowNum-1){
      if (!b.tiles_[i]){
	os << setw(j) << " " << " ";
      } else {
      os << setw(j) << b.tiles_[i] << " ";
      }
    } else {
      if (!b.tiles_[i]){
	os << setw(j) << " " << endl;
      } else {
      os << setw(j) << b.tiles_[i] << endl;
      }
      rowNum += width;
    }
  }
  return os;
}

/** @param rhs board to compare with this board
 * @return true if boards are the same, false otherwise */
bool Board::operator==(const Board& rhs) const
{
  for (int i=0; i<size_; i++){
    if (rhs.tiles_[i] != tiles_[i]){
      return false;
    }
  }
  return true;
}

/** @param rhs board to compare with this board
 * @return true if this board is smaller than the other, false if the other board is smaller than this board */
bool Board::operator<(const Board& rhs) const
{
  if(size_ < rhs.size_){
    return true;
  }
  bool val = false;
  for(int i=0; i < size_; i++){
    if(tiles_[i] < rhs.tiles_[i]){
       //val = true;
       //break;
       return true;
     }
     else if(tiles_[i] > rhs.tiles_[i]){
       //break;
       return false;
     }
  }
  return val;
}

/** @param rhs board to compare to this board
 * @return true if boards are different, false otherwise */
bool Board::operator!=(const Board& rhs) const
{
  if (Board::operator==(rhs)){
    return false;
  } else {
    return true;
  }
}

/** @return array of tiles in board */
int* Board::getTiles()
{
  return tiles_;
}

/** @return size of board */
int Board::getSize()
{
  return size_;
}

