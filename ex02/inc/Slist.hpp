#ifndef SLIST_HPP
#define SLIST_HPP

#include "PmergeMe.hpp"

class Slist {
public:
	Slist() {}
	Slist(std::list<int> lst) { l = lst; }
	Slist& operator=(const std::list<int>& lst) {
		l = lst;
		return *this;
	}
	~Slist() {}
	void	timsort(int p, int r);
	void	print();
	int	size() { return l.size(); }
private:
	std::list<int> l;
	void	insertion_sort(int start, int middle);
	void	merge(int start, int middle, int end);
};


#endif
