// Lab7-jwill119.h
// Function declarations for sorting.

#ifndef LAB7_H
#define LAB7_H

#include <vector>
using std::vector;

void bubsort(vector<double> A, size_t n);
void selsort(vector<double> A, size_t n);
void inssort(vector<double> A, size_t n);
void mergsort(vector<double> A, vector<double> temp, int left, int right);
void quicksort(vector<double> A, int n);

#endif
