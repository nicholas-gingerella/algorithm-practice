// File: quickselect.cpp
// Author: Nick Gingerella
// Description:
// Implementation of the QuickSelect algorithm for finding the Kth smallest element
// in an array of integers.
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>

// function declarations
int get_kth_smallest(int*, int, int, int);
int get_kth_smallest_v2(int*, int, int, int);
int partition(int*, int, int);
void swap(int*, int, int);
int compare(int, int);
void run_partition_test();
void run_kth_smallest_test();
int* gen_random_int_array(int, int);

int main()
{
    // seed random number generator
    std::srand(std::time(nullptr));

    //run_partition_test();
    run_kth_smallest_test();
    
    return 0;
}


// function: get_kth_smallest
//
// Description:
// Get the kth smallest item from the array using the quickselect algorithm
// Worst Case: N^2 (higher likelihood of your computer getting struck by lightening)
// Average Case: N
// Space Complexity: 1 (in-place)
//
// Notes:
// This function modifies the passed in array in-place.
// assumed left < right
//
// Parameters:
// arr:     Integer array we wish to swap elements within.
// left:    Index of leftmost element in array for this partition
// right:   Index of rightmost element in array for this partition
//  
// return value:
// None, the values at the indices within the array will be swapped.
int get_kth_smallest(int* arr, int left, int right, int k)
{
    int pivot_index = partition(arr, left, right);
    if (k < (pivot_index+1))
    {
        // the kth item is to the left of the pivot.
        return get_kth_smallest(arr, left, pivot_index-1, k);
    }
    else if (k > (pivot_index+1))
    {
        // the kth smallest item is to the right of the pivot.
        return get_kth_smallest(arr, pivot_index+1, right, k);
    }
    else
    {
        // pivot index is the kth index in the array.
        // found our kth smallest item.
        return arr[pivot_index];
    } 
}

// function: get_kth_smallest_v2
//
// Description:
// Get the kth smallest item from the array using the quickselect algorithm (deterministic version)
//
// Notes:
// This function modifies the passed in array in-place.
// assumed left < right
//
// Parameters:
// arr:     Integer array we wish to swap elements within.
// left:    Index of leftmost element in array for this partition
// right:   Index of rightmost element in array for this partition
//  
// return value:
// None, the values at the indices within the array will be swapped.
int get_kth_smallest_v2(int* arr, int left, int right, int k)
{
    // if array is less than 50 elements
    //   sort it and return kth element (use quicksort)
    // else
    //   group array into n/5 groups of size 5, and find the median of each group. (quickselect for n/2 on each group)
    int numMedians = (right - left + 1) / 5;
    int medianIndices[numMedians];
    for (int i=0; i < numMedians; i++)
    {
        // go through array in chunks of 5 elements
        int start = i * 5;
        int end = start + 5 - 1;

        // get the median element from this chunk of 5
        int median_index = get_kth_smallest_v2(arr, start, end, 3); // out of 5 elements, 3 is the middle (median) value
        medianIndices[i] = median_index;
    }

    // Use map to recover the index of the median-of-medians in the input array
    std::map <int, int> medianValueToIndex;

    // Add all the medians to an array so we can get the median-of-medians
    int medians[numMedians];
    for (int i = 0; i < numMedians; i++)
    {
        // get median values from array
        int medianIndex = medianIndices[i];
        int medianValue = arr[medianIndex];

        medians[i] = medianValue;
        medianValueToIndex[medianValue] = medianIndex;
    }

    // find the median of the medians to use as pivot
    int tempMedianIndex = get_kth_smallest_v2(medians, 0, numMedians-1, 3);
    int medianOfMediansValue = medians[tempMedianIndex];
    int medianOfMedianIndex = medianValueToIndex[medianOfMediansValue];

    // swap move median-of-medians value to start of array, since partition()
    // uses the first element of the subset as the pivot
    swap(arr, 0, medianOfMedianIndex);

    //   find the median of the medians, this will be the pivot value (quickselect on n/2 for the set of medians)
    //   swap first element of array with the pivot value element
    //   run quickselect
    int pivot_index = partition(arr, left, right);
    if (k < (pivot_index+1))
    {
        // the kth item is to the left of the pivot.
        return get_kth_smallest_v2(arr, left, pivot_index-1, k);
    }
    else if (k > (pivot_index+1))
    {
        // the kth smallest item is to the right of the pivot.
        return get_kth_smallest_v2(arr, pivot_index+1, right, k);
    }
    else
    {
        // pivot index is the kth index in the array.
        // found our kth smallest item.
        return arr[pivot_index];
    } 
}

