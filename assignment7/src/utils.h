#ifndef UTILS_H
#define UTILS_H

#include <vector>

template <typename RandomIt>
void bubble_sort(RandomIt first, RandomIt last)
{
    // Implementation
    if (first == last)
        return;
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (auto it = first; it != last - 1; it++)
        {
            // Default ascending
            if (*it > *(it + 1))
            {
                std::swap(*it, *(it + 1));
                swapped = true;
            }
        }
        last--;
    }
}

template <typename RandomIt, typename Compare>
void bubble_sort(RandomIt first, RandomIt last, Compare comp)
{
    if (first == last)
        return;
    // Implementation
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (auto it = first; it != last - 1; it++)
        {
            if (comp(*(it + 1), *it))
            {
                std::swap(*it, *(it + 1));
                swapped = true;
            }
        }
        last--;
    }
}

#endif // UTILS_H