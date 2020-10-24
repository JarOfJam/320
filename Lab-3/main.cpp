#include <iostream>
#include <cstdlib>
#include <chrono>

struct Heap {
	int* arr;
	int length;
	int heap_size;
	int& operator[](int i) {
		return arr[i-1];
	}
};

void fill(Heap A, int n, int type) {
	if(type == 1) {
		for(int i = 1; i <= n; i++) {
			A[i] = i;
		}
	}
	if(type == 2) {
		for(int i = 1; i <= n; i++) {
			A[i] = n - i;
		}
	}
	if(type == 3) {
		for(int i = 1; i <= n; i++) {
			A[i] = i % 3;
		}
	}
	if(type == 4) {
		for(int i = 1; i <= n; i++) {
			A[i] = rand();
		}
	}
}

void swap(int& i, int& j) {
	int k = i;
	i = j;
	j = k;
}

void maxHeapify(Heap A, int i) {
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
		swap(A[i], A[max]);
		maxHeapify(A, max);
	}
}

void buildMaxHeap(Heap A) {
	A.heap_size = A.length;
	for(int i = (A.length / 2); i >= 1; i--) {
		maxHeapify(A, i);
	}
}

void printHeap(Heap A) {
	for(int i = 1; i < 64; i++) {
		std::cout << A[i] << " ";
		if(i == 1 || i == 3 || i == 7 || i == 15 || i == 31 || i == 63) {
			std::cout << std::endl << std::endl;
		}
	}
}

void heapSort(Heap A) {
	auto begin = std::chrono::system_clock::now();
	buildMaxHeap(A);
	for(int i = A.length; i>= 2; i--) {
		swap(A[1], A[i]);
		A.heap_size = A.heap_size - 1;
		maxHeapify(A, 1);
	}
	auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = finish-begin;
	std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
	printHeap(A);
	std::cout << "Sort Done at " << std::ctime(&end_time) << "Time taken: " << elapsed_seconds.count() << std::endl << std::endl;
}

int main() {
	int n = 100;
	Heap A;
	A.length = n;
	A.arr = new int[A.length];

	std::cout << "100 Sized Array" << std::endl;
	fill(A, n, 1);
	std::cout << "Ascending" << std::endl;
	heapSort(A);
	fill(A, n, 2);
	std::cout << "Descending" << std::endl;
	heapSort(A);
	fill(A, n, 3);
	std::cout << "Repeats" << std::endl;
	heapSort(A);
	fill(A, n, 4);
	std::cout << "Random" << std::endl;
	heapSort(A);

	n = 1000;
	A.length = n;
	A.arr = new int[A.length];

	std::cout << "1000 Sized Array" << std::endl;
	fill(A, n, 1);
	std::cout << "Ascending" << std::endl;
	heapSort(A);
	fill(A, n, 2);
	std::cout << "Descending" << std::endl;
	heapSort(A);
	fill(A, n, 3);
	std::cout << "Repeats" << std::endl;
	heapSort(A);
	fill(A, n, 4);
	std::cout << "Random" << std::endl;
	heapSort(A);

	n = 10000;
	A.length = n;
	A.arr = new int[A.length];
	
	std::cout << "10000 Sized Array" << std::endl;
	fill(A, n, 1);
	std::cout << "Ascending" << std::endl;
	heapSort(A);
	fill(A, n, 2);
	std::cout << "Descending" << std::endl;
	heapSort(A);
	fill(A, n, 3);
	std::cout << "Repeats" << std::endl;
	heapSort(A);
	fill(A, n, 4);
	std::cout << "Random" << std::endl;
	heapSort(A);

	n = 1000000;
	A.length = n;
	A.arr = new int[A.length];
	
	std::cout << "1000000 Sized Array" << std::endl;
	fill(A, n, 1);
	std::cout << "Ascending" << std::endl;
	heapSort(A);
	fill(A, n, 2);
	std::cout << "Descending" << std::endl;
	heapSort(A);
	fill(A, n, 3);
	std::cout << "Repeats" << std::endl;
	heapSort(A);
	fill(A, n, 4);
	std::cout << "Random" << std::endl;
	heapSort(A);
	
	return 0;
}
