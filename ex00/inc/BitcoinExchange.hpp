#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <cstdlib>
#include <map>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &src){ *this = src;};
    ~BitcoinExchange() {};
    BitcoinExchange &operator=(const BitcoinExchange &rhs) { (void)rhs; return *this; };

    void display_history();
    double find_rate(const std::string& date, const std::map<std::string, double>& data);
    void process_input_file(char *file);

private: 
    std::map<std::string, double> data;
    std::map<std::string, double> parse_CSV(std::string csv_file);
    bool check_date(const std::string& date);
    bool check_value(const std::string& value);
    std::string nearest_date(const std::string& current_date);
};


#endif