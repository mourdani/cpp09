#include "../inc/RPN.hpp"

std::string parse_equation(char *str) {
	std::string equation(str);
	size_t i = 0;
	while (equation[i]) {
		if (equation[i] == ' ')
			equation.erase(i, 1);
		else
			i++;
	}
	
	return equation;
}
int main (int argc, char **argv) {
	try {
	(void)argc;

	// parse equation
	std::string equation = parse_equation(argv[1]);
	std::cout << equation << std::endl;

	// convert to stack
	std::stack<int> numbers_stack;
	std::stack<char> operators_stack;

	for (size_t i = equation.length() - 1; i > 0; i--) {
		if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '%') 
			operators_stack.push(equation[i]);
		else 
			numbers_stack.push(equation[i] - '0');
	}
	numbers_stack.push(equation[0] - '0');

	// print numbers stack 
	std::cout << "numbers stack: " << std::endl;
	while (!numbers_stack.empty()) {
		std::cout << numbers_stack.top() << std::endl;
		numbers_stack.pop();
	}

	// print operators stack
	std::cout << std::endl << "operators stack: ";
	while (!operators_stack.empty()) {
		std::cout << operators_stack.top() << std::endl;
		operators_stack.pop();
	}
	}
	catch (std::exception &e) {}	
	return 0;
}