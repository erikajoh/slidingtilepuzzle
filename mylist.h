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

//templated dynamically allocated unbounded array list
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

template <typename T>
MyList<T>::MyList(){
  _size = 1;
  _at = 0;
  _list = new T[_size]; //dynamically allocates array
}

template <typename T>
MyList<T>::~MyList(){
  delete [] _list;
}

//adds item to list
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

//returns allocated size (capacity) of list
template <typename T>
int MyList<T>::getSize(){
  return _size;
}

//returns location of last item in list
template <typename T>
int MyList<T>::whereAt(){
  return _at;
}

//returns reference to value at given location in list
template <typename T>
T& MyList<T>::getVal(int loc){
  if (loc >= _at || loc < 0){
   throw std::invalid_argument("That location is invalid!");
  }
  return _list[loc];
}

//removes item from list
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

//does same thing as getVal() function
template<typename T>
T& MyList<T>::operator[](int loc){
  if (loc >= _at || loc < 0){
    throw std::invalid_argument("That location is invalid!");
  }
  return _list[loc];
}

#endif
