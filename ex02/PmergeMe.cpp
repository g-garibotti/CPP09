#include "PmergeMe.hpp"

/* 
 * Ford-Johnson merge-insertion sort implementation for std::vector
 */
std::vector<int> PmergeVec(std::vector<int>& tab) {
    size_t pairs = 0;
    
    std::vector<int> result;
    std::vector<int> big;
    std::vector<int> small;
    std::vector<int>::iterator pos;
    
    // Create pairs and separate into 'big' and 'small' elements
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
    
    // Base case: only one pair
    if (pairs == 1) {
        result.push_back(small[0]);
        if (!big.empty())
            result.push_back(big[0]);
        return result;
    }
    
    // Recursive call on the 'big' elements
    result = PmergeVec(big);
    
    // Insert 'small' elements using binary search and Jacobsthal sequence
    std::vector<int> jacobsthal;
    jacobsthalSequence<std::vector<int> >(jacobsthal, small.size());
    
    for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it) {
        int num = small.at(*it);
        pos = std::lower_bound(result.begin(), result.end(), num);
        result.insert(pos, num);
    }
    
    return result;
}

/*
 * Ford-Johnson merge-insertion sort implementation for std::deque
 */
std::deque<int> PmergeDeque(std::deque<int>& tab) {
    size_t pairs = 0;
    
    std::deque<int> result;
    std::deque<int> big;
    std::deque<int> small;
    std::deque<int>::iterator pos;
    
    // Create pairs and separate into 'big' and 'small' elements
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
    
    // Base case: only one pair
    if (pairs == 1) {
        result.push_back(small.front());
        if (!big.empty())
            result.push_back(big.front());
        return result;
    }
    
    // Recursive call on the 'big' elements
    result = PmergeDeque(big);
    
    // Insert 'small' elements using binary search and Jacobsthal sequence
    std::deque<int> jacobsthal;
    jacobsthalSequence<std::deque<int> >(jacobsthal, small.size());
    
    for (std::deque<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it) {
        int num = small.at(*it);
        pos = std::lower_bound(result.begin(), result.end(), num);
        result.insert(pos, num);
    }
    
    return result;
}