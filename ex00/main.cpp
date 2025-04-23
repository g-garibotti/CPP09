#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
    // Check if an input file is provided
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try {
        // Create a BitcoinExchange object
        BitcoinExchange btc;
        
        // Load the database (assuming data.csv is in the current directory)
        btc.loadDatabase("data.csv");
        
        // Process the input file
        btc.processInputFile(argv[1]);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}