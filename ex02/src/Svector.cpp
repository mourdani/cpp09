#include "../inc/Svector.hpp"

void Svector::insertion_sort(int start, int end) {
	for (int i = start + 1; i <= end; i++)
	{
		int temp = v[i];
		int j = i - 1;
		while (j >= start && v[j] > temp) {
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = temp;
	}
}

void Svector::merge(int start, int middle, int end) {

	int len1 = middle - start + 1, len2 = end - middle;
	std::vector<int> left(len1), right(len2);
	for (int i = 0; i < len1; i++)
		left[i] = v[start + i];
	for (int i = 0; i < len2; i++)
		right[i] = v[middle + 1 + i];

	int li = 0;
	int ri = 0;
	int vi = start;

	while (li < len1 && ri < len2) {
		if (left[li] <= right[ri])
			v[vi] = left[li++];
      		else 
			v[vi] = right[ri++];
		vi++;
	}

	while (li < len1) 
		v[vi++] = left[li++]; 

	while (ri < len2) 
		v[vi++] = right[ri++];
}

void Svector::timsort(int n) {
	for (int i = 0; i < n; i+=RUN)
		insertion_sort(i, std::min((i+RUN-1), (n-1)));

	for (int size = RUN; size < n; size *= 2) {
		
		for (int left = 0; left < n; left += 2 * size) {
			int mid = left + size - 1;
			int right = std::min((left + 2 * size - 1), (n-1));

			if(mid < right)
				merge(left, mid, right);
		}
	}
}

void Svector::print() {
	for (long unsigned int i = 0; i < v.size(); i++)
		std::cout << GREEN << v[i] << " ";
	std::cout << RESET << std::endl;
}
