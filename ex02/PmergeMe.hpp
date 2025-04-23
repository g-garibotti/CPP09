#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>   // Pour std::sort, std::lower_bound, std::max, std::min
# include <climits>     // Pour INT_MAX
# include <cmath>       // Pour std::pow
# include <cstdlib>     // Pour EXIT_SUCCESS, EXIT_FAILURE, std::atoll
# include <cstring>     // Pour les fonctions de chaînes de caractères
# include <ctime>       // Pour std::clock, CLOCKS_PER_SEC
# include <deque>       // Pour std::deque
# include <iomanip>     // Pour std::setprecision
# include <iostream>    // Pour std::cout, std::cerr
# include <stdexcept>   // Pour std::invalid_argument
# include <string>      // Pour std::string
# include <vector>      // Pour std::vector

template<typename T>
void jacobsthalSequence(T& container, int size) {
    bool finished = false;
    int last = 0;

    if (size == 0) 
        return;
        
    container.push_back(0);

    for (int temp = 0, n = 1, j = 0; !finished; n++) {
        j = (std::pow(2, n) - std::pow(-1, n)) / 3;
        
        temp = last;
        last = j;
        for (; j > temp; j--) {
            if (j < size) 
                container.push_back(j);
            else 
                finished = true;
        }
    }
}

// Function declarations
void startSorts(std::vector<int> vec, std::deque<int> deque);
std::vector<int> PmergeVec(std::vector<int>& tab);
std::deque<int> PmergeDeque(std::deque<int>& tab);
bool isNumOnly(char *arg);
std::vector<int> parseArgs(char **av);
void printTimes(int size, double vecTime, double dequeTime, double stdVecTime);

// Stream operator overloads
std::ostream& operator<<(std::ostream& os, const std::vector<int>& tab);
std::ostream& operator<<(std::ostream& os, const std::deque<int>& tab);

#endif