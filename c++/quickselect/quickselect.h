// File: quickselect.h
// Author: Nick Gingerella
// Description:
// Declaration of the QuickSelect algorithm for finding the Kth smallest element
// in an array of integers.
#ifndef QUICKSELECT_H
#define QUICKSELECT_H

// function declarations
int get_kth_smallest(int*, int, int, int);
int get_kth_smallest_v2(int*, int, int, int);
void quicksort(int*, int, int);
int partition(int*, int, int);
void swap(int*, int, int);
int compare(int, int);

#endif