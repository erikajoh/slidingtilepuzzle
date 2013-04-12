#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>

/** Board creates a puzzle board with size, number of tile moves to scramble board, and randomly chosen direction based on commandline arguments, and stores the tiles and size of the puzzle board and potential and subsequent boards throughout puzzle play */
class Board
{
 public:
  /**  Default constructor, makes a sorted 2x2 board */
  Board(); 

  /** Init a board of given size and scramble it with numInitMoves 
   * by moving the space tile with a randomly chosen direction N, W, S, E
   * some of which may be invalid, in which case we skip that move */
  Board(int size, int numInitMoves, int seed);

  /** Copy constructor */
  Board(const Board &b);

  /** Another kind of "copy" constructor */
  Board(int *tiles, int size); 

  /** Default destructor */
  ~Board();

  /** Swaps the blank with the specified tile */
  bool move(int tile);

  /** Generate potential moves and returns new boards */
  std::map<int, Board*> potentialMoves(); 

  /** Checks to see if board is in solved state */
  bool solved();

  /** Prints board */
  friend std::ostream& operator<<(std::ostream &os, const Board &b);
  /** Checks to see if two boards are the same */
  bool operator==(const Board& rhs) const;
  /** Checks to see if one board is smaller than another */
  bool operator<(const Board& rhs) const;
  /** Checks to see if two boards are different */
  bool operator!=(const Board& rhs) const;
  
  /** Accessor function for tiles in board */
  int* getTiles();
  /** Accessor function for size of board */
  int getSize();

 private:
  /** Tiles in board */
  int *tiles_;
  /** Size of board, i.e. number of tiles in board */
  int size_;
  /** Board pointer for copy constructors */
  Board *newBoard_;
  /** Map to store potential moves, with Key=tile that is moved, Value=Ptr to resulting Board */
  std::map<int, Board*> boardMap_;

};

/** BoardLessThan defines how to compare Board*s */
struct BoardLessThan : 
  public std::binary_function<const Board*, const Board*,bool>
{
  /** Compares Board*s
   * @param b1 First Board* to compare
   * @param b2 Second Board* to compare
   * @return true if b1 is less than b2, false otherwise */
  bool operator()(const Board *b1, const Board *b2) const
  {
    return *b1 < *b2;
  }
};


#endif
