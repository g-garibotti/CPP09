#include "PmergeMe.hpp"



std::vector<int> PmergeVec(std::vector<int>& tab) {
    size_t pairs = 0;
    
    std::vector<int> result;
    std::vector<int> big;
    std::vector<int> small;
    std::vector<int>::iterator pos;

    // hello bastien
    
    for (std::vector<int>::iterator it = tab.begin(); it != tab.end(); ++it) {
        int n1 = *it;
        ++pairs;
        ++it;
        
        if (it != tab.end()) {
            int n2 = *it;
            big.push_back(std::max(n1, n2));
            small.push_back(std::min(n1, n2));
        } else {
            small.push_back(n1);
            break;
        }
    }
    
    if (pairs == 1) {
        result.push_back(small[0]);
        if (!big.empty())
            result.push_back(big[0]);
        return result;
    }
    
    result = PmergeVec(big);
    
    std::vector<int> jacobsthal;
    jacobsthalSequence<std::vector<int> >(jacobsthal, small.size());
    
    for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it) {
        int num = small.at(*it);
        pos = std::lower_bound(result.begin(), result.end(), num);
        result.insert(pos, num);
    }
    
    return result;
}



std::deque<int> PmergeDeque(std::deque<int>& tab) {
    size_t pairs = 0;
    
    std::deque<int> result;
    std::deque<int> big;
    std::deque<int> small;
    std::deque<int>::iterator pos;
    
    for (std::deque<int>::iterator it = tab.begin(); it != tab.end(); ++it) {
        int n1 = *it;
        ++pairs;
        ++it;
        
        if (it != tab.end()) {
            int n2 = *it;
            big.push_back(std::max(n1, n2));
            small.push_back(std::min(n1, n2));
        } else {
            small.push_back(n1);
            break;
        }
    }
    
    if (pairs == 1) {
        result.push_back(small.front());
        if (!big.empty())
            result.push_back(big.front());
        return result;
    }
    
    result = PmergeDeque(big);
    
    std::deque<int> jacobsthal;
    jacobsthalSequence<std::deque<int> >(jacobsthal, small.size());
    
    for (std::deque<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it) {
        int num = small.at(*it);
        pos = std::lower_bound(result.begin(), result.end(), num);
        result.insert(pos, num);
    }
    
    return result;
}