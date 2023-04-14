#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    this->data = parse_CSV(CSVFILE);
}

std::map<std::string, double> BitcoinExchange::parse_CSV(std::string csv_file) {
    std::map<std::string, double> data;
    std::ifstream inputFile(csv_file.c_str());

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
            double exchange_rate = std::atof(rate.c_str());

            data[date] = exchange_rate;
        }
        catch (const std::exception&)
            { throw std::runtime_error("Invalid data in data file.");}
    }

    inputFile.close();
    return data;
}

void BitcoinExchange::process_input_file(char *file) {
    std::ifstream inputFile(file);
    if (!inputFile) { throw std::runtime_error("Error: Failed to open Input file."); }

    std::string firstLine;
    std::getline(inputFile, firstLine);
    if (firstLine != "date | value")
        { throw std::runtime_error("Error: Input file not recognised."); }

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
            std::cerr << date << std::endl;
            continue;
        }
        double doubleValue = atof(value.c_str());
        double result = doubleValue * find_rate(date, this->data);
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
    inputFile.close();
}

double BitcoinExchange::find_rate(const std::string& date, const std::map<std::string, double>& data) {
    std::map<std::string, double>::const_iterator rateIt = data.find(date);
    if (rateIt != data.end()) { return rateIt->second; }

    std::string previous_day = nearest_date(date);
    if (previous_day == "not valid date") { return 0; }


    return find_rate(previous_day, data);
}   

std::string BitcoinExchange::nearest_date(const std::string& current_date) {
    int year = std::atoi(current_date.substr(0, 4).c_str());
    int month = std::atoi(current_date.substr(5, 2).c_str());
    int day = std::atoi(current_date.substr(8, 2).c_str());

    if (year > 2023)
        { year = 2022; month = 03; day = 29;}


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
    std::ostringstream prev_year_str, prev_month_str, prev_day_str;
    prev_year_str << prev_year;
    prev_month_str << prev_month;
    prev_day_str << prev_day;

    std::string prev_date = prev_year_str.str() + "-";
    if (prev_month < 10)
        prev_date += "0" + prev_month_str.str();
    else
        prev_date += prev_month_str.str();
    if (prev_day < 10)
        prev_date += "-0" + prev_day_str.str();
    else
        prev_date += "-" + prev_day_str.str();

    return (prev_date);
}

bool BitcoinExchange::check_date(const std::string& date) {
    if (date.length() != 10)
        return (std::cout << "Error: bad date => " ,false); 

    
    int year, month, day;
    char sep1, sep2;
    std::istringstream ss(date);
    ss >> year >> sep1 >> month >> sep2 >> day;
    
    if (ss.fail() || sep1 != '-' || sep2 != '-'
        || year < 2009 
        || month < 1 || month > 12 
        || day < 1 || day > 31) 
    {

        std::cerr << "Error: bad date => ";
        return false; 
    }
    bool leap_year = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    if ((month == 2 && (leap_year ? day > 29 : day > 28)) ||
        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) 
        {
            std::cerr << "Error: bad date => ";;
        return false; 
        }
    return true;
}

bool BitcoinExchange::check_value(const std::string& value) {
    std::istringstream iss(value);
    double d;
    iss >> std::noskipws >> d;
    if (iss.fail() || !iss.eof()) {
            std::cerr << "Error: bad value => ";
        return false;
    }
    if (d < 0 || d > 1000) {
            std::cerr << "Error: bad value => ";
        return false;
    }
    return true;
}

void BitcoinExchange::display_history() {
    for (std::map<std::string, double>::const_iterator it = this->data.begin(); it != this->data.end(); ++it)
    { std::cout << it->first << "=" << it->second << " \n"; }
}
