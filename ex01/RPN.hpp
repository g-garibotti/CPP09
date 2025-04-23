#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>
# include <stdexcept>

class RPN {
    private:
        std::stack<int> _numbers;
        
        void performOperation(char op);
        bool isOperator(char c) const;
        bool isDigit(char c) const;

    public:
        RPN();
        RPN(const RPN &src);
        RPN &operator=(const RPN &rhs);
        ~RPN();

        int calculate(const std::string &expression);
};

#endif