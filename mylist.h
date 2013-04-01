//mylist.h written by Erika Johnson 2/17/13

#ifndef MYLIST_H
#define MYLIST_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <vector>

using namespace std;

/** Templated dynamically allocated unbounded array list */
template <typename T>
class MyList {
public:
  MyList();
  ~MyList();
  void pushBack(T val);
  int getSize();
  int whereAt();
  T& getVal(int loc);
  bool remove(T val);
  T& operator[](int loc);
private:
  int _size;
  int _at;
  T *_list;
};

/** Constructor, creates empty list */
template <typename T>
MyList<T>::MyList(){
  _size = 1;
  _at = 0;
  _list = new T[_size]; //dynamically allocates array
}

/** Destructor, deletes list */
template <typename T>
MyList<T>::~MyList(){
  delete [] _list;
}

/** Adds item to list
 * @param val Value to add to list */
template <typename T>
void MyList<T>::pushBack(T val){
  if (_at == _size){ //no more allocated capacity for new items in list
    T *tempbuf = _list; //keep copy of pointer to existing list
    _size *= 2;
    _list = new T[_size]; //dynamically allocate an array with twice the capacity of the previous list
   for (int i=0; i<_at; i++){
     _list[i] = tempbuf[i]; //copy previous list items into new list
   }
   delete [] tempbuf; //free up memory taken up by the previous list
  }
  _list[_at++] = val; //add val to list and increment location of last item in list
}

/** Returns allocated size (capacity) of list
 * @return allocated size (capacity) of list */
template <typename T>
int MyList<T>::getSize(){
  return _size;
}

/** Returns location of last item in list
 * @return location of last item in list */
template <typename T>
int MyList<T>::whereAt(){
  return _at;
}

/** Returns reference to value at given location in list
 * @param loc Location of value to return
 * @return reference to value at given location in list */
template <typename T>
T& MyList<T>::getVal(int loc){
  if (loc >= _at || loc < 0){
   throw std::invalid_argument("That location is invalid!");
  }
  return _list[loc];
}

/** Removes item from list
 * @param val Value of item to remove
 * @return true if value was successfully removed, false if value not found */
template<typename T>
bool MyList<T>::remove(T val){
  for (int i=0; i<_at; i++){
    if (_list[i]==val){
      for (int j=i; j<--_at; j++){
	_list[j] = _list[j+1];
      }
      return true;
    }
  }
  return false;
}

/** Does same thing as getVal() function
 * @param loc Location of value to return
 * @return reference to value at given location in list */
template<typename T>
T& MyList<T>::operator[](int loc){
  if (loc >= _at || loc < 0){
    throw std::invalid_argument("That location is invalid!");
  }
  return _list[loc];
}

#endif
