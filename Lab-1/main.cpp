#include <iostream>
#include <chrono>
#include <cstdlib>

bool isSorted(int* arr, int n){
  for(int i = 0; i < n-1; i++){
    if(arr[i] > arr[i+1]){
      return false;
    }
  }
  return true;
}

void bubbleSort(int *arr, int n){
  auto start = std::chrono::system_clock::now();
  bool swap;
  int i, j, k, swaps;
  swaps = 0;
  j = n - 1;
  do {
    swap = false;
    for (i = 0; i < j; i++) {
      if (arr[i] > arr[i+1]) {
	k = arr[i];
	arr[i] = arr[i+1];
	arr[i+1] = k;
	swap = true;
	swaps++;
      }
    }
    j--;
  } while (swap);
  std::cout << "Swaps: " << swaps << std::endl;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout << "Done at " << std::ctime(&end_time) << "Time taken: " << elapsed_seconds.count() << std::endl;
  if(isSorted(arr, n)) {
    std::cout << "Sorted Properly" << std::endl;
  }
}

void insertionSort(int *arr, int n){
  auto start = std::chrono::system_clock::now();
  int i, j, k, swaps;
  swaps = 0;
  for (i = 1; i < n; i++) {
    k = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > k) {
      arr[j+1] = arr[j];
      j = j - 1;
      swaps++;
    }
    arr[j+1] = k;
  }
  std::cout << "Swaps: " << swaps << std::endl;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout << "Done at " << std::ctime(&end_time) << "Time taken: " << elapsed_seconds.count() << std::endl;
  if(isSorted(arr, n)) {
    std::cout << "Sorted Properly" << std::endl;
  }
}

void selectionSort(int *arr, int n){
  auto start = std::chrono::system_clock::now();
  int i, j, k, min, swaps;
  swaps = 0;
  for (i = 0; i < n-1; i++) {
    k = i;
    min = arr[i];
    for (j = i+1; j < n; j++) {
      if (arr[j] < min) {
	min = arr[j];
	k = j;
	swaps++;
      }
    }
    arr[k] = arr[i];
    arr[i] = min;
  }
  std::cout << "Swaps: " << swaps << std::endl;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout << "Done at " << std::ctime(&end_time) << "Time taken: " << elapsed_seconds.count() << std::endl;
  if(isSorted(arr, n)) {
    std::cout << "Sorted Properly" << std::endl;
  }
}

void fill(int* arr, int n, int type) {
  if(type = 1) {
    for(int i = 0; i < n; i++) {
      arr[i] = i;
    }
  }
  if(type = 2) {
    for(int i = 0; i < n; i++) {
      arr[i] = n - i;
    }
  }
 if(type = 3) {
    for(int i = 0; i < n; i++) {
      arr[i] = i % 3;
    }
  }
 if(type = 4) {
    for(int i = 0; i < n; i++) {
      arr[i] = rand();
    }
  }
}

int main(){
  int n = 100;
  int* arr = new int[n];

  fill(arr, n, 1);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 2);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 3);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 4);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  n = 1000;
  arr = new int[n];

  fill(arr, n, 1);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 2);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 3);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 4);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  n = 10000;
  arr = new int[n];

  fill(arr, n, 1);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 2);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 3);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 4);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  n = 1000000;
  arr = new int[n];

  fill(arr, n, 1);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 2);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 3);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  fill(arr, n, 4);
  
  bubbleSort(arr, n);
  insertionSort(arr, n);
  selectionSort(arr, n);

  return 0;
}
