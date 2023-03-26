#include "BitcoinExchange.hpp"

#include "BitcoinExchange.hpp"

std::map<std::string, double> parseCSV(std::string csv_file) {
    
    std::map<std::string, double> data;

    std::ifstream inputFile(csv_file);
    if (!inputFile) { throw std::runtime_error("Failed to open data file."); }

    std::string line;
    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string date, rate;
        std::getline(ss, date, ',');
        std::getline(ss, rate, ',');

        try {
            double exchange_rate = std::stod(rate);
            data[date] = exchange_rate;
        } catch (const std::exception&) { throw std::runtime_error("Invalid data in data file."); }
    }

    inputFile.close();
    return data;
}

void checkInput(char *file, std::map<std::string, double> data) {
    
    std::ifstream inputFile(file);
    if (!inputFile) { throw std::runtime_error("Error: Failed to open Input file."); }

    std::string firstLine;
    std::getline(inputFile, firstLine);
    if (firstLine != "date | value") { throw std::runtime_error("Error: Input file not recognised."); }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string date, value;
        char separator;
        if (!(iss >> date >> separator >> value) || separator != '|') {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!check_date(date) || !check_value(value)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        double doubleValue = stod(value);
        if (doubleValue < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (doubleValue > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        double result = doubleValue * findRate(date, data);
        std::cout << date << " => " << value << " = " << result << std::endl;
    }

    inputFile.close();
}

double findRate(const std::string& date, const std::map<std::string, double>& data) {
    auto rateIt = data.find(date);
    if (rateIt != data.end()) { return rateIt->second; }

    const std::string previousDay = getPreviousDate(date);
    if (previousDay == "not valid date") { return 0; }

    return findRate(previousDay, data);
}   

std::string getPreviousDate(const std::string& date) {
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
    int prev_day = day - 1;
    int prev_month = month;
    int prev_year = year;
    if (prev_day == 0) {
        prev_month = month - 1;
        if (prev_month == 0) {
            prev_month = 12;
            prev_year = year - 1;
            if (prev_year < 2009) {
                return "not valid date";
            }
        }
        switch (prev_month) {
            case 2:
                if (prev_year % 4 == 0 && (prev_year % 100 != 0 || prev_year % 400 == 0)) {
                    prev_day = 29;
                } else {
                    prev_day = 28;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                prev_day = 30;
                break;
            default:
                prev_day = 31;
        }
    }
    std::string prev_date = std::to_string(prev_year) + "-";
    if (prev_month < 10)
        prev_date += "0" + std::to_string(prev_month);
    else
        prev_date += std::to_string(prev_month);
    if (prev_day < 10)
        prev_date += "-0" + std::to_string(prev_day);
    else
        prev_date += "-" + std::to_string(prev_day);
    return (prev_date);
}

bool check_date(const std::string& date) {
    try {
        if (date.length() != 10) { throw std::invalid_argument("Invalid date format. use \"Year-Month-Day\" instead"); }
        
        int year, month, day;
        char separator1, separator2;
        std::istringstream ss(date);
        ss >> year >> separator1 >> month >> separator2 >> day;
        
        if (ss.fail() || separator1 != '-' || separator2 != '-'
            || year < 0 
            || month < 1 || month > 12 
            || day < 1 || day > 31) 
        { throw std::invalid_argument("Invalid date format"); }
        
        bool leap_year = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
        if ((month == 2 && (leap_year ? day > 29 : day > 28)) ||
            ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) 
        { throw std::invalid_argument("Invalid day for given month and year"); }
        
        return true;
    }
    catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; return false; }
}

bool check_value(const std::string& value) {
    try { std::stof(value); }
    catch (const std::invalid_argument& e) { return false; }
    return true;
}

void displayMap(const std::map<std::string, double>& map) {
    for (std::map<std::string, double>::const_iterator it = map.begin(); it != map.end(); ++it)
    { std::cout << it->first << "=" << it->second << " \n"; }
}
