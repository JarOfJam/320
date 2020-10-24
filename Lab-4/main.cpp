#include <iostream>
#include "heap.cpp"
#include <string>

using namespace std;

int main() {
	int n = 0;
	cout << "Enter number of nodes: ";
	cin >> n;
	string* arr = new string[n];
	for(int i = 0; i < n; i++) {
		cout << "Enter name: ";
		cin >> arr[i];
	}
	int* arrP = new int[n];
	for(int j = 0; j < n; j++) {
		arrP[j] = j;
	}
	HeapQ<string> A(arr, arrP, n);
	A.heapSort(A);
	A.print(A);
	cout << endl;
	A.peek(A);
	cout << endl;
	A.extractMax(A);
	//A.insert(A, 10); //segfault when i try to print after this
	A.print(A);
	return 0;
}
