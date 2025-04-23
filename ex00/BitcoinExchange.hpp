#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <exception>

class BitcoinExchange {
private:
    std::map<std::string, float> _database;
    
    bool isValidDate(const std::string &date) const;
    bool isValidValue(const float value) const;
    std::string findClosestDate(const std::string &date) const;
    
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();
    
    class FileOpenException : public std::exception {
    public:
        virtual const char *what() const throw() {
            return "could not open file";
        }
    };
    
    class EmptyDatabaseException : public std::exception {
    public:
        virtual const char *what() const throw() {
            return "database is empty";
        }
    };
    
    void loadDatabase(const std::string &filename);
    void processInputFile(const std::string &filename);
};

#endif