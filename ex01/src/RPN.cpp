#include "../inc/RPN.hpp"

int RPN(char *argv)
{
    std::stack<int> _stack;
    std::istringstream ss(argv);

    std::string token;
    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (_stack.size() < 2) {
                std::cout << "Error: More numbers needed for this operation." << std::endl;
                exit (1);
            }

            int b = _stack.top();
            _stack.pop(); 

            int a = _stack.top();
            _stack.pop();

            int res = 0;

            if (token == "+") res = a + b;
            else if (token == "-") res = a - b;
            else if (token == "*") res = a * b;
            else if (token == "/") {
                if (b == 0) { std::cout << "Error: Invalid division" << std::endl; exit (1); }
                res = a / b;
            }

            _stack.push(res);
        } 
        else { 
            for(int i=0; token[i]; i++) { 
                if(token[i] < '0' || token[i] > '9') {
                    std::cout << "Error: bad input : [" << token << "]" << std::endl;
                    exit (1);
                }
            }
            int num = atoi(token.c_str()); 
            _stack.push(num);
        }
    }

    if (_stack.size() != 1) { 
        std::cout << "Error: Invalid input expression." << std::endl;
        exit (1);
    }
    return _stack.top();
}
