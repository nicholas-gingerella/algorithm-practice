// File: quickselect_tests.cpp
// Author: Nick Gingerella
// Description:
// Simple unit tests for quickselect algorithm using GoogleTest
#include <gtest/gtest.h>
#include "quickselect.h"

TEST(KthSmallestTest, NonEmptyList)
{
    int target_kth_element = 57;

    int size = 10;
    int k = 7;
    int input[size] = {5,99,3,57,21,58,94,31,11,26};

    // Get 7th smallest element from list
    int kth_index = get_kth_smallest(input, 0, size - 1, k);

    EXPECT_EQ(input[kth_index], target_kth_element);
}

TEST(KthSmallestTest, ListSmallerThanK)
{
    // Error case should return -1
    int target_kth_index = -1;

    int size = 5;
    int k = 7;
    int input[size] = {5,99,3,57,21};

    // Get 7th smallest element from list
    int kth_index = get_kth_smallest(input, 0, size - 1, k);

    EXPECT_EQ(kth_index, target_kth_index);
}

TEST(KthSmallestTest, InvalidK)
{
    // Error case should return -1
    int target_kth_index = -1;

    int size = 5;
    int k = 0;
    int input[size] = {58,94,31,11,26};

    // Get 7th smallest element from list
    int kth_index = get_kth_smallest(input, 0, size - 1, k);

    EXPECT_EQ(kth_index, target_kth_index);
}

int main(int argc, char** argv)
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}