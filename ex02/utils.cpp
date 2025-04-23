#include "PmergeMe.hpp"

void printTimes(int size, double vecTime, double dequeTime, double stdVecTime) {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Time to process a range of " << size << " elements with std::vector : " << vecTime << " s" << std::endl;
    std::cout << "Time to process a range of " << size << " elements with std::deque  : " << dequeTime << " s" << std::endl;
    std::cout << "Time for std::sort() to process a range of " << size << " elements  : " << stdVecTime << " s" << std::endl;
}

void startSorts(std::vector<int> vec, std::deque<int> deque) {
    // Display the input sequence
    std::cout << "Before: " << vec << std::endl;
    
    std::clock_t start, end;
    double vecTime, dequeTime, stdVecTime;
    
    // Standard sort for comparison
    std::vector<int> stdSortVec = vec;
    start = std::clock();
    std::sort(stdSortVec.begin(), stdSortVec.end());
    end = std::clock();
    stdVecTime = double(end - start) / CLOCKS_PER_SEC;
    
    // Vector merge-insertion sort
    start = std::clock();
    vec = PmergeVec(vec);
    end = std::clock();
    vecTime = double(end - start) / CLOCKS_PER_SEC;
    
    // Deque merge-insertion sort
    start = std::clock();
    deque = PmergeDeque(deque);
    end = std::clock();
    dequeTime = double(end - start) / CLOCKS_PER_SEC;
    
    // Display the sorted sequence
    std::cout << "After:  " << vec << std::endl;
    
    // Print timing information
    printTimes(vec.size(), vecTime, dequeTime, stdVecTime);
}

bool isNumOnly(char *arg) {
    for (int i = 0; arg[i] != '\0'; i++) {
        if (!std::isdigit(arg[i])) {
            return false;
        }
    }
    return true;
}

std::vector<int> parseArgs(char **av) {
    std::vector<int> tab;
    long long num;
    
    for (int i = 0; av[i]; i++) {
        if (av[i][0] == '-')
            throw std::invalid_argument("Error: only positive number allowed");
        if (!isNumOnly(av[i]))
            throw std::invalid_argument("Error: unrecognized argument");
            
        num = std::atoll(av[i]);
        if (num > INT_MAX) {
            throw std::invalid_argument("Error: number too large");
        }
        tab.push_back(static_cast<int>(num));
    }
    
    return tab;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& tab) {
    if (tab.empty())
        return os;
        
    const int MAX_DISPLAY = 4;
    int i = 0;
    
    for (std::vector<int>::const_iterator it = tab.begin(); it != tab.end(); ++it) {
        if (i > MAX_DISPLAY) {
            os << " [...]";
            break;
        }
        
        os << *it;
        if (it + 1 != tab.end() && i < MAX_DISPLAY) {
            os << " ";
        }
        ++i;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::deque<int>& tab) {
    if (tab.empty())
        return os;
        
    const int MAX_DISPLAY = 4;
    int i = 0;
    
    for (std::deque<int>::const_iterator it = tab.begin(); it != tab.end(); ++it) {
        if (i > MAX_DISPLAY) {
            os << " [...]";
            break;
        }
        
        os << *it;
        if (it + 1 != tab.end() && i < MAX_DISPLAY) {
            os << " ";
        }
        ++i;
    }
    return os;
}