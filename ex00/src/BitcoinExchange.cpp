#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    this->data = parse_CSV(CSVFILE);
}

std::map<std::string, double> BitcoinExchange::parse_CSV(std::string csv_file) {
    
    std::map<std::string, double> data;
    std::ifstream inputFile(csv_file);
    std::cout << csv_file << std::endl;
    if (!inputFile) { throw std::runtime_error("Failed to open CSV data file."); }

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

void BitcoinExchange::process_input_file(char *file) {
    std::ifstream inputFile(file);
    if (!inputFile) { throw std::runtime_error("Error: Failed to open Input file."); }

    std::string firstLine;
    std::getline(inputFile, firstLine);
    if (firstLine != "date | value") { throw std::runtime_error("Error: Input file not recognised."); }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line); 
        std::string date, value;
        char sep;
        if (!(iss >> date >> sep >> value) || sep != '|') {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!check_date(date) || !check_value(value)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        double doubleValue = stod(value);
        double result = doubleValue * find_rate(date, this->data);
        std::cout << date << " => " << value << " = " << result << std::endl;
    }

    inputFile.close();
}

double BitcoinExchange::find_rate(const std::string& date, const std::map<std::string, double>& data) {
    auto rateIt = data.find(date);
    if (rateIt != data.end()) { return rateIt->second; }

    std::string previous_day = nearest_date(date);
    if (previous_day == "not valid date") { return 0; }

    return find_rate(previous_day, data);
}   

std::string BitcoinExchange::nearest_date(const std::string& current_date) {

    // extract year, month, day from current_date
    int year = std::stoi(current_date.substr(0, 4));
    int month = std::stoi(current_date.substr(5, 2));
    int day = std::stoi(current_date.substr(8, 2));


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
                if (prev_year % 4 == 0 && (prev_year % 100 != 0 || prev_year % 400 == 0))
                    prev_day = 29;
                else
                    prev_day = 28;
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

bool BitcoinExchange::check_date(const std::string& date) {
    if (date.length() != 10)
        return false; 
    
    int year, month, day;
    char sep1, sep2;
    std::istringstream ss(date);
    ss >> year >> sep1 >> month >> sep2 >> day;
    
    if (ss.fail() || sep1 != '-' || sep2 != '-'
        || year < 0 
        || month < 1 || month > 12 
        || day < 1 || day > 31) 
        return false; 
    
    bool leap_year = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    if ((month == 2 && (leap_year ? day > 29 : day > 28)) ||
        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) 
        return false; 
    
    return true;
}

bool BitcoinExchange::check_value(const std::string& value) {
    if (std::stod(value) < 0 || std::stod(value) > 10000000000)
        return false;
    return true;
}

void BitcoinExchange::display_history() {
    for (std::map<std::string, double>::const_iterator it = this->data.begin(); it != this->data.end(); ++it)
    { std::cout << it->first << "=" << it->second << " \n"; }
}
