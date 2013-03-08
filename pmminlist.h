#ifndef PMMINLIST_H
#define PMMINLIST_H
#include <list>

/**
 * PMMinList implements a sorted list of PuzzleMoves
 * based on their f-score (from smallest to largest)
 */
class PMMinList 
{
 public:
  
  PMMinList();
  ~PMMinList();
  /** Returns the size of items in the list */
  int size() const { return slist_.size(); }
  /** Returns true if the list is empty */
  bool empty() const { return slist_.empty(); }
  /** Adds a puzzle move to the sorted list */
  void push(PuzzleMove* pm);
  /** Removes the minimum scored (front) puzzle move */
  void pop();
  /** Returns the PuzzleMove with the lowest score */
  PuzzleMove* top();
 private:
  /** the sorted list */
  std::list<PuzzleMove*> slist_;
};

#endif
