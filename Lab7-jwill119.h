// Lab7-jwill119.h
// Function declarations for sorting.

#ifndef LAB7_H
#define LAB7_H


void bubsort(vector<double> A, int n);
void selsort(vector<double> A, int n);

template <typename E, typename Comp>
void selsort(E A[], int n);


#endif
