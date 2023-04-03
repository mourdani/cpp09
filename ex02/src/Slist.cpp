#include "../inc/PmergeMe.hpp"

void Slist::insertion_sort(int start, int middle) {
    std::list<int>::iterator it_i = l.begin();
    std::advance(it_i, start);
    for (int i = start; i < middle; i++, it_i++) {
        // Get the value at index (i+1)
        std::list<int>::iterator it_j = it_i;
        it_j++;
        int tempVal = *it_j;
        int j = i + 1;
        // Shift elements to the right to make space for the current element
        std::list<int>::iterator it_shift = it_j;
        it_shift--;
        while (j > start && (*it_shift) > tempVal) {
            *it_j = *it_shift;
            it_j = it_shift;
            it_shift--;
            j--;
        }
        // Insert the current element at its correct position
        *it_j = tempVal;
    }
}

void Slist::merge(int start, int middle, int end) {
    int len1 = middle - start + 1, len2 = end - middle;
    std::list<int> left, right;

    // Copy elements from the left sublist to left
    std::list<int>::iterator it = l.begin();
    std::advance(it, start);
    for (int i = 0; i < len1; i++, it++) {
        left.push_back(*it);
    }
    // Copy elements from the right sublist to right
    it = l.begin();
    std::advance(it, middle + 1);
    for (int i = 0; i < len2; i++, it++) {
        right.push_back(*it);
    }
    int li = 0;
    int ri = 0;
    // Merge left and right into l
    it = l.begin();
    std::advance(it, start);
    for (int i = start; i <= end; i++, it++) {
        if (li == len1) {
            *it = right.front();
            right.pop_front();
            ri++;
        } else if (ri == len2) {
            *it = left.front();
            left.pop_front();
            li++;
        } else if (left.front() <= right.front()) {
            *it = left.front();
            left.pop_front();
            li++;
        } else {
            *it = right.front();
            right.pop_front();
            ri++;
        }
    }
}

void Slist::timsort(int p, int r) {
    if (r - p > RUN) {
        int q = (p + r) / 2;
        timsort(p, q);
        timsort(q + 1, r);
        merge(p, q, r);
    }
    else
        insertion_sort(p, r);
}

void Slist::print() {
    std::list<int>::iterator it = l.begin();
    for (long unsigned int i = 0; i < l.size(); i++, it++) {
        std::cout << GREEN << *it << " ";
    }
    std::cout << RESET << std::endl;
}
