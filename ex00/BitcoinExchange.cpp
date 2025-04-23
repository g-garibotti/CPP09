#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}





bool BitcoinExchange::isValidDate(const std::string &date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7) { 
            if (!isdigit(date[i]))
                return false;
        }
    }
    
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    
    if (month == 2) {
        bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((leapYear && day > 29) || (!leapYear && day > 28))
            return false;
    }
    
    return true;
}

bool BitcoinExchange::isValidValue(const float value) const {
    return value >= 0.0f && value <= 1000.0f;
}

std::string BitcoinExchange::findClosestDate(const std::string &date) const {
    std::map<std::string, float>::const_iterator exact = _database.find(date);
    if (exact != _database.end()) {
        return date;
    }
    std::map<std::string, float>::const_iterator it = _database.upper_bound(date);
    
    if (it == _database.begin()) {
        return "";
    }

    --it;
    return it->first;
}

void BitcoinExchange::loadDatabase(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileOpenException();
    }
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        float value;
        
        if (std::getline(iss, date, ',') && (iss >> value)) {
            date.erase(0, date.find_first_not_of(" \t"));
            date.erase(date.find_last_not_of(" \t") + 1);
            
            if (isValidDate(date))
                _database[date] = value;
        }
    }
    file.close();
    if (_database.empty()) {
        throw EmptyDatabaseException();
    }
}

void BitcoinExchange::processInputFile(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileOpenException();
    }
    
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }
        
        std::istringstream iss(line);
        std::string date;
        std::string valueStr;
        
        if (std::getline(iss, date, '|') && std::getline(iss, valueStr)) {
            date.erase(0, date.find_first_not_of(" \t"));
            date.erase(date.find_last_not_of(" \t") + 1);
            
            valueStr.erase(0, valueStr.find_first_not_of(" \t"));
            valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
            
            if (!isValidDate(date)) {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
            
            char* endPtr;
            float value = strtof(valueStr.c_str(), &endPtr);
            
            if (*endPtr != '\0') {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            
            if (value < 0) {
                std::cerr << "Error: not a positive number." << std::endl;
                continue;
            }
            
            if (value > 1000) {
                std::cerr << "Error: too large a number." << std::endl;
                continue;
            }
            
            std::string closestDate = findClosestDate(date);
            if (closestDate.empty()) {
                std::cerr << "Error: no valid date found in database." << std::endl;
                continue;
            }
            
            float exchangeRate = _database[closestDate];
            float result = value * exchangeRate;
            
            std::cout << date << " => " << value << " = " << result << std::endl;
        }
        else {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
    file.close();
}