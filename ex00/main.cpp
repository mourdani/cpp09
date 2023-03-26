#include "BitcoinExchange.hpp"

int main (int argc, char **argv) {
	try {
		
	if (argc != 2) throw std::runtime_error("usage: ./btc \"input_file.txt\"");
	
	std::map<std::string, double> exchange_rates = parseCSV("data.csv");


	checkInput(argv[1], exchange_rates);
	
	//displayMap(exchange_rates);
	
	} catch (const std::exception& e) { std::cout << e.what() << '\n'; return 1; }
	return 0;
}