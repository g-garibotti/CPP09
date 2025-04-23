#include "BitcoinExchange.hpp"

// Orthodox Canonical Form implementations
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Helper method to validate date format (YYYY-MM-DD)
bool BitcoinExchange::isValidDate(const std::string &date) const {
    // Check format "YYYY-MM-DD"
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    // Check that all characters in the expected positions are digits
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7) {  // Skip the dash positions
            if (!isdigit(date[i]))
                return false;
        }
    }
    
    // Extract year, month, day
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    
    // Validate ranges
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    
    // Validate specific month-day relationships
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    
    // February
    if (month == 2) {
        bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((leapYear && day > 29) || (!leapYear && day > 28))
            return false;
    }
    
    return true;
}

// Helper method to validate value (0 <= value <= 1000)
bool BitcoinExchange::isValidValue(const float value) const {
    return value >= 0.0f && value <= 1000.0f;
}

// Find the closest previous date in the database
std::string BitcoinExchange::findClosestDate(const std::string &date) const {
    // Check for exact match first
    std::map<std::string, float>::const_iterator exact = _database.find(date);
    if (exact != _database.end()) {
        return date; // Exact match found
    }
    
    // Use upper_bound to find the first element greater than the date
    std::map<std::string, float>::const_iterator it = _database.upper_bound(date);
    
    if (it == _database.begin()) {
        // No previous date available
        return "";
    }
    
    // Move to the previous element (which is the closest date less than the given date)
    --it;
    return it->first;
}

// Load the database from a CSV file
void BitcoinExchange::loadDatabase(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileOpenException();
    }
    
    std::string line;
    // Skip header line (if it exists)
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        float value;
        
        if (std::getline(iss, date, ',') && (iss >> value)) {
            // Trim whitespace from date if needed
            date.erase(0, date.find_first_not_of(" \t"));
            date.erase(date.find_last_not_of(" \t") + 1);
            
            if (isValidDate(date))
                _database[date] = value;
        }
    }
    file.close();
    
    // Check if database is empty
    if (_database.empty()) {
        throw EmptyDatabaseException();
    }
}

// Process the input file and compute Bitcoin values
void BitcoinExchange::processInputFile(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileOpenException();
    }
    
    std::string line;
    // Skip header line (if it exists)
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        // Check if line is empty
        if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }
        
        std::istringstream iss(line);
        std::string date;
        std::string valueStr;
        
        // Try to split by pipe
        if (std::getline(iss, date, '|') && std::getline(iss, valueStr)) {
            // Trim whitespace from date and value
            date.erase(0, date.find_first_not_of(" \t"));
            date.erase(date.find_last_not_of(" \t") + 1);
            
            valueStr.erase(0, valueStr.find_first_not_of(" \t"));
            valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
            
            // Check date validity
            if (!isValidDate(date)) {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
            
            // Convert value string to float
            char* endPtr;
            float value = strtof(valueStr.c_str(), &endPtr);
            
            // Check for conversion errors
            if (*endPtr != '\0') {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            
            // Check value constraints
            if (value < 0) {
                std::cerr << "Error: not a positive number." << std::endl;
                continue;
            }
            
            if (value > 1000) {
                std::cerr << "Error: too large a number." << std::endl;
                continue;
            }
            
            // Find closest date in database
            std::string closestDate = findClosestDate(date);
            if (closestDate.empty()) {
                std::cerr << "Error: no valid date found in database." << std::endl;
                continue;
            }
            
            // Calculate and display result
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