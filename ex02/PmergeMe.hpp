#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <climits>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <deque>
# include <iomanip>
# include <iostream> 
# include <stdexcept>
# include <string>
# include <vector>

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

void startSorts(std::vector<int> vec, std::deque<int> deque);
std::vector<int> PmergeVec(std::vector<int>& tab);
std::deque<int> PmergeDeque(std::deque<int>& tab);
bool isNumOnly(char *arg);
std::vector<int> parseArgs(char **av);
void printTimes(int size, double vecTime, double dequeTime, double stdVecTime);

std::ostream& operator<<(std::ostream& os, const std::vector<int>& tab);
std::ostream& operator<<(std::ostream& os, const std::deque<int>& tab);

#endif