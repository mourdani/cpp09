#include "../inc/PmergeMe.hpp"

void vector_inser_sort(std::vector<int>& A, int p, int q) {
    for (int i = p; i < q; i++) {
        int tempVal = A[i + 1];
        int j = i + 1;
        while (j > p && A[j - 1] > tempVal) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = tempVal;
    }
}

void vector_merge_sort(std::vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<int> LA(n1), RA(n2);
    for (int i = 0; i < n1; i++) {
        LA[i] = A[p + i];
    }
    for (int i = 0; i < n2; i++) {
        RA[i] = A[q + 1 + i];
    }
    int RIDX = 0;
    int LIDX = 0;
    for (int i = p; i <= r; i++) {
        if (RIDX == n2) {
            A[i] = LA[LIDX];
            LIDX++;
        } else if (LIDX == n1) {
            A[i] = RA[RIDX];
            RIDX++;
        } else if (RA[RIDX] > LA[LIDX]) {
            A[i] = LA[LIDX];
            LIDX++;
        } else {
            A[i] = RA[RIDX];
            RIDX++;
        }
    }
}

/* 
    * @brief: merge sort with insertion sort
    * @param: A: vector to be sorted
    * @param: p: start index
    * @param: r: end index
    * @return: void
    * @note:
    *     */ 

// in c++11
void vector_merge_insert(std::vector<int>& A, int p, int r) {
    std::clock_t start_vec = std::clock();
    if (r - p > K) {
        int q = (p + r) / 2;
        vector_merge_insert(A, p, q);
        vector_merge_insert(A, q + 1, r);
        vector_merge_sort(A, p, q, r);
    } else {
        vector_inser_sort(A, p, r);
    }
    std::clock_t end_vec = std::clock();
    double elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC * 1000000;
    if (p == 0 && (unsigned long)r == A.size() - 1)
        std::cout << "number of arguments: " << A.size() << " time: " << elapsed_vec << " us" << std::endl;
        //std::cout << "Time to process a range of " << A.size() << " elements with vector sort: " << elapsed_vec << " us" << std::endl;
}


// int main() {
//     std::vector<int> A;
//     A.push_back(5);
//     A.push_back(3);
//     A.push_back(9);
//     A.push_back(2);
//     A.push_back(8);
//     A.push_back(7);
//     A.push_back(1);
//     A.push_back(4);
//     A.push_back(6);
//     int n = A.size();
//     vector_merge_insert(A, 0, n - 1);
//     for (int i = 0; i < n; i++) {
//         std::cout << A[i] << " ";
//     }
//     std::cout << std::endl;
//     return 0;
// }