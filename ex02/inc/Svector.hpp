#ifndef SVECTOR_HPP
#define SVECTOR_HPP

#include "PmergeMe.hpp"

class Svector {
public:
	Svector()  {}
	Svector(std::vector<int> vec) { v = vec; }
	Svector& operator=(const std::vector<int>& vec) {
		v = vec;
		return *this;
	}
	~Svector() {}
	void	timsort(int n);
	void	print();
	int 	size() { return v.size(); }


private:
	std::vector<int> v;
	void	insertion_sort(int start, int end);
	void	merge(int start, int middle, int end);
};



#endif
