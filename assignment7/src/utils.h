#ifndef UTILS_H
#define UTILS_H

#include <vector>

template <typename RandomIt>
void bubble_sort(RandomIt first, RandomIt last)
{
    // Implementation
}

template <typename RandomIt, typename Compare>
void bubble_sort(RandomIt first, RandomIt last, Compare comp)
{
    // Implementation
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (comp(arr[j + 1], arr[j]))
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

#endif // UTILS_H