#include <iostream>
#include <algorithm>
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
	os << obj._re << "+" << obj._im << "i"; 
    return os;
}

bool operator>(const Complex& lhs, const Complex& rhs) //comparison operators
{
	return (lhs._re > rhs._re);
}

bool operator<(const Complex& lhs, const Complex& rhs)
{
	return !(lhs > rhs);
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
	return( (lhs._re == rhs._re) && (lhs._im == rhs._im) );
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs==rhs);
}

//---------------------------------------------------------  END OF COMPLEX NUMBER FUNCTIONS  ----------------------------------------------------

//----------------------------------------------------  DEFINITION OF DATE CLASS & OPERATOR FUNCTIONS  -------------------------------------------

class Date
{
	public:
	
	int _dd;
	int _mm;
	int _yy;
	
	Date(): _dd(1), _mm(1), _yy(1970)
	{
		
	}
	
	Date(int dd, int mm, int yy): _dd(dd), _mm(mm), _yy(yy)
	{
		if(_dd >=0 && _mm>=0 && _yy>=0) //check if all values are nonnegative
		{
			if(_mm >= 1 && _mm <= 12) //check for legal month field value
			{
				int maxday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
				if(_yy % 400 == 0)
					maxday[1] = 29; //accounting for leap years
				
				if(_dd == 0 || _dd > maxday[_mm - 1])
					throw "Error: day field value outside allowed limits";
			}
			
			else
				throw "Error: month must be between 1 and 12";
		}
		
		else
			throw "Error: day, month and year fields must all be nonnegative values";
	}
};

std::istream& operator>>(std::istream& is, Date& obj) //getting object of type 'Date' as input
{
    // write obj to stream
	cout<<"Enter day: ";
	is >> obj._dd;
	cout<<"Enter month: ";
	is >> obj._mm;
	cout<<"Enter year: ";
	is >> obj._yy;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Date& obj) //printing object of type 'Date' as output
{
    // write obj to stream
	os << obj._dd << "-" << obj._mm << "-" << obj._yy; 
    return os;
}

bool operator>(const Date& lhs, const Date& rhs)
{
	return ((lhs._yy > rhs._yy) || ((lhs._yy == rhs._yy)&&(lhs._mm > rhs._mm)) || ((lhs._yy == rhs._yy)&&(lhs._mm == rhs._mm)&&(lhs._dd == rhs._dd)));
}

bool operator<(const Date& lhs, const Date& rhs)
{
	return !(lhs > rhs);
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return ((lhs._dd == rhs._dd) && (lhs._mm == rhs._mm) && (lhs._yy == rhs._yy));
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}

//---------------------------------------------------------  END OF DATE CLASS FUNCTIONS  --------------------------------------------------------

//---------------------------------------------------------  SPARSE ELEMENT TEMPLATE CLASS -------------------------------------------------------


template<typename T>
class SparseElement
{
	int _index; //index at which this element exists in the array (conceptually)
	T _element; //pointer to the location storing the actual element data
	SparseElement<T> *_next;
	SparseElement<T> *_prev;
	
	template<typename V> friend class SparseArray;
		
	public:
	
	SparseElement(int index): _index(index), _next(nullptr), _prev(nullptr)
	{
		
	}
	
	SparseElement(int index, T obj):  _index(index), _element(obj), _next(nullptr), _prev(nullptr)
	{
		
	}
	
	template<class V> bool friend operator>(const SparseElement<V>& lhs, const V& rhs);
	template<class V> bool friend operator<(const SparseElement<V>& lhs, const V& rhs);
	template<class V> bool friend operator==(const SparseElement<V>& lhs, const V& rhs);
	template<class V> bool friend operator!=(const SparseElement<V>& lhs, const V& rhs);
	template<class V> bool friend operator>(const SparseElement<V>& lhs, const SparseElement<V>& rhs);
	template<class V> bool friend operator<(const SparseElement<V>& lhs, const SparseElement<V>& rhs);
	template<class V> bool friend operator==(const SparseElement<V>& lhs, const SparseElement<V> & rhs);
	template<class V> bool friend operator!=(const SparseElement<V>& lhs, const SparseElement<V> & rhs);
	template<class V> friend std::istream& operator>>(std::istream& is, SparseElement<V>& obj);
	template<class V> friend std::ostream& operator<<(std::ostream& os, const SparseElement<V>& obj);
};

template<typename T>
bool operator>(const SparseElement<T>& lhs, const T& rhs)
{
	return (lhs._element > rhs);
}

template<typename T>
bool operator<(const SparseElement<T>& lhs, const T& rhs)
{
	return !(lhs > rhs);
}

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

template<typename T>
bool operator>(const SparseElement<T>& lhs, const SparseElement<T>& rhs)
{
	return (lhs._element > rhs._element);
}

template<typename T>
bool operator<(const SparseElement<T>& lhs, const SparseElement<T>& rhs)
{
	return !(lhs > rhs);
}

template<typename T>
bool operator==(const SparseElement<T>& lhs, const SparseElement<T>& rhs)
{
	return (lhs._element == rhs._element);
}

