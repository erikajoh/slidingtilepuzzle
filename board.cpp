#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;


/** Init a board of given size and scramble it with numInitMoves 
 * by moving the space tile with a randomly chosen direction N, W, S, E
 * some of which may be invalid, in which case we skip that move 
 * 
 *  @param size Number of tiles for the game.  \
 *      Should be a perfect square (4, 16, 25)
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


/** Default constructor. Makes a 2x2 board in sorted frame. */
Board::Board()
{
  size_ = 4;
  tiles_ = new int[size_];
  for (int i=0; i<size_; i++){
    tiles_[i] = i;
  }
}

Board::Board(const Board &b)
{
  size_ = b.size_;
  tiles_ = new int[size_];
  for (int i=0; i<size_; i++){
    tiles_[i] = b.tiles_[i];
  }
}

Board::Board(int *tiles, int size)
{
  size_ = size;
  tiles_ = tiles;
  for (int i=0; i<size_; i++){
    tiles_[i] = tiles[i];
  }
}

/** Default destructor. Deletes tiles_. */
Board::~Board()
{
  delete tiles_;
}

void Board::move(int tile)
{
  int width = sqrt(size_);
  int tileLoc, zeroLoc;
  for (int i=0; i<size_; i++){
    if (tiles_[i] == 0){
      zeroLoc = i;
    }
    if (tiles_[i] == tile){
      tileLoc = i;
    }
  }
  if (tileLoc-width == zeroLoc || tileLoc+width == zeroLoc || tileLoc%width >= 0 || tileLoc%width < width-1){
    tiles_[zeroLoc] = tile;
    tiles_[tileLoc] = 0;
  }
}

map<int, Board*> Board::potentialMoves()
{
  map<int, Board*> boardMap;
  int width = sqrt(size_);
  int zeroLoc, up, down, left, right;
  for (int i=0; i<size_; i++){
    if (tiles_[i] == 0){
      zeroLoc = i;
    }
  }

  up = zeroLoc-width;
  down = zeroLoc+width;
  left = zeroLoc-1;
  right = zeroLoc+1;

  if (up >= 0){
    Board newBoard1(tiles_, size_);
    newBoard1.move(up);
    boardMap[up] = &newBoard1;
  }

  if (down < size_){
    Board newBoard2(tiles_, size_);
    newBoard2.move(down);
    boardMap[down] = &newBoard2;
  }

  if (zeroLoc%width != 0){
    Board newBoard3(tiles_, size_);
    newBoard3.move(left);
    boardMap[left] = &newBoard3;
  }

  if (zeroLoc%width != width-1){
    Board newBoard4(tiles_, size_);
    newBoard4.move(right);
    boardMap[right] = &newBoard4;
  }

  return boardMap;

}

bool Board::solved(){
  for (int i=0; i<size_; i++){
    if (tiles_[i] != i){
      return false;
    }
  }
    return true;
}

ostream& operator<<(ostream &os, const Board &b){
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
      os << setw(j) << b.tiles_[i] << " ";
    } else {
      os << setw(j) << b.tiles_[i] << endl;
      rowNum += width;
    }
  }
  return os;
}

bool Board::operator==(const Board& rhs) const
{
  for (int i=0; i<size_; i++){
    if (rhs.tiles_[i] != tiles_[i]){
      return false;
    }
  }
  return true;
}

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

bool Board::operator!=(const Board& rhs) const
{
  if (Board::operator==(rhs)){
    return false;
  } else {
    return true;
  }
}

int* Board::getTiles()
{
  return tiles_;
}

int Board::getSize()
{
  return size_;
}

