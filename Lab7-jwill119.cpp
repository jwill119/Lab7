// Lab7-jwill119.cpp
// Function definitions: sorting

#include <iostream>
#include "Lab7-jwill119.h"
#include "Randomutilities.h"    // includes <algorithm> with std::sort
#include "unixTimer.h"


using namespace std;


// Bubble sort
// Modified from Shaffer "Data Structures and Algorithms in C++", 2012
void bubsort(vector<double> vec, size_t n) {
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
void inssort(vector<double> vec, size_t n) {
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
void selsort(vector<double> vec, size_t n) {
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
void mergsort(vector<double> vec, vector<double> temp, int left, int right) {
    // We won't bother implementing an insertion sort for small lists.
    // This is super recursive.

    int i, j, k;
    int mid = (left + right)/2;
    mergsort(vec,temp,left,mid);
    mergsort(vec,temp,mid+1,right);

    // Do the merge operation! First: copy both halves to temp
    for (i = mid; i >= left; i--) temp[i] = vec[i];
    for (j = 1; j < right - mid; j++) temp[right-j+1] = vec[j+mid];

    // Merge sublists back to vec
    for (i = left, j = right, k = left; k <= right; k++) {
        if (temp[i] < temp[j]) {
            vec[k] = temp[i++];
        } else {
            vec[i] = temp[j--];
        }
    }

}


// The template
/*
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
*/



// Quicksort
// Modified from Shaffer "Data Structures and Algorithms in C++", 2012
void quicksort(vector<double> vec, int begin, int end) {
    if (end <= begin) return;
    int pivotIndex = (begin+end)/2; // is an integer
    // Swap the pivot to the end
    double temp = vec[j];
    vec[j] = vec[pivotIndex];
    vec[pivotIndex] = temp;
    // Now, k is the first position in the right sub-array
}

// The template
/*
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
*/

// Generate random vector
vector<double> makeVec(double minNum, double maxNum, size_t theSize) {
    vector<double> theVec;
    for (size_t i = 0; i < theSize; i++) {
        theVec.push_back(randReal(minNum,maxNum));
    }

    return theVec;
}

// Testing the functions
int main() {

    // We want a vector that takes like four seconds to sort.


    // Test std::sort (supposed to run in O(n log n) time)
    cout << "Testing std::sort." << endl;
    vector<double> sortVec = makeVec(1,500,5300000);
    Timer stdTime;
    stdTime.start();
    std::sort(sortVec.begin(),sortVec.end());
    stdTime.stop();
    cout << "std::sorted vector of length " << sortVec.size() << " in " << stdTime() << " seconds." << endl << endl;

    // Test the bubble sort.
    cout << "Testing bubble sort." << endl;
    vector<double> bubbleVec = makeVec(1,500,15000);
    Timer bubTime;
    bubTime.start();
    bubsort(bubbleVec,bubbleVec.size());
    bubTime.stop();
    cout << "Bubble-sorted vector of length " << bubbleVec.size() << " in " << bubTime() << " seconds." << endl << endl;

    // Test the insertion sort.
    cout << "Testing insertion sort." << endl;
    vector<double> insVec = makeVec(1,500,18100);
    Timer insTime;
    insTime.start();
    inssort(insVec,insVec.size());
    insTime.stop();
    cout << "Insertion-sorted vector of length " << insVec.size() << " in " << insTime() << " seconds." << endl << endl;


    // Test the selection sort.
    cout << "Testing selection sort." << endl;
    vector<double> selVec = makeVec(1,500,21500);
    Timer selTime;
    selTime.start();
    selsort(selVec,selVec.size());
    selTime.stop();
    cout << "Selection-sorted vector of length " << selVec.size() << " in " << selTime() << " seconds." << endl << endl;


    // Test the merge sort.
    cout << "Testing merge sort." << endl;
    vector<double> mergVec = makeVec(1,500,100);
    vector<double> tempVec(mergVec.size());
    Timer mergTime;
    mergTime.start();
    mergsort(mergVec,tempVec,0,mergVec.size()-1);
    mergTime.stop();
    cout << "Merge-sorted vector of length " << mergVec.size() << " in " << mergTime() << " seconds." << endl << endl;


    // Test the quicksort.

    return 0;
}