template<typename T>
bool operator!=(const SparseElement<T>& lhs, const SparseElement<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
std::istream& operator>>(std::istream& is, SparseElement<T>& obj) //getting object of generic type SparseElement as input
{
    // write obj to stream
	cout<<"Enter index: ";
	is >> obj._index;
	cout<<"Enter element data - "<<endl;
	is >> obj._element;
    return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const SparseElement<T>& obj) //printing object of generic type SparseElement as output
{
    // write obj to stream
	os << obj._element; 
    return os;
}

//----------------------------------------------------  END of SPARSE ELEMENT TEMPLATE CLASS  ------------------------------------------------ 

//----------------------------------------------------  MAIN SPARSE ARRAY TEMPLATE CLASS  ---------------------------------------------------


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
	
	T& operator[] (const int index) //RETURNS LVALUE: operator overloading for [] brackets
	{
		if(index >= 0 && index < _size)
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
						//cout<<"node found\n";
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
							//cout<<"updated head"<<endl;
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
					
					//cout<<"updated tail"<<endl;
					_tail = new_el;
					return (*new_el)._element;
				}
			}
			
			else
			{
				//cout<<"first node created"<<endl;
				SparseElement<T> *new_el = new SparseElement<T>(index);
				_head = new_el;
				_tail = new_el;
				return (*_head)._element;
			}
		}
		
		else
			throw "Error: index out of range";
	}
	
	const T& operator[] (const int index) const //RETURNS RVALUE: operator overloading for [] brackets
	{
		if(index >= 0 && index < _size)
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
						cout<<"node found: value returned"<<endl;
						return (*trav)._element;
					}
					
					else if(trav->_index > index)
					{
						cout<<"non-empty, didn't reach end: empty returned"<<endl;
						T new_el;					
						return new_el;
					}
				}
				
				else
				{
					cout<<"reached end of array: index not found"<<endl;
					T new_el;
					return new_el;
				}
			}
			
			else
			{
				cout<<"empty array: no nodes created"<<endl;
				T new_el;
				return new_el;
			}
		}
		
		else
			throw "Error: index out of range";
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
				cout<<*trav;
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
	
	void sort()
	{
		if(_head)
		{
			if(_head!=_tail) //i.e. if array has more than one element
			{
				SparseElement<T> *trav = _head->_next;
				//cout<<"Start: "<<trav->_index<<endl;
				
				while(trav)
				{
					SparseElement<T> *trav2 = trav->_prev;
					SparseElement<T> *trav3 = trav2;
					SparseElement<T> *trav5 = trav->_next; //we need to keep a hold on trav's next so we can assign trav to this after everything is done
					
					//cout<<"preceded by index: "<<trav3->_index<<endl;
					
					while(trav2 && *trav2 > *trav) //_element needs to support < and > operators
					{
						//cout<<"trav2 is now at "<<trav2->_index<<endl;
						trav2 = trav2->_prev;
					}
					
					if(trav2) //general case; trav is not the smallest element so far
					{
						if(trav2 != trav3) //i.e. if there exist one or more elements before trav whose index is greater than trav's
						{							
							//cout<<"general case: trav2 topped at "<<trav2->_index;
							trav->_prev->_next = trav->_next; //if trav is tail, this will become NULL; else it goes to trav's next
							if(trav->_next) trav->_next->_prev = trav->_prev; //if trav is not tail, this happens
							
							if(trav == _tail)
								_tail = trav->_prev;
							
							SparseElement<T> *trav4 = trav2->_next; //trav has to be inserted between trav2 and trav4
							trav4->_prev = trav;
							trav2->_next = trav;
							trav->_prev = trav2;
							trav->_next = trav4;
						}
						
						else //i.e. trav is the largest element so far
						{
							cout<<"largest element so far: trav2 didn't move\n";
							//do nothing; trav doesn't have to be shifted
						}
					}
					else //trav is the smallest element so far, so trav2 has passed even head and gone to NULL; update head
					{
						//cout<<"smallest element so far\n";
						trav->_prev->_next = trav->_next;
						if(trav->_next) trav->_next->_prev = trav->_prev;
						
						if(trav == _tail)
							_tail = trav->_prev;
						
						trav->_prev = nullptr;
						trav->_next = _head;
						_head->_prev = trav;
						_head = trav;
					}
					
					trav = trav5;
				}
				
				//loop through entire DLL once again and change indices to 0, 1, 2 etc.
				trav = _head;
				int ind = 0;
				while(trav)
				{
					trav->_index = ind;
					++ind;
					trav = trav->_next;
				}
			}
			
			else
			{
				//array has only one element; shift its index to 0
				_head->_index = 0;
			}
		}
		
		else
		{
			cout<<"Array empty: no sort possible\n";
		}
	}
	
	int search(T search_el)
	{
		if(_head)
		{
			SparseElement<T> *trav = _head;
			while(trav && *trav != search_el)
				trav = trav->_next;
			
			if(trav) //element found
			{
				return trav->_index;
			}
			
			else //element not found: trav passed tail and went to NULL
			{
				return -1;
			}
		}
		
		else
			return -1;//array is empty; return -1
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
			return (*p_it_)._element;
		}
		Iterator& operator++() // pre
		{
			p_it_ = p_it_->_next;
			return *this;
		}
		/*Iterator& operator--() // pre
		{
			p_it_ = p_it_->_prev;
			return *this;
		}*/
		Iterator operator++(int) // post
		{
			Iterator temp(*this);
			++*this;
			return temp;
		}
		/*Iterator operator--(int) // post
		{
			Iterator temp(*this);
			--*this;
			return temp;
		}*/
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
    // generic find: returns iterator to elemnt
    // present in sparse array else returns end()
    // template<class InputIterator, class T>
    /*Iterator find(Iterator first, Iterator last, const T &val)
    {
        while (first!=last) 
        {
        if (*first==val) return first;
        ++first;
        }
        return last;
    }*/
};