// function: partition
//
// Description:
// Use the Djikstra 3-way Paritition algorithm to Partition the array around a
// pivot point, arranging values less then the pivot value to the left of
// the pivot, and values that are greater than the pivot value to the
// right of the pivot.
//
// Notes:
// This function chooses the first element in the the range (low_index) as
// the pivot value to be partitioned on. This function modifies the passed
// in array in-place. Assumed all elements are unique (no duplicates)
//
// Parameters:
// arr:        integer array we wish to partition.
// low_index:  the leftmost index of the array we wish to start the partition.
// high_index: the rightmost index of the array we wish to end the partition.
//  
// return value:
// The index in the array to the pivot value that was partitioned on. If the pivot
// has duplicates in the array, the index of the rightmost (highest) element is returned.
int partition(int* arr, int low_index, int high_index)
{

    // initialize marker positions 
    int lessThanIndex = low_index;
    int currentIndex = low_index;
    int greaterThanIndex = high_index;

    // choose pivot value.
    // can also choose a random value as pivot, and swap it with the first element
    // in the array as an alternative pivot selection approach.
    int pivotValue = arr[low_index];

    // int random_index = (std::rand() % (high_index - low_index + 1)) + low_index;
    // swap(arr, low_index, random_index);
    // int pivotValue = arr[low_index];

    // while the current and greater-than markers have not crossed
    // during the list traversal
    while (currentIndex <= greaterThanIndex)
    {
        // compare the value at the current marker position with the
        // chosen pivot value
        int compareResult = compare(arr[currentIndex], pivotValue);

        switch(compareResult)
        {
            case -1:
            {
                // current marker < pivot value
                // swap values between current marker and less-than marker
                // increment both markers
                swap(arr, currentIndex, lessThanIndex);
                currentIndex++;
                lessThanIndex++;
                break;
            }
            case 0:
            {
                // current marker == pivot value
                // increment current marker
                currentIndex++;
                break;
            }
            case 1:
            {
                // current marker > pivot value
                // swap values between current marker and greater-than marker
                // decrement greater-than marker only
                swap(arr, currentIndex, greaterThanIndex);
                greaterThanIndex--;
                break;
            }
            default:
            {
                std::cout << "Error: Partition(" << low_index << "," << high_index  << ") - Why are we here? Just to suffer?" << std::endl;
            }
        }
    }

    // greater than marker is now pointing to the final index of our pivot value.
    return greaterThanIndex;
}


// function: compare
//
// Description:
// Simple 3-way comparison between two integer values, i and j.
//
// Notes:
// None
//
// Parameters:
// i: Integer we wish to compare
// j: Integer we are comparing the value 'i' against
//  
// return value:
// -1 if i is less than j
//  0 if i is equivilant to j
//  1 if i is greater than j
int compare(int i, int j)
{
    if (i < j)
    {
        return -1;
    }
    else if ( i > j)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// function: swap
//
// Description:
// Simply swap the values between two indices within an integer array.
//
// Notes:
// This function modifies the passed in array in-place.
//
// Parameters:
// arr:     Integer array we wish to swap elements within.
// index1:  The first index in the array whose value will be swapped with that at index2.
// index2:  The second index in the array whose value will be swapped with that at index1.
//  
// return value:
// None, the values at the indices within the array will be swapped.
void swap(int* arr, int index1, int index2)
{
    int tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}


// function: run_partition_test
//
// Description:
// Test hoare_partition() function on a number of random arrays
//
// Notes:
// None
//
// Parameters:
// None
//  
// return value:
// None
void run_partition_test()
{
   // Partition Method Test
    int* currArray = nullptr;
    int numTestRuns = 100;
    int arrSize = 30;
    int maxNum = 100;
    for (int i=0; i < numTestRuns; i++)
    {
        std::cout << "Partition Test #" << i+1 << std::endl;

        // get array of random numbers
        currArray = gen_random_int_array(arrSize, maxNum);

        std::cout << "Array Before Partition" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;

        // partition entire array
        int left_index = 0;
        int right_index = arrSize - 1;
        int pivot_index = partition(currArray, left_index, right_index);
    
        std::cout << "Array After Partition" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "partitioned on " << currArray[pivot_index] << " at index " << pivot_index << std::endl;
        std::cout << currArray[pivot_index] << " is the " << pivot_index+1 << "th smallest element in the array" << std::endl;

        delete [] currArray;

        std::cout << std::endl;
    }
}

// function: run_kth_smallest_test
//
// Description:
// Test get_kth_smallest() function on a number of random arrays
//
// Notes:
// None
//
// Parameters:
// None
//  
// return value:
// None
void run_kth_smallest_test()
{

   // Partition Method Test
    int* currArray = nullptr;
    int numTestRuns = 100;
    int arrSize = 10;
    int maxNum = 100;
    for (int i=0; i < numTestRuns; i++)
    {
        std::cout << "get_kth_smallest() Test #" << i+1 << std::endl;

        // get array of random numbers
        currArray = gen_random_int_array(arrSize, maxNum);

        // get random kth target
        //int target_k = (std::rand() % arrSize) + 1;
        int target_k = (arrSize/2) + 1;
        std::cout << "target k = " << target_k << std::endl;

        std::cout << "Array Before getting kth smallest" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;

        int left_index = 0;
        int right_index = arrSize - 1;
        int kth_item = get_kth_smallest(currArray, left_index, right_index, target_k);
    
        std::cout << "Array After kth_smallest" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << target_k << "th smallest item: " << kth_item << std::endl;

        delete [] currArray;

        std::cout << std::endl;
    }
}

// function: gen_random_int_array
//
// Description:
// Generates an array of length 'size' containing random integers ranging
// from 0 to 'max'
//
// Notes:
// This function generates a dynamically allocated array that should be cleaned up to
// avoid memory leaks after it is no longer needed.
//
// Parameters:
// size:    Number of integers the generated array should hold
// max:     The maximum of the range of integers that will be randomly generated.
//  
// return value:
// None, the values at the indices within the array will be swapped.
int* gen_random_int_array(int size, int max )
{
    int* retArr = new int[size];
    for (int i=0; i < size; i++)
    {
        retArr[i] = std::rand() % max;
    }

    return retArr;
}
