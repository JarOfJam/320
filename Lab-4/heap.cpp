#include <iostream>
#include <chrono>
#include <math.h>
#include <string>

static int inserts = 0;

template <class T>
class HeapQ {
private:
	template <class U>
	struct HeapObj {
        	U data;
        	int key;
	};
	HeapObj<T>* arr;
	void increaseKey(HeapQ, int, int); //error state
	int heap_size;
	int length;
	void buildMaxHeap(HeapQ);
	void maxHeapify(HeapQ, int);
public:
	HeapQ<T>(T*, int*, int);
	int extractMax(HeapQ); //error case
	void peek(HeapQ); //hopefully done
	void insert(HeapQ, int); //hopefully done
	void print(HeapQ); //hopefully done
	void heapSort(HeapQ);
	int& operator[](int i) {
		return (arr[i - 1].key);
	}
};

template <class T>
HeapQ<T>::HeapQ(T* arr1, int* arrP, int n) {
	arr = new HeapObj<T>[n];
	heap_size = n;
	length = n;
	for(int i = 0; i < n; i++) {
		arr[i].data = arr1[i];
		arr[i].key = arrP[i];
	}
}

template <class T>
void HeapQ<T>::print(HeapQ A) {
	for(int i = 1; i <= length + inserts; i++) {
		if(A[i] >= 0) {
			std::cout << A.arr[i-1].data << " (" << A[i] << ")   ";
		}
		for(int j = 1; j <= length + inserts; j++) {
			if(i == (pow(2.0, j) - 1)) {
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

template <class T>
void HeapQ<T>::peek(HeapQ A) {
	std::cout << "Max: " << A.arr[0].data << std::endl;
}

template <class T>
int HeapQ<T>::extractMax(HeapQ(A)) {
	if(A.heap_size < 1) {
		std::cout << "Error: heap underflow" << std::endl;
		exit(1);
	}
	A[1] = -1;
	//swap(A.arr[0], A.arr[heap_size-1]);
	HeapObj<T> temp = A.arr[0];
	A.arr[0] = A.arr[heap_size-1];
	A.arr[heap_size-1] = temp;
	A.heap_size--;
	maxHeapify(A, 1);
	return A.heap_size;
}

template <class T>
void HeapQ<T>::insert(HeapQ A, int k) {
	A.heap_size = A.heap_size + 1;
	inserts++;
	A[A.heap_size] = -1;
	increaseKey(A, A.heap_size, k);
}

template <class T>
void HeapQ<T>::increaseKey(HeapQ A, int i, int k) {
	if(k < A[i]) {
		std::cout << "Error: new key smaller than old key" << std::endl;
		exit(1);
	}
	A[i] = k;
	A.arr[i-1].data = "inserted";
	while(i > 1 && A[i/2] < A[i]) {
		//swap(A.arr[i-1], A.arr[(i/2)-1]);
		HeapObj<T> temp = A.arr[i-1];
		A.arr[i-1] = A.arr[(i/2)-1];
		A.arr[(i/2)-1] = temp;
		i = i/2;
	}
}

template <typename V>
void swap(V& i, V& j) {
	V k = i;
	i = j;
	j = k;
}

template <class T>
void HeapQ<T>::maxHeapify(HeapQ A, int i) {
	int max;
	int l = (i * 2) - 1;
	int r = i * 2;
	if(l <= A.heap_size && A[l] > A[i]) {
		max = l;
	}
	else {
		max = i;
	}
	if(r <= A.heap_size && A[r] > A[max]) {
		max = r;
	}
	if(max != i) {
		//swap(A.arr[i-1], A.arr[max-1]);
		HeapObj<T> temp = A.arr[i-1];
		A.arr[i-1] = A.arr[max-1];
		A.arr[max-1] = temp;
		A.maxHeapify(A, max);
	}
}

template <class T>
void HeapQ<T>::buildMaxHeap(HeapQ A) {
	A.heap_size = A.length;
	for(int i = (A.length / 2); i >= 1; i--) {
		A.maxHeapify(A, i);
	}
}

template <class T>
void HeapQ<T>::heapSort(HeapQ A) {
	auto begin = std::chrono::system_clock::now();
	A.buildMaxHeap(A);
	for(int i = A.length; i>= 2; i--) {
		//swap(A.arr[0], A.arr[i-1]);
		HeapObj<T> temp = A.arr[0];
		A.arr[0] = A.arr[i-1];
		A.arr[i-1] = temp;
		A.heap_size = A.heap_size - 1;
		A.maxHeapify(A, 1);
	}
	int j = length;
	int k = 1;
	while(k<j) {
		//swap(A.arr[j-1], A.arr[k-1]);
		HeapObj<T> temp2 = A.arr[j-1];
		A.arr[j-1] = A.arr[k-1];
		A.arr[k-1] = temp2;
		k++;
		j--;
	}
	auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = finish-begin;
	std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
	std::cout << "Sort Done at " << std::ctime(&end_time) << "Time taken: " << elapsed_seconds.count() << std::endl << std::endl;
}
