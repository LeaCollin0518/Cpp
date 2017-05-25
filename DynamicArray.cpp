#include <iostream>

using namespace std;

template <class T> class DynamicArray;
template <class T> class DynamicArrayIterator;

//DynamicArray Class
template <class T>
class DynamicArray{
public:
	//constructor
	DynamicArray();
	//destructor
	~DynamicArray();

	//overloaded [] operator
	T& operator [](int index);

	//add, size, and remove methods
	void add(T item);
	int size();
	T remove(int i);

	//methods that will return iterators
	DynamicArrayIterator<T> begin();
	DynamicArrayIterator<T> end();

	DynamicArrayIterator<T> r_begin();
	DynamicArrayIterator<T> r_end();

private:

	T *array;
	int capacity;
	int current;
};

//constructor sets initial capacity to size 10, current position to 0, and initializes array to have size 10
template<class T>
DynamicArray<T>::DynamicArray(){
	capacity = 10;
	current = 0;
	array = new T[10];
}

//frees memory of backend array, sets memory to null 
template<class T>
DynamicArray<T>::~DynamicArray(){
	if(array){
		delete array;
		array = NULL;
	}
}

//returns current which is the number of elements in the array
template<class T>
int DynamicArray<T>::size(){
	return current;
}

//if current is greater than or equal to capacity, need to copy array to a new, bigger array with double the capacity
//then simply add item to current position and increment current
template<class T>
void DynamicArray<T>::add(T item){
	if(current >= capacity){
		T *newArray;
		newArray = new T[capacity*2];
		copy(array, array+capacity, newArray); 
		capacity *=2;
		array = newArray;		
	}

	*(array + current) = item;
	current++;

}

//return value at array[index]
template<class T>
T& DynamicArray<T>::operator [](int i){
        return array[i];
}

//remove and return element at i
//shifts all elements after the removed element to the left
template<class T>
T DynamicArray<T>::remove(int i){
	const T temp = array[i];

	if(current == 1){
		array[i] = NULL;
	}
	else{
		for(int pos = i; pos < current - 1; pos++){
			array[pos] = array[pos+1];
		}

	}

	current--;
	return temp;
}

//returns an iterator, forward iterator at begin so position is 0 and direction is 1 (forward)
template<class T>
DynamicArrayIterator<T> DynamicArray<T>::begin(){
	DynamicArrayIterator<T> begin = DynamicArrayIterator<T>(this, 0, 1);
	return begin;
}

//end iterator so it needs to be one past last element in array which is position current
template<class T>
DynamicArrayIterator<T> DynamicArray<T>::end(){
	DynamicArrayIterator<T> end = DynamicArrayIterator<T>(this, current, 1);
	return end;
}

template<class T>
DynamicArrayIterator<T> DynamicArray<T>::r_begin(){
	DynamicArrayIterator<T> r_begin = DynamicArrayIterator<T>(this, (current-1), -1);
	return r_begin;
}

template<class T>
DynamicArrayIterator<T> DynamicArray<T>::r_end(){
	DynamicArrayIterator<T> r_end = DynamicArrayIterator<T>(this, -1, -1);
	return r_end;
}

/*
*
*
*
	Start of DynamicArrayIterator Class
*
*
*
*/

template<class T>
class DynamicArrayIterator{
private:
        int currentPosition;
        DynamicArray<T> *array;
        int direction;


public:
	//constructor
	DynamicArrayIterator(DynamicArray<T> *arr, int curr, int dir);

	//overloaded operators
	T& operator* ();
	void operator++ ();
	bool operator== (DynamicArrayIterator<T> a);
	bool operator!= (DynamicArrayIterator<T> a);

};

//constructor
template<class T>
DynamicArrayIterator<T>::DynamicArrayIterator(DynamicArray<T> *arr, int curr, int dir){
	array = arr;
	currentPosition = curr;
	direction = dir;
}

template<class T>
T& DynamicArrayIterator<T>::operator*(){
	return (*array)[currentPosition];
}

template<class T>
void DynamicArrayIterator<T>::operator++(){
	if(direction == 1){
		currentPosition++;
	}
	else{
		currentPosition--;
	}

}

template<class T>
bool DynamicArrayIterator<T>::operator==(DynamicArrayIterator<T> a){
	if(this->currentPosition == a.currentPosition){
		return true;
	}
	else{
		return false;
	}
}

template<class T>
bool DynamicArrayIterator<T>::operator!=(DynamicArrayIterator<T> a){
	if(this->currentPosition != a.currentPosition){
		return true;
	}
	else{
		return false;
	}
}

int main(){

	DynamicArray<int> foo;

	for(int i = 0; i < 15; i++){
		foo.add(i);
	}

	foo[5] = 69;	

	for(DynamicArrayIterator<int> a = foo.begin(); a!=foo.end(); ++a){
		cout << *a << endl;
	}	

	for(DynamicArrayIterator<int> a = foo.r_begin(); a!=foo.r_end(); ++a){
		cout << *a << endl;
	}
		
	return 0;
}
