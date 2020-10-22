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
#include <chrono>

// function declarations
int get_kth_smallest(int*, int, int, int);
int get_kth_smallest_v2(int*, int, int, int);
void quicksort(int*, int, int);
int partition(int*, int, int);
void swap(int*, int, int);
int compare(int, int);
void run_partition_test();
void run_kth_smallest_test();
void run_kth_smallest_v2_test();
void run_quicksort_test();
int* gen_random_int_array(int, int);

int main()
{
    // seed random number generator
    std::srand(std::time(nullptr));

    // run_partition_test();

    // auto start = std::chrono::high_resolution_clock::now(); // returns a timepoint before sort
    // run_kth_smallest_test();
    // auto stop = std::chrono::high_resolution_clock::now(); // returns a timepoint after sort
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // auto start = std::chrono::high_resolution_clock::now(); // returns a timepoint before sort
    //run_kth_smallest_v2_test();
    // auto stop = std::chrono::high_resolution_clock::now(); // returns a timepoint after sort
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // start = std::chrono::high_resolution_clock::now(); // returns a timepoint before sort
    // run_quicksort_test();
    // stop = std::chrono::high_resolution_clock::now(); // returns a timepoint after sort
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout << "sort time: " << duration.count() << "microseconds" << std::endl;

    //int arr[1000] = {634,933,855,263,587,528,753,775,610,315,209,101,339,861,871,413,950,818,48,22,683,854,831,72,98,646,603,146,852,550,406,839,484,261,454,71,141,207,846,104,522,407,205,862,620,428,627,571,246,27,945,281,881,128,705,332,774,309,478,979,859,884,818,343,498,624,766,639,831,964,95,706,724,300,920,344,80,547,915,678,927,212,959,808,341,665,492,467,326,322,446,185,559,616,881,57,240,999,48,424,964,144,130,688,796,50,32,229,949,300,907,876,864,219,37,557,236,529,25,562,852,823,99,411,440,980,820,32,980,868,456,296,364,586,336,513,988,368,742,938,20,1,814,885,220,851,794,808,381,819,370,585,995,470,348,435,802,168,819,134,388,276,782,105,214,118,618,203,839,712,141,859,713,307,96,286,159,891,94,892,62,817,829,57,287,177,844,441,697,16,928,85,644,710,190,858,829,160,413,668,872,906,879,938,214,328,224,725,571,670,969,633,487,798,43,126,327,239,568,24,255,848,461,251,558,4,462,739,164,875,407,389,134,639,327,700,967,551,425,538,573,746,523,61,896,566,187,223,158,107,599,765,955,60,17,866,64,479,605,229,706,13,970,840,4,297,540,971,200,317,509,773,63,32,834,959,951,374,182,109,833,133,226,789,194,243,655,610,74,260,191,781,625,161,621,981,458,514,952,10,831,813,784,895,198,970,206,149,696,389,610,530,874,836,319,68,432,326,679,506,938,870,639,916,32,613,897,842,127,202,853,958,15,989,205,213,959,412,714,8,153,324,538,27,513,209,448,297,535,127,155,825,349,795,741,733,408,991,576,535,193,429,845,560,770,403,774,81,815,488,89,320,165,627,699,30,836,147,327,723,274,482,901,976,277,994,709,37,985,285,924,530,66,122,91,836,525,865,918,692,705,359,12,222,987,63,252,175,211,579,251,485,62,152,813,691,146,523,81,132,808,5,662,227,127,105,415,4,322,685,696,28,45,60,250,32,124,855,559,335,434,810,172,848,962,986,540,109,509,621,593,669,978,607,248,106,713,664,110,35,349,159,415,746,571,18,130,695,873,690,382,659,500,907,508,463,893,400,924,754,373,517,775,351,124,24,809,189,40,272,225,741,431,992,488,2,362,618,50,235,308,784,247,161,691,755,976,584,507,900,690,880,769,466,231,893,842,393,83,882,665,660,623,448,4,111,802,367,730,852,954,390,637,201,551,680,308,527,265,815,779,307,695,548,773,279,794,967,672,877,849,689,889,473,137,893,584,291,260,666,144,567,409,133,768,960,813,77,840,430,244,971,90,940,520,215,219,314,183,243,543,32,284,432,505,421,325,442,712,938,460,208,505,869,693,625,182,859,54,374,641,299,345,731,239,217,947,810,883,482,405,426,514,689,210,372,462,888,166,526,826,626,735,683,848,780,660,382,639,715,756,633,14,453,716,605,23,663,767,906,497,524,333,12,213,895,736,27,783,902,553,961,880,288,644,728,421,657,462,412,372,570,45,738,24,762,695,399,777,462,305,275,338,990,639,551,886,375,578,669,629,483,983,509,124,979,590,545,636,52,957,8,623,3,98,999,117,793,398,894,607,55,521,945,46,160,848,284,887,778,305,516,262,288,378,386,268,968,931,904,372,240,265,347,595,715,698,712,509,448,959,468,504,480,414,902,993,262,186,880,41,843,749,655,132,479,41,400,447,972,656,171,564,273,871,160,989,921,872,498,370,831,966,226,664,732,480,9,347,18,241,740,861,990,395,993,469,436,745,268,760,402,792,324,675,15,484,664,936,709,514,658,892,833,884,556,917,716,565,264,734,807,4,596,149,399,589,971,187,335,591,947,89,383,272,764,398,108,781,687,817,647,345,710,832,582,618,750,298,536,14,33,343,19,629,844,770,570,815,958,905,407,905,994,142,529,111,893,990,244,580,807,891,277,869,724,859,840,474,158,376,840,543,71,211,524,915,982,94,83,940,0,490,197,346,984,79,809,877,69,53,809,228,297,87,450,373,298,290,199,808,666,39,351,737,251,875,4,585,970,87,877,322,577,74,20,914,505,830,791,574,235,601,803,884,40,605,257,338,895,456,147,913,848,498,2,451,726,6,388,48,94,265,722,23,691,742,937,197,924,729,771,160,682,926,44,74,883,654,412,778,462,911,43,310,762,45,113,488,52,501,888,146,118,610,169,810,352,107,7,277,188,130,789,222,409,833,296,292,487,60,423,950,972,466,612,734,512,78,222,564,579,110,710,50,72,231,860,424,338,};
    int arr[50] = {51,18,14,1,16,29,45,62,94,76,77,87,79,62,22,65,81,87,59,25,43,56,81,35,56,35,34,23,22,70,81,74,40,47,75,56,76,72,70,22,48,0,10,28,62,32,45,95,19,57};
    auto start = std::chrono::high_resolution_clock::now(); // returns a timepoint before sort
    int kth = get_kth_smallest(arr, 0, 49, 30);
    auto stop = std::chrono::high_resolution_clock::now(); // returns a timepoint after sort
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "kth version1: " << duration.count() << " microseconds" << std::endl;
    std::cout << "kth index = " << kth << std::endl;
    std::cout << "kth item = " << arr[kth] << std::endl;

    //int arr2[1000] = {634,933,855,263,587,528,753,775,610,315,209,101,339,861,871,413,950,818,48,22,683,854,831,72,98,646,603,146,852,550,406,839,484,261,454,71,141,207,846,104,522,407,205,862,620,428,627,571,246,27,945,281,881,128,705,332,774,309,478,979,859,884,818,343,498,624,766,639,831,964,95,706,724,300,920,344,80,547,915,678,927,212,959,808,341,665,492,467,326,322,446,185,559,616,881,57,240,999,48,424,964,144,130,688,796,50,32,229,949,300,907,876,864,219,37,557,236,529,25,562,852,823,99,411,440,980,820,32,980,868,456,296,364,586,336,513,988,368,742,938,20,1,814,885,220,851,794,808,381,819,370,585,995,470,348,435,802,168,819,134,388,276,782,105,214,118,618,203,839,712,141,859,713,307,96,286,159,891,94,892,62,817,829,57,287,177,844,441,697,16,928,85,644,710,190,858,829,160,413,668,872,906,879,938,214,328,224,725,571,670,969,633,487,798,43,126,327,239,568,24,255,848,461,251,558,4,462,739,164,875,407,389,134,639,327,700,967,551,425,538,573,746,523,61,896,566,187,223,158,107,599,765,955,60,17,866,64,479,605,229,706,13,970,840,4,297,540,971,200,317,509,773,63,32,834,959,951,374,182,109,833,133,226,789,194,243,655,610,74,260,191,781,625,161,621,981,458,514,952,10,831,813,784,895,198,970,206,149,696,389,610,530,874,836,319,68,432,326,679,506,938,870,639,916,32,613,897,842,127,202,853,958,15,989,205,213,959,412,714,8,153,324,538,27,513,209,448,297,535,127,155,825,349,795,741,733,408,991,576,535,193,429,845,560,770,403,774,81,815,488,89,320,165,627,699,30,836,147,327,723,274,482,901,976,277,994,709,37,985,285,924,530,66,122,91,836,525,865,918,692,705,359,12,222,987,63,252,175,211,579,251,485,62,152,813,691,146,523,81,132,808,5,662,227,127,105,415,4,322,685,696,28,45,60,250,32,124,855,559,335,434,810,172,848,962,986,540,109,509,621,593,669,978,607,248,106,713,664,110,35,349,159,415,746,571,18,130,695,873,690,382,659,500,907,508,463,893,400,924,754,373,517,775,351,124,24,809,189,40,272,225,741,431,992,488,2,362,618,50,235,308,784,247,161,691,755,976,584,507,900,690,880,769,466,231,893,842,393,83,882,665,660,623,448,4,111,802,367,730,852,954,390,637,201,551,680,308,527,265,815,779,307,695,548,773,279,794,967,672,877,849,689,889,473,137,893,584,291,260,666,144,567,409,133,768,960,813,77,840,430,244,971,90,940,520,215,219,314,183,243,543,32,284,432,505,421,325,442,712,938,460,208,505,869,693,625,182,859,54,374,641,299,345,731,239,217,947,810,883,482,405,426,514,689,210,372,462,888,166,526,826,626,735,683,848,780,660,382,639,715,756,633,14,453,716,605,23,663,767,906,497,524,333,12,213,895,736,27,783,902,553,961,880,288,644,728,421,657,462,412,372,570,45,738,24,762,695,399,777,462,305,275,338,990,639,551,886,375,578,669,629,483,983,509,124,979,590,545,636,52,957,8,623,3,98,999,117,793,398,894,607,55,521,945,46,160,848,284,887,778,305,516,262,288,378,386,268,968,931,904,372,240,265,347,595,715,698,712,509,448,959,468,504,480,414,902,993,262,186,880,41,843,749,655,132,479,41,400,447,972,656,171,564,273,871,160,989,921,872,498,370,831,966,226,664,732,480,9,347,18,241,740,861,990,395,993,469,436,745,268,760,402,792,324,675,15,484,664,936,709,514,658,892,833,884,556,917,716,565,264,734,807,4,596,149,399,589,971,187,335,591,947,89,383,272,764,398,108,781,687,817,647,345,710,832,582,618,750,298,536,14,33,343,19,629,844,770,570,815,958,905,407,905,994,142,529,111,893,990,244,580,807,891,277,869,724,859,840,474,158,376,840,543,71,211,524,915,982,94,83,940,0,490,197,346,984,79,809,877,69,53,809,228,297,87,450,373,298,290,199,808,666,39,351,737,251,875,4,585,970,87,877,322,577,74,20,914,505,830,791,574,235,601,803,884,40,605,257,338,895,456,147,913,848,498,2,451,726,6,388,48,94,265,722,23,691,742,937,197,924,729,771,160,682,926,44,74,883,654,412,778,462,911,43,310,762,45,113,488,52,501,888,146,118,610,169,810,352,107,7,277,188,130,789,222,409,833,296,292,487,60,423,950,972,466,612,734,512,78,222,564,579,110,710,50,72,231,860,424,338,};
    int arr2[50] = {51,18,14,1,16,29,45,62,94,76,77,87,79,62,22,65,81,87,59,25,43,56,81,35,56,35,34,23,22,70,81,74,40,47,75,56,76,72,70,22,48,0,10,28,62,32,45,95,19,57};
    start = std::chrono::high_resolution_clock::now(); // returns a timepoint before sort
    int kth2 = get_kth_smallest_v2(arr2, 0, 49, 30);
    stop = std::chrono::high_resolution_clock::now(); // returns a timepoint after sort
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "kth version2: " << duration.count() << " microseconds" << std::endl;
    std::cout << "kth index = " << kth2 << std::endl;
    std::cout << "kth item = " << arr2[kth] << std::endl;


    quicksort(arr, 0, 49);
    std::cout << "kth from sorted: " << arr[29] << std::endl;
    
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
        return pivot_index;
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
    // If array is less than 50 elements, sort it and return the
    // kth element from the array
    int arr_size = right - left + 1;
    if ( arr_size < 50)
    {
        quicksort(arr, left, right);
        return left + (k - 1); //kth element index from this section of the array
        //return k - 1; // if k > pivot
    }
    
    // Group array into n/5 groups of size 5, and find the median of each group.
    int numMedians = arr_size / 5;
    int medianIndices[numMedians];
    // std::cout << "numMedians: " << numMedians << std::endl;
    for (int i=0; i < numMedians; i++)
    {
        // go through array in chunks of 5 elements
        int start = i * 5;
        int end = start + 5 - 1;

        // get the median element from this chunk of 5
        int median_index = get_kth_smallest_v2(arr, start, end, 3); // out of 5 elements, 3 is the middle (median) value
        medianIndices[i] = median_index;
    }
    
    // std::cout << "median indices: ";
    // for (int i = 0; i < numMedians; i++)
    // {
    //     std::cout << medianIndices[i] << ",";
    // }
    // std::cout << std::endl;

    // std::cout << "median values: ";
    // for (int i = 0; i < numMedians; i++)
    // {
        // int medianIndex = medianIndices[i];
        // std::cout << arr[medianIndex] << ",";
    // }
    // std::cout << std::endl;

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

    // std::cout << "median values (medians array): ";
    // for (int i = 0; i < numMedians; i++)
    // {
    //     std::cout << medians[i] << ",";
    // }
    // std::cout << std::endl;

    // find the median of the medians to use as pivot
    int tempMedianIndex = get_kth_smallest_v2(medians, 0, numMedians-1, numMedians/2);
    int medianOfMediansValue = medians[tempMedianIndex];
    int medianOfMedianIndex = medianValueToIndex[medianOfMediansValue];
    
    // std::cout << "median values array after getting median: ";
    // for (int i = 0; i < numMedians; i++)
    // {
    //     std::cout << medians[i] << ",";
    // }
    // std::cout << std::endl;
    // std::cout << "median of medians value: " << medianOfMediansValue << std::endl;
    // std::cout << "median of medians index: " << medianOfMedianIndex << std::endl;

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
        return get_kth_smallest_v2(arr, pivot_index+1, right, k - pivot_index - 1);
    }
    else
    {
        // pivot index is the kth index in the array.
        // found our kth smallest item.
        return pivot_index;
    } 
}


