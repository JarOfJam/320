#include <iostream>
#include <chrono>
#include <cstdlib>

int swaps = 0;

bool isSorted(int* arr, int n){
  for(int i = 0; i < n-1; i++){
    if(arr[i] > arr[i+1]){
      return false;
    }
  }
  return true;
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

void swap(int& i, int& j) {
  int k;
  k = i;
  i = j;
  j = k;
}

int partition(int arr[], int start, int end) {
  int pivot = arr[end];  
  int i = (start - 1); 
  for (int j = start; j <= end - 1; j++) {   
    if (arr[j] < pivot) {  
      i++;
	swap(arr[i], arr[j]);
	swaps++;
    }  
  }  
  swap(arr[i + 1], arr[end]);
  swaps++;
  return (i + 1);
}

void quickSorting(int arr[], int start, int end) {
  if (start < end) {  
    int p = partition(arr, start, end);  
    quickSorting(arr, start, p - 1);  
    quickSorting(arr, p + 1, end);  
  }  
}

void quickSort(int arr[], int start, int end) {
  swaps = 0;
  auto begin = std::chrono::system_clock::now();
  quickSorting(arr, start, end);
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  if(isSorted(arr, end)) {
    std::cout << "Sorted Properly" << std::endl;
  }
  else {
    std::cout << "Not Sorted Properly" << std::endl;
  }
  std::cout << "Quick Sort Done at " << std::ctime(&end_time) << "Time taken: " << elapsed_seconds.count() << std::endl;
  std::cout << "Swaps: " << swaps << std::endl;
}

void merge(int arr[], int start, int mid, int end) {
  int i, j, k, n, m;
  n = mid - start + 1;
  m = end - mid;

  int l[n];
  int r[m];

  for(i = 0; i < n; i++) {
    l[i] = arr[start + i];
  }
  for(j = 0; j < m; j++) {
    r[j] = arr[mid + 1 + j];
  }
  i = 0;
  j = 0;
  k = start;
  while(i < n && j < m) {
    if(l[i] <= r[j]) {
      arr[k] = l[i];
      i++;
      swaps++;
    }
    else {
      arr[k] = r[j];
      j++;
      swaps++;
    }
    k++;
  }
  while(i < n) {
    arr[k] = l[i];
    i++;
    k++;
  }
  while(j < m) {
    arr[k] = r[j];
    j++;
    k++;
  }
}

void mergeSorting(int arr[], int start, int end) {
  if(start < end) {
    int mid = (start + (end-1)) / 2;
    mergeSorting(arr, start, mid);
    mergeSorting(arr, mid + 1, end);
    merge(arr, start, mid, end);
  }
}

void mergeSort(int arr[], int start, int end) {
  swaps = 0;
  auto begin = std::chrono::system_clock::now();
  mergeSorting(arr, start, end);
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  if(isSorted(arr, end)) {
    std::cout << "Sorted Properly" << std::endl;
  }
  else {
    std::cout << "Not Sorted Properly" << std::endl;
  }
  std::cout << "Merge Sort Done at " << std::ctime(&end_time) << "Time taken: " << elapsed_seconds.count() << std::endl;
  std::cout << "Comparisons: " << swaps << std::endl;
}

int main(){
  
  //*
  int n = 100;
  int* arr = new int[n];

  std::cout << std::endl << "100: Ascending, Descending, Repreated, Random" << std::endl << std::endl;
  
  fill(arr, n, 1);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);
  
  fill(arr, n, 2);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);
  
  fill(arr, n, 3);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 4);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);
  
  n = 1000;
  arr = new int[n];

  std::cout << std::endl << "1000: Ascending, Descending, Repreated, Random" << std::endl << std::endl;

  fill(arr, n, 1);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);
  
  fill(arr, n, 2);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);;

  fill(arr, n, 3);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 4);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  n = 10000;
  arr = new int[n];

  std::cout << std::endl << "10000: Ascending, Descending, Repreated, Random" << std::endl << std::endl;

  fill(arr, n, 1);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 2);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 3);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 4);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  n = 1000000;
  arr = new int[n];

std::cout << std::endl << "1000000: Ascending, Descending, Repreated, Random" << std::endl << std::endl;

  fill(arr, n, 1);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 2);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 3);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);

  fill(arr, n, 4);
  
  quickSort(arr, 0, n-1);
  mergeSort(arr, 0, n-1);
  //*/
  return 0;
}
