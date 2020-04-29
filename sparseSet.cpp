#include <cstdlib>
#include <iostream>
using namespace std;

//------------------------------------  DEFINITION OF COMPLEX NUMBER CLASS AND INPUT-OUTPUT STREAM OVERLOADING  -----------------------------

class Complex
{
	public:
	
	int _re;
	int _im;
	
	Complex(): _re(0), _im(0)
	{
	}
	
	Complex(int re, int im): _re(re), _im(im)
	{
	}
	
};

bool operator==(const Complex& lhs, const Complex& rhs)
{
	return( (lhs._re == rhs._re) && (lhs._im == rhs._im) );
}

std::istream& operator>>(std::istream& is, Complex& obj) //getting object of type 'Complex' as input
{
    // write obj to stream
	cout<<"Enter real: ";
	is >> obj._re;
	cout<<"Enter imag: ";
	is >> obj._im;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Complex& obj) //printing object of type 'Complex' as output
{
    // write obj to stream
	os << obj._re << " + " << obj._im << "i" << endl; 
    return os;
}

//---------------------------------------------------------  END OF COMPLEX NUMBER FUNCTIONS  ----------------------------------------------------

//---------------------------------------------------------  SPARSE ELEMENT TEMPLATE CLASS -------------------------------------------------------

template<typename T>
class SparseElement
{
	int _index; //index at which this element exists in the array (conceptually)
	T _element; //pointer to the location storing the actual element data
	SparseElement<T> *_next;
	SparseElement<T> *_prev;
	
	template<typename V> friend class SparseArray;
	friend class Iterator;
		
	public:
	
	SparseElement(int index): _index(index), _next(nullptr), _prev(nullptr)
	{
		
	}
	
	SparseElement(int index, T obj):  _index(index), _element(obj), _next(nullptr), _prev(nullptr)
	{
		
	}
	
	template<class V> bool friend operator==(const SparseElement<V>& lhs, const V& rhs);
	template<class V> bool friend operator!=(const SparseElement<V>& lhs, const V& rhs);
};

template<typename T>
bool operator==(const SparseElement<T>& lhs, const T& rhs)
{
	return (lhs._element == rhs);
}

template<typename T>
bool operator!=(const SparseElement<T>& lhs, const T& rhs)
{
	return !(lhs == rhs);
}

//----------------------------------------------------  END of SPARSE ELEMNT TEMPLATE CLASS  ------------------------------------------------ 

//----------------------------------------------------  MAIN SPARSE ARRAY TEMPLATE CLASS  ---------------------------------------------------

template<typename T>
class SparseArray
{
	int _size;
	SparseElement<T> *_head;
	SparseElement<T> *_tail;

	//friend class Iterator;
	
	public:
	
	SparseArray(int size): _size(size), _head(nullptr), _tail(nullptr)
	{
		
	}
	
	T& operator[] (const int index) //RETURNS LVALUE: operator overloading for [] brackets
	{
		if(_head)
		{
			SparseElement<T> *trav = _head;
			while(trav && trav->_index < index) //searches for element at given index if it exists
			{
				trav = trav->_next;
			}
			
			if(trav)
			{
				//if node with the correct index was found, i.e. this node already exists
				if(trav->_index == index)
				{
					cout<<"node found\n";
					return (*trav)._element;
				}
				
				else if(trav->_index > index)
				{
					//initialize new node
					SparseElement<T> *new_el = new SparseElement<T>(index);
					
					//hook up the pointers
					new_el->_next = trav;
					new_el->_prev = trav->_prev;
					if(trav->_prev) trav->_prev->_next = new_el;
					trav->_prev = new_el;
					
					//updating head and tail if element is inserted at beginning or end
					if(new_el->_prev==nullptr)
					{
						cout<<"updated head"<<endl;
						_head = new_el;
					}
					
					return (*new_el)._element;
				}
			}
			
			else
			{
				//initialize new node
				SparseElement<T> *new_el = new SparseElement<T>(index);
				
				//hook it up to the tail because this must be the biggest index value yet
				_tail->_next = new_el;
				new_el->_prev = _tail;
				
				cout<<"updated tail"<<endl;
				_tail = new_el;
				return (*new_el)._element;
			}
		}
		
		else
		{
			cout<<"first node created"<<endl;
			SparseElement<T> *new_el = new SparseElement<T>(index);
			_head = new_el;
			_tail = new_el;
			return (*_head)._element;
		}
	}
   
	const T& operator[] (const int index) const //RETURNS RVALUE: operator overloading for [] brackets
	{
		
	}
	
	void display()
	{
		if(_head)
		{
			//print out empty spaces from 0 till the first filled index of the array
			for(int i = 0; i<_head->_index; i++)
				cout<<"[ ],";
			
			SparseElement<T> *trav = _head;
			while(trav)
			{
				
				if(trav!=_head)
				{
					int diff = trav->_index - (trav->_prev->_index);
					
					for(int i=1; i<diff; i++)
						cout<<"[ ],";
				}
				cout<<trav->_element;
				if(trav!=_tail)
					cout<<",";
				
				trav = trav->_next;
			}
			
			if(_tail->_index != (_size - 1))
				cout<<",";
			
			//print out empty spaces from the last filled index of the array to the (size-1)th index
			for(int i = _tail->_index + 1; i<_size; i++)
			{
				cout<<"[ ]";
				if(i != (_size-1))
					cout<<",";
			}
			
			cout<<endl;
		}
		
		else
			cout<<"Array is currently empty\n";
	}
	class Iterator
	{
		//friend class SparseArray;
		//template<typename V> friend class SparseArray;
		public:
		explicit Iterator(SparseElement<T> *p_it = nullptr) : p_it_(p_it){}
		bool operator==(const Iterator& rhs) const
		{
			return p_it_ == rhs.p_it_;
		}
		bool operator!=(const Iterator& rhs) const
		{
			return !(*this == rhs);
		}
		T operator*() 
		{
			return *p_it_;
		}
		Iterator& operator++() // pre
		{
			p_it_ = p_it_->next;
			return *this;
		}
		Iterator operator++(int) // post
		{
			Iterator temp(*this);
			++*this;
			return temp;
		}
		private:
		SparseElement<T> *p_it_;
	};
	Iterator begin()
	{
		return Iterator(_head);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}	
};

int main()
{
	
	//TEST SNIPPET 1
	Complex a(5,6);
	cout << a << endl;
	cin >> a;
	cout<<a<<endl; //this prints the complex number in the format (a + ib)
	SparseElement<Complex> s1(5, a), s2(6, a);
	cout<<(s1 != a)<<endl<<endl<<endl;
	
	
	
	//TEST SNIPPET 2
	SparseElement<int> b(4, 5);	
	cout<< (b==7) << endl<<endl<<endl;
	
	
	//TEST SNIPPET 3
	SparseArray<int> c(10);
	c.display();
	c[4] = 4; //first node created
	c[4] = 5; //node found
	c[2] = 7; //updated head
	c[7] = 9; //updated tail
	c[8] = 8; //updated tail
	c[5] = 19;

	c.display();
	SparseArray<int>:: Iterator it;
	it = c.begin();
	while(it != c.end())
	{
		cout << *it;
		cout << endl;
		++it;
	}

}