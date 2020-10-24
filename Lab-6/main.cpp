//Jordan Welch - Cosc 320 - Lab 6 - 10/17/19

#include <iostream>
#include <time.h>
#include <chrono>

void swap(int &i, int &j) {
	int k = i;
	i = j;
	j = k;
}

int* shuffle(int n) {
	int* arr = new int[n];
	for(int i = 0; i < n; i++) {
		arr[i] = -1;
	}
	for(int i = 1; i <= n; i++) {
		srand(time(NULL));
		int j = rand() % n;
		while(arr[j] != -1) {
			j = rand() % n;
		}
		arr[j] = i;
	}
	return arr;
}

void hireAss() {
	int ass = 0;
	int n = 10;
	int* arr;
	arr = shuffle(n);
	int rep = 0;
	for(int i = 1; i < n; i++) {
		if(arr[i] > arr[ass]) {
			ass = i;
			rep++;
		}
	}
	for(int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "Assistant is: " << ass + 1 << " with " << rep << " swaps." << std::endl;
}

int partition(int arr[], int l, int r) {
	int p, ind;
	ind = l;
	p = r;
	for(int i = l; i < r; i++) {
		if(arr[i] < arr[p]) {
			swap(arr[i], arr[ind]);
			ind++;
		}
	}
	swap(arr[p], arr[ind]);
	return ind;
}
 
int ranPart(int arr[], int l, int r) {
	int p, a, temp;
	a = rand();
	p = l + a % (r-l+1);
	swap(arr[r], arr[p]);
 
	return partition(arr, l, r);
}
 
void rQuickSort(int arr[], int l, int r) {
	int p;
	if(l < r) {
		p = ranPart(arr, l, r);
		rQuickSort(arr, l, p - 1);
		rQuickSort(arr, p + 1, r);
	}
}

int* merge(int* arr1, int start, int end, int mid){
	 int i;
 	 int j;
	 int k;
	 int n1= mid- start+1;
         int n2 = end - mid;
 	 int L[n1],R[n2];
	  k = start;
    	for(i=0;i<n1;i++) {
        	L[i]=arr1[start+i];
    	}
    	for(j=0;j<n2;j++) {
        	R[j]=arr1[mid+j+1];
    	}
   	i=0,j=0;
	while(i<n1 && j <n2){
    		if(L[i] <= R[j]) {
			arr1[k] = L[i];
			i++;
			k++;
     		}
		else if(L[i]>= R[j]) {
			arr1[k] = R[j];
			j++;
			k++;
      		}
  	}
 	while(i<n1) {
        	arr1[k++]=L[i++];
   	}	
    	while(j<n2) {
        	arr1[k++]=R[j++];
	}
	return arr1;
}
int* mergeSort(int* arr, int start, int end){
	if(start<end){
     		int mid = (start+end)/2;
     		int *m1 = mergeSort(arr, start, mid);
     		int *m2 = mergeSort(arr, mid+1, end);
     		return merge(arr, start, end, mid);
  	}
}

struct Heap {
    int* arr;
    int length;
    int heap_size;

    int& operator[](int i){
	return arr[i-1];
    }	
};

void maxHeapify(Heap A, int i) {
    	int l = (2 * i) - 1;
    	int r = 2 * i;
    	int largest;	
    	if(l <= A.heap_size && A[l] > A[i]) {
		largest = l;
	}
    	else {                                        
		largest = i;
	} 		
    	if(r <= A.heap_size && A[r] > A[largest]) {
		largest = r; 
	}
    	if(largest != i) {
		swap(A[i], A[largest]);
		maxHeapify(A, largest);
    	}
}

void buildMaxHeap(Heap A) {
   	A.heap_size = A.length;
   	for(int i = (A.length / 2); i >= 1; i--) {
   		maxHeapify(A, i);
   	}
}

void heapSort(Heap A) {
   	buildMaxHeap(A);
   	for(int i = A.length; i >= 2; i--) {
		swap(A[1], A[i]);
		A.heap_size = A.heap_size - 1;
		maxHeapify(A, 1);
	}  
}

int part(int* arr, int start, int end) {
	int a = arr[end];
	int b = start - 1;      
	for(int i = start; i < end; i++){
		if(arr[i] <= a) {
			b = b + 1;
			swap(arr[b], arr[i]);
		}
	}
	swap(arr[b + 1], arr[end]);
	return b + 1;
}

void quickSort(int* arr, int start, int end){
	int index;
        if (start < end)  {
                index = part(arr, start, end);
		quickSort(arr, start, index - 1);
                quickSort(arr, index + 1, end);
	}
}

int main() {
	hireAss();
	for(int k = 0; k < 20; k++) {
		std::cout << "Randomized Quick Sort Size " << 50000 + (50000 * k) << ":";
		int* rqs = shuffle(50000 + (50000 * k));
		auto begin = std::chrono::system_clock::now();
		rQuickSort(rqs, 0, (49999 + (50000 * k)));
		auto finish = std::chrono::system_clock::now();
  		std::chrono::duration<double> elapsed_seconds = finish-begin;
  		std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
		std::cout << std::endl << "Time taken: " << elapsed_seconds.count() << std::endl;
	}
	for(int k = 0; k < 20; k++) {
                std::cout << "Merge Sort Size " << 50000 + (50000 * k) << ":";
                int* ms = shuffle(50000 + (50000 * k));
                auto begin = std::chrono::system_clock::now();
                mergeSort(ms, 0, (49999 + (50000 * k)));
                auto finish = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = finish-begin;
                std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
                std::cout << std::endl << "Time taken: " << elapsed_seconds.count() << std::endl;
        }
	for(int k = 0; k < 20; k++) {
                std::cout << "Heap Sort Size " << 50000 + (50000 * k) << ":";
                Heap hs;
		hs.arr = new int[50000 + (50000 * k)];
		int* arr = new int[50000 + (50000 * k)];
		arr = shuffle(50000 + (50000 * k));
		for(int i = 0; i < (50000 + (50000 * k)); i++) {
			hs.arr[i] = arr[i];
		}
		hs.length = 50000 + (50000 * k);
		hs.heap_size = hs.length;
                auto begin = std::chrono::system_clock::now();
                heapSort(hs);
                auto finish = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = finish-begin;
                std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
                std::cout << std::endl << "Time taken: " << elapsed_seconds.count() << std::endl;
        }
	
	for(int k = 0; k < 20; k++) {
                std::cout << "Quick Sort Size " << 50000 + (50000 * k) << ":";
                int* qs = shuffle(50000 + (50000 * k));
                auto begin = std::chrono::system_clock::now();
                quickSort(qs, 0, (49999 + (50000 * k)));
                auto finish = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = finish-begin;
                std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
                std::cout << std::endl << "Time taken: " << elapsed_seconds.count() << std::endl;
        }
}
