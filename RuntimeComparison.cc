#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
using namespace std;

void bubbleSort(int *p, int length);
void swap(int &a, int &b);
void mergeSort(int* arr, int size);
void merge(int *arr, int* arr1, int* arr2, int size1, int size2);

int main(){
	clock_t t1;
	clock_t t2;

	//file that will contain table outputted by program
	ofstream out("table.txt");

	//variables to help with table formatiing
	const char separator = ' ';
	const int nameWidth = 6;
	const int numWidth = 8;

	//chose i to go up to 40960 as bubbleSort will start to take about 8 seconds for arrays of this length
for(int i=10; i<=40960; i = i*2){
	int list1 [i];
	int list2 [i];
	
	int *p = &list1[0];
	int *q = &list2[0];

	srand(time(NULL));	

	//populating the arrays with random numbers
	for(int j=0; j<i; j++){
		list1[j] = rand() % (i + 1);
	}


	int length = sizeof(list1)/sizeof(list1[0]);	

	std::copy(list1, list1 + length, list2);

	t1 = clock();
	mergeSort(p, length);	
	t1 = clock() - t1;

	t2 = clock();
	bubbleSort(q, length);
	t2 = clock() - t2;

	//writing table to file
	out << left << setw(nameWidth) << setfill(separator) <<"Array size: ";
	out << left << setw(numWidth) << setfill(separator) << i;
	out << left << setw(nameWidth) << setfill(separator) << "MergeSort (milliseconds): "; 
	out << left << setw(numWidth) << setfill(separator) << (((float)t1/CLOCKS_PER_SEC)*1000);
	out << setw(nameWidth) << setfill(separator) << "BubbleSort (milliseconds): ";
	out << setw(nameWidth) << setfill(separator) << (((float)t2/CLOCKS_PER_SEC)*1000);
	out << endl;
}
	ifstream in("table.txt");
	out.close();

	return 0;
}

//classic bubbleSort method
void bubbleSort(int* p, int length){
	for(int i=0; i<length; i++){
		for(int j=0; j<length-1; j++){
			if(*(p+j) > *(p+j+1)){
				swap(*(p+j), *(p+j+1));
			}
		}
	}
}

//helper swap method, called on by bubbleSort
void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

//simple version of merge method
void merge(int* arr, int *leftarr, int *rightarr, int size1, int size2){
	int i = 0;
	int j = 0;
	
	while(i < size1 && j < size2){
		if (leftarr[i] > rightarr[j]){
			arr[i+j] = rightarr[j];
			j++;
		}
		else{
			arr[i+j] = leftarr[i];
			i++;
		}
	}

	while(i < size1){
		arr[i+j] = leftarr[i];
		i++;
	}

	while(j < size2){
		arr[i+j] = rightarr[j];
		j++;
	}


}

//classic  mergeSort method
void mergeSort(int *arr, int size) {
	if(size <= 1){
		return;
	}

	int size1 = size/2;
	int size2 = size - size/2;
	int temp1 [size1];
	int temp2 [size2];

	for(int i = 0; i < size1; i++){
		temp1[i] = arr[i];
	}

	for(int i = 0; i < size2; i++){
		temp2[i] = arr[i + size/2];
	}

	mergeSort(temp1, size1);
	mergeSort(temp2, size2);
	merge(arr, temp1, temp2, size1, size2);
}
