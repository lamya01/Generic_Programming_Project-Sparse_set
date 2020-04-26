#include <stdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class Complex
{
	int re;
	int im;
};

template<typename T>
class SparseElement
{
	int _index; //index at which this element exists in the array (conceptually)
	T _element; //pointer to the location storing the actual element data
	SparseElement<T> *next;
	SparseElement<T> *prev;
	
	friend class SparseArray;
		
	public:
	
	SparseElement(int ind, T obj):  _index(index), _element(obj), _next(nullptr), _prev(nullptr)
	{
		
	}
	
	
};

template<typename T>
class SparseArray
{
	int _size;
	SparseElement<T> *_head;
	SparseElement<T> *_tail;
	
	public:
	
	SparseArray(int size): _size(size), _head(nullptr), _tail(nullptr)
	{
		
	}
	
	int& operator[] (const int index) //RETURNS LVALUE: operator overloading for [] brackets
	{
		
	}
   
	const int operator[] (const int index) const //RETURNS RVALUE: operator overloading for [] brackets
	{
		
	}
};

int main()
{
	
}