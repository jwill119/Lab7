// Lab7-jwill119.cpp
// Function definitions: sorting

#include <iostream>
#include "Lab7-jwill119.h"
#include "Randomutilities.h"    // includes <algorithm> with std::sort
#include "unixTimer.h"


using namespace std;


// Bubble sort
// Modified from Shaffer "Data Structures and Algorithms in C++", 2012
void bubsort(vector<double> vec, int n) {
    double temp;
    for (int i=0; i<n-1; i++) {         // Bubble forward
        for (int j = n-1; j>i; j--) {   // Inner bubble goes back
            if (vec[j] < vec[j-1]) {
                temp = vec[j];
                vec[j] = vec[j-1];
                vec[j-1] = temp;
            }
        }
    }
}

// The template
/*
template <typename E, typename Comp>
void bubsort(E A[], int n) { // Bubble Sort
    for (int i=0; i<n-1; i++) // Bubble up i’th record
        for (int j=n-1; j>i; j--)
            if (Comp::prior(A[j], A[j-1]))
                swap(A, j, j-1);
}
*/

// Insertion sort
// Modified from Shaffer "Data Structures and Algorithms in C++", 2012
void inssort(vector<double> vec, int n) {
    double temp;
    for (int i = 1; i < n; i++) {
        for (int j = i; (j > 0) && (vec[j] < vec[j-1]); j--) {
            temp = vec[j];
            vec[j] = vec[j-1];
            vec[j-1] = temp;
        }
    }
}

// The template
/*
template <typename E, typename Comp>
void inssort(E A[], int n) { // Insertion Sort
    for (int i=1; i<n; i++) // Insert i’th record
        for (int j=i; (j>0) && (Comp::prior(A[j], A[j-1])); j--)
            swap(A, j, j-1);
}
*/


// Selection sort
// Modified from Shaffer "Data Structures and Algorithms in C++", 2012
void selsort(vector<double> vec, int n) {
    double temp;
    for (int i = 0; i < n-1; i++) {
        int lowindex = i;
        for (int j = n-1; j > i; j--) {
            if (vec[j] < vec[lowindex]) {
                lowindex = j;
            }
        }
        temp = vec[i];
        vec[i] = vec[lowindex];
        vec[lowindex] = temp;
    }
}

// The template
/*
template <typename E, typename Comp>
void selsort(E A[], int n) { // Selection Sort
    for (int i=0; i<n-1; i++) { // Select i’th record
        int lowindex = i; // Remember its index
        for (int j=n-1; j>i; j--) // Find the least value
            if (Comp::prior(A[j], A[lowindex]))
                lowindex = j; // Put it in place
        swap(A, i, lowindex);
    }
}
*/

// Merge sort
// Modified from Shaffer "Data Structures and Algorithms in C++", 2012
template <typename E, typename Comp>
void mergesort(E A[], E temp[], int left, int right) {
    if ((right-left) <= THRESHOLD) { // Small list
        inssort<E,Comp>(&A[left], right-left+1);
        return;
    }
    int i, j, k, mid = (left+right)/2;
    mergesort<E,Comp>(A, temp, left, mid);
    mergesort<E,Comp>(A, temp, mid+1, right);
    // Do the merge operation. First, copy 2 halves to temp.
    for (i=mid; i>=left; i--) temp[i] = A[i];
    for (j=1; j<=right-mid; j++) temp[right-j+1] = A[j+mid];
    // Merge sublists back to A
    for (i=left,j=right,k=left; k<=right; k++) {
        if (Comp::prior(temp[i], temp[j])) {
            A[k] = temp[i++];
        } else { 
            A[k] = temp[j--];
        }
    }
}



// Quicksort
// Modified from Shaffer "Data Structures and Algorithms in C++", 2012
template <typename E, typename Comp>
void qsort(E A[], int i, int j) { // Quicksort
    if (j <= i) return; // Don’t sort 0 or 1 element
    int pivotindex = findpivot(A, i, j);
    swap(A, pivotindex, j); // Put pivot at end
    // k will be the first position in the right subarray
    int k = partition<E,Comp>(A, i-1, j, A[j]);
    swap(A, k, j); // Put pivot in place
    qsort<E,Comp>(A, i, k-1);
    qsort<E,Comp>(A, k+1, j);
    }


// Generate random vector
vector<double> makeVec(double minNum, double maxNum, size_t theSize) {

}

// Testing the functions
int main() {

    return 0;
}