// function: quicksort
//
// Description:
// Sort the array in-place using quicksort algorithm
//
// Notes:
// None
//
// Parameters:
// arr:     Integer array we wish to swap elements within.
// left:    Index of array to start sort
// right:   Index of array to end sort
//  
// return value:
// None, the array is sorted in-place from index 'left' to index 'right'.
void quicksort(int* arr, int left, int right)
{
    if (left < right)
    {
        int pivot_index = partition(arr, left, right);
        quicksort(arr, left, pivot_index -1 );
        quicksort(arr, pivot_index + 1, right);
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
    int* currArray = nullptr;
    int numTestRuns = 10;
    int arrSize = 20;
    int maxNum = 100;
    for (int i=0; i < numTestRuns; i++)
    {
        std::cout << "get_kth_smallest() Test #" << i+1 << std::endl;

        // get array of random numbers
        currArray = gen_random_int_array(arrSize, maxNum);

        // get random kth target
        //int target_k = (std::rand() % arrSize) + 1;
        int target_k = 10;
        std::cout << "target k = " << target_k << std::endl;

        std::cout << "Array Before getting kth smallest" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;

        int left_index = 0;
        int right_index = arrSize - 1;
        int kth_item_index = get_kth_smallest(currArray, left_index, right_index, target_k);
        int kth_item_value = currArray[kth_item_index];
        std::cout << "Array After kth_smallest" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << target_k << "th smallest item: " << kth_item_value << std::endl;

        // check if this is actually the case
        quicksort(currArray, 0, arrSize-1);
        std::cout << "Sorted array" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Does kth item match kth item in sorted array: ";
        if (currArray[target_k - 1] != kth_item_value)
        {
            std::cout << "FAIL" << std::endl;
        }
        else
        {
            std::cout << "PASS" << std::endl;
        }
        std::cout << "Does kth item index match k-1: ";
        if (target_k - 1 != kth_item_index)
        {
            std::cout << "FAIL" << std::endl;
        }
        else
        {
            std::cout << "PASS" << std::endl;
        }
        

        delete [] currArray;

        std::cout << std::endl;
    }
}

// function: run_kth_smallest_v2_test
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
void run_kth_smallest_v2_test()
{
    int* currArray = nullptr;
    int numTestRuns = 1;
    int arrSize = 50;
    int maxNum = 100;
    for (int i=0; i < numTestRuns; i++)
    {
        std::cout << "get_kth_smallest_v2() Test #" << i+1 << std::endl;

        // get array of random numbers
        currArray = gen_random_int_array(arrSize, maxNum);

        // get random kth target
        int target_k = (std::rand() % arrSize) + 1;

        std::cout << "Array: {";
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << ",";
        }
        std::cout << "};";
        std::cout << std::endl;
        std::cout << "target k = " << target_k << std::endl;

        int left_index = 0;
        int right_index = arrSize - 1;
        int kth_item_index = get_kth_smallest_v2(currArray, left_index, right_index, target_k);
        int kth_item_value = currArray[kth_item_index];

        std::cout << "Array After kth_smallest" << std::endl;
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << target_k << "th smallest item: " << kth_item_value << std::endl;


        // check if this is actually the case
        quicksort(currArray, 0, arrSize-1);
        std::cout << "Sorted Array: {";
        for(int i=0; i < arrSize; i++)
        {
            std::cout << currArray[i] << ",";
        }
        std::cout << "};";
        std::cout << std::endl;

        // is the chosen kth item in the kth place of the a sorted array?
        // does it match the kth item in a sorted array?
        bool pass = true;
        if (currArray[target_k - 1] != kth_item_value)
        {
            pass = false;
        }
        if (target_k - 1 != kth_item_index)
        {
            pass = false;
        }

        if (!pass)
        {
            std::cout << "FAIL" << std::endl;
            std::cout << target_k << "th item in original array: " << kth_item_value << std::endl;
            std::cout << target_k << "th item in sorted array: " << currArray[target_k - 1] << std::endl;
            std::cout << target_k << "th index in original array: " << kth_item_index << std::endl;
            std::cout << target_k << "th index in sorted array: " << target_k - 1 << std::endl;
        }

        delete [] currArray;
        
        std::cout << std::endl;
    }
}


// function: quicksort_test
//
// Description:
// Test quicksort() function on a number of random arrays
//
// Notes:
// None
//
// Parameters:
// None
//  
// return value:
// None
void run_quicksort_test()
{

    int* currArray = nullptr;
    int numTestRuns = 1;
    int arrSize = 1000000;
    int maxNum =  1000000;
    for (int i=0; i < numTestRuns; i++)
    {
        std::cout << "qucksort() Test #" << i+1 << std::endl;

        // get array of random numbers
        currArray = gen_random_int_array(arrSize, maxNum);

        int left_index = 0;
        int right_index = arrSize - 1;
        quicksort(currArray, left_index, right_index);

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
