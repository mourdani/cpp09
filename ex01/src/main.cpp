#include "../inc/RPN.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./RPN \"Reverse polish notation\"\nexample: ./RPN  \"8 9 * 9 -\"" << std::endl;
        exit (1);
    }

    std::cout << "Result: " << RPN(argv[1]) << std::endl;
    return 0;
}