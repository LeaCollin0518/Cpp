#include <iostream>
#include <stdlib.h>
#include <functional>

using namespace std;

//all function headers here
class IComparer;
class LessThanComparer;
class GreaterThanComparer;
class IsClosestToComparer;

typedef bool(*compFunction)(int, int);

void sortWithPointers(int *p, int length, bool (*compFunction)(int,int));
void sortWithInterfaces(int *p, int length, IComparer & ic);
void sortWithStandardFunction(int *p, int length, function<bool(int, int)> closestTo);

function<bool(int, int)> generateNearestTo (int center);

void swap(int &a, int &b);

bool isLessThan(int a, int b);
bool isGreaterThan(int a, int b);

void testSortWithPointers();
void testSortWithInterfaces();
void testSortWithLambdas();

//main class that calls all the testing methods
int main(){
	
	testSortWithPointers();
	testSortWithInterfaces();
	testSortWithLambdas();	

}

//IComparer class
class IComparer{
public:
	virtual bool isBefore(int a, int b) = 0;	
};

//LessThanComparer class
class LessThanComparer : public IComparer{
public:
	bool isBefore(int a, int b){
		return a < b;
	}
};

//GreaterThanComparer class
class GreaterThanComparer : public IComparer{
public:
	bool isBefore(int a, int b){
		return a > b;
	}
};

//IsClosestToComparer class
class IsClosestToComparer : public IComparer{
public:
	IsClosestToComparer(int c){
		center = c;	
	}
	bool isBefore(int a, int b){
		return ((abs(a - center)) < (abs(b - center)));
	}

private:
	int center;
	
};


//sortWithPointers method
void sortWithPointers(int* p, int length, bool (*compFunction)(int,int)){
	for(int i=0; i<length; i++){
		for(int j=0; j<length-1; j++){
			if(compFunction(*(p+j+1), *(p+j))){
				swap(*(p+j), *(p+j+1));
			}
		}
	}
}

//sortWithInterface method
void sortWithInterfaces(int* p, int length, IComparer &ic){
	for(int i=0; i<length; i++){
		for(int j=0; j<length-1; j++){
			if(ic.isBefore(*(p+j+1), *(p+j))){
				swap(*(p+j), *(p+j+1));
			}
		}
	}
}

//helper swap method
void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

//simple isLessThan method
bool isLessThan(int a, int b){
	return a < b;
}

//simple isGreaterThan method
bool isGreaterThan(int a, int b){
	return a > b;
}

//generateNearestTo function
function<bool(int, int)> generateNearestTo(int center){
	return [center] (int a, int b) {
		return ((abs(a - center)) < (abs(b - center)));
	};
}

//sortWithStandardFunction method
void sortWithStandardFunction(int *p, int length, function<bool(int, int)> closestTo){
	for(int i=0; i<length; i++){
		for(int j=0; j<length-1; j++){
			if(closestTo(*(p+j+1), *(p+j))){
				swap(*(p+j), *(p+j+1));
			}
		}
	}
}

//all testing methods create a random array of size 10
//testSortWithPointers method
void testSortWithPointers(){
	int list [10];
	int length = sizeof(list)/sizeof(list[0]);

	for(int i = 0; i < length; i++){
		list[i] = rand() % (10+1);
	}
		
	cout << "Initial List: " << endl;

	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}

	sortWithPointers(list, length, isLessThan);
		
	cout << "Increasing List: " << endl;

	
	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}	

	sortWithPointers(list, length, isGreaterThan);

	cout << "Decreasing List: " << endl;

	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}
}

//testSortWithInterfaces method
void testSortWithInterfaces(){
	int list [10];
	int length = sizeof(list)/sizeof(list[0]);	

	LessThanComparer less;
	GreaterThanComparer greater;
	IsClosestToComparer  closest = IsClosestToComparer(3);

	for(int i = 0; i < length; i++){
		list[i] = rand() % (10+1);
	}
		
	cout << "Initial List: " << endl;

	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}

	sortWithInterfaces(list, length, less);	
	
	cout << "Increasing List: " << endl;

	
	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}	

	sortWithInterfaces(list, length, greater);
	
	cout << "Decreasing List: " << endl;

	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}

	sortWithInterfaces(list, length, closest);

	cout << "Closest List: " << endl;

	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}
}

//testSortWithStandardFunction method
void testSortWithLambdas(){
	int list [10];
	int length = sizeof(list)/sizeof(list[0]);

	for(int i = 0; i < length; i++){
		list[i] = rand() % (10+1);
	}
		
	cout << "Initial List: " << endl;

	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}

	sortWithStandardFunction(list, length, generateNearestTo(3));		

	cout << "Closest List: " << endl;

	
	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}	

	sortWithStandardFunction(list, length, generateNearestTo(10));

	cout << "Decreasing List: " << endl;

	for(int i = 0; i < length; i++){
		cout << list[i] << endl;
	}
}
