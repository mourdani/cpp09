#include "../inc/PmergeMe.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No input sequence provided." << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::list<int> lst;

    try {
    for (int i = 1; i < argc; i++) {
        int num = std::atoi(argv[i]);
            for(int j=0; argv[i][j]!='\0';j++) {
                if(argv[i][j] < '0' || argv[i][j] > '9')
                    { return(std::cout << "Error: bad input: [" << argv[i][j] << "]" << std::endl, 1); 
                }
            }
            vec.push_back(num);
            lst.push_back(num);           
    }
    }
    catch (const std::invalid_argument& e) 
        { return(std::cout << e.what() << std::endl, 1);}

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Original Order    : ";
    for (long unsigned int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;
    Svector svec(vec);
    std::clock_t start = std::clock();
    svec.timsort(svec.size());
    std::clock_t end = std::clock();
    double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "sorted            : ";
    svec.print();

    std::cout << "--------------------------------------------------" << std::endl;
    Slist slst(lst);
    std::clock_t start2 = std::clock();
    slst.timsort(0, slst.size() - 1);
    std::clock_t end2 = std::clock();
    double elapsed2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000;

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << elapsed << " ms" << std::endl;
    std::cout << "Time to process a range of " << lst.size() << " elements with std::list   : " << elapsed2 << " ms" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    return 0;
}
