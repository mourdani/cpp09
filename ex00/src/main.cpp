#include "../inc/BitcoinExchange.hpp"

int main (int argc, char **argv) {
	try {
		
	if (argc != 2) throw std::runtime_error("usage: ./btc \"input_file.txt\"");
	
	BitcoinExchange exchange;
	exchange.process_input_file(argv[1]);
	
	
	//exchange.display_history();
	
	} catch (const std::exception& e) { std::cout << e.what() << '\n'; return 1; }
	return 0;
}