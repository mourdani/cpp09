#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <map>

#define MAX	2147483647


std::map<std::string, double> parseCSV(std::string csv_file);

double findRate(const std::string& date, const std::map<std::string, double>& data);
void checkInput(char *file, std::map<std::string, double> data);
void display_map(const std::map<std::string, double>& myMap);
std::string getPreviousDate(const std::string& currentDate);
bool check_date(const std::string& date);
bool check_value(const std::string& value);

#endif