int main()
{
    cout << endl << endl;
	/*
	//TEST SNIPPET 1
	Complex a(5,6);
	Complex a2(6,7);
	cin >> a;
	cout<<a<<endl; //this prints the complex number in the format (a + ib)
	SparseElement<Complex> s1(5, a), s2(6, a), s3(5,a2);
	cout<<(s1 == s2)<<endl;
	cout<<(s1 == s3)<<endl;
	cout<<(s1 == a)<<endl;
	cout<<(s1 == a2)<<endl;
	
	Date a3(5,6,1972);
	Date a4(5,6,1974);
	cin >> a3;
	cout<<a2<<endl; //this prints the date in the format (dd-mm-yy)
	SparseElement<Date> sd1(5, a3), sd2(6, a3), sd3(5, a4);
	cout<<(sd1 == sd2)<<endl;
	cout<<(sd1 < sd3)<<endl;
	cout<<(sd1 == a3)<<endl;
	cout<<(sd1 == a4)<<endl;
	cout<<(a3 > a4)<<endl;
	*/
	
	/*
	//TEST SNIPPET 2
	SparseElement<int> b(4, 5);	
	cout<< (b==7) << endl;
	*/
	
	/*
	//TEST SNIPPET 3
	SparseArray<int> c(10);
	//c.display();
	c[4] = 4; //first node created
	c[4] = 5; //node found
	c[2] = 7; //updated head
	c[7] = 9; //updated tail
	c[8] = 8; //updated tail
	c[5] = 19;
	c.display();
	SparseArray<int>:: Iterator it;
    int ser = 8;

    it = find(c.begin(), c.end(), ser);
    if (it != c.end())
        std::cout << "Element " << *it << " found in sparse array..! " << endl;
    else
        std::cout << "Element " << ser << " not found in sparse array..!"<< endl;
	it = c.begin();
	/*while(it != c.end())
	{
		cout << *it;
		cout << endl;
		++it;
	}*/
    
	
	
	/*
	//TEST SNIPPET 4
	SparseArray<Complex> d(10);
	d.display();
	d[4] = Complex(4,8); //first node created
	d[4] = Complex(4,9); //node found
	d[2] = Complex(2,4); //updated head
	d[7] = Complex(7,14); //updated tail
	d[8] = Complex(8,16); //updated tail
	d[5] = Complex(5,10);
	
	d[5] = d[8];
	d[5] = d[9]; //first initializes d[9] to default value as it hasn't been created yet; then performs assignment
	
	d.display();

    SparseArray<Complex>:: Iterator it;
    Complex ser(2,4);

    it = find(d.begin(), d.end(), ser);
    if (it != d.end())
        std::cout << "Element " << *it << " found in sparse array..! " << endl;
    else
        std::cout << "Element " << ser << " not found in sparse array..!"<< endl;

	/*cout<<"##"<<endl;
	//this will iterate over the whole array and initialize every node; not recommended
	//as it then becomes much more inefficient than a normal random access array
	//and loses the advantage of space efficiency as well
	for(int i=0; i<10; i++)
	{
		cout<<d[i]<<" ";
	}
	cout<<endl<<"##"<<endl;
	d.display();
	d.sort();
	d.display();
	
	try
	{
	d[10] = Complex(10,20);
	}
	catch (const char *msg)
	{
		cerr<<msg<<endl; //Error: index out of range
	}
	*/
	
	
	//TEST SNIPPET 5
	SparseArray<Date> e(10);
	e.display();
	//e.sort();
	e[4] = Date(5,6,1982);
	e[2] = Date();
	e[7] = Date(15,3,1969);
	e[6] = e[7];
	e[3] = e[2];
	e.display();
    Date ser(15,3,1969);
    SparseArray<Date>:: Iterator it;

    it = find(e.begin(), e.end(), ser);
    if (it != e.end())
        std::cout << "Element " << *it << " found in sparse array..! " << endl;
    else
        std::cout << "Element " << ser << " not found in sparse array..!"<< endl;

    /*
	cout<<(e[4]==Date(5,6,1982))<<endl;
	e.sort();
	cout<<e.search(Date(5,6,1982))<<endl;
	cout<<e.search(Date(5,6,1782))<<endl;
	e.display();
    */

   cout << endl << endl;
   return 0;   
}