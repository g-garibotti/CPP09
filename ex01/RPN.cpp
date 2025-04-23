#include "RPN.hpp"
#include <iostream>
#include <sstream>

RPN::RPN() {}
RPN::RPN(const RPN &src) {
    *this = src;
}
RPN &RPN::operator=(const RPN &rhs) {
    if (this != &rhs) {
        this->_numbers = rhs._numbers;
    }
    return *this;
}
RPN::~RPN() {}

bool RPN::isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigit(char c) const {
    return (c >= '0' && c <= '9');
}

void RPN::performOperation(char op) {
    if (_numbers.size() < 2)
        throw std::runtime_error("Error: Not enough operands for operation");
    
    int b = _numbers.top();
    _numbers.pop();
    int a = _numbers.top();
    _numbers.pop();
    
    switch (op) {
        case '+':
            _numbers.push(a + b);
            break;
        case '-':
            _numbers.push(a - b);
            break;
        case '*':
            _numbers.push(a * b);
            break;
        case '/':
            if (b == 0)
                throw std::runtime_error("Error: Division by zero");
            _numbers.push(a / b);
            break;
        default:
            throw std::runtime_error("Error: Unknown operator");
    }
}

int RPN::calculate(const std::string &expression) {
    std::istringstream iss(expression);
    std::string token;
    
    while (!_numbers.empty())
        _numbers.pop();
    
    while (iss >> token) {
        if (token.length() == 1) {
            char c = token[0];
            
            if (isDigit(c)) {
                _numbers.push(c - '0');
            } else if (isOperator(c)) {
                performOperation(c);
            } else if (c != ' ') {
                throw std::runtime_error("Error: Invalid character in expression");
            }
        } else {
            bool validToken = true;
            for (size_t i = 0; i < token.length(); i++) {
                if (!isDigit(token[i])) {
                    validToken = false;
                    break;
                }
            }
            
            if (validToken) {
                int value = 0;
                std::istringstream(token) >> value;
                
                if (value >= 10)
                    throw std::runtime_error("Error: Input numbers must be less than 10");
                    
                _numbers.push(value);
            } else {
                throw std::runtime_error("Error: Invalid token in expression");
            }
        }
    }
    
    if (_numbers.size() != 1)
        throw std::runtime_error("Error: Invalid expression");
    
    return _numbers.top();
}
