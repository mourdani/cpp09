#include "../inc/PmergeMe.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No input sequence provided." << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::list<int> lst;

    // Parse input sequence and store in containers
    try {
    for (int i = 1; i < argc; i++) {
        int num = std::atoi(argv[i]);
            for(int j=0; argv[i][j]!='\0';j++) {
                if(argv[i][j] < '0' || argv[i][j] > '9')
                    { return(std::cout << "Error: bad input: [" << argv[i][j] << "]" << std::endl, 1); }
                vec.push_back(num);
                lst.push_back(num);           
            }
        
        std::cout << num << " ";
    }
    }
    catch (const std::invalid_argument& e) 
        { return(std::cout << e.what() << std::endl, 1);}
    std::cout << std::endl;


    // find size vec
    int nVec = vec.size();
   // int nLst = lst.size();

    // Sort with vector and measure time
    mergeInsertVec(vec, 0, nVec - 1);
//
//    // Sort with list and measure time
//    std::clock_t start_lst = std::clock();
//    mergeInsertList(lst, 0 , nLst-1);
//    std::clock_t end_lst = std::clock();
//    double elapsed_lst = static_cast<double>(end_lst - start_lst) / CLOCKS_PER_SEC * 1000000;
//
//    // Display sorted sequence with vector
//    std::cout << "<vec>After: ";
//    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;
//
//    // Display sorted sequence with list
//    std::cout << "<list>After: ";
//    for (std::list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;
//
//    // Display time taken by vector sort
//
//    // Display time taken by list sort
//    std::cout << "Time to process a range of " << lst.size() << " elements with list sort: " << elapsed_lst << " us" << std::endl;
//
    return 0;
}