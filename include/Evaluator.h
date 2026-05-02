#pragma once
#include <stack>
#include <vector>

#include "TokenType.h"

namespace StoneMath {
    class Evaluator {
        std::vector<Token> rpn_tokens;
        std::stack<double> numbers_stack;
        double output_value;
        double Function_Type(std::string function_name,  const double& top);
        double Operation_Type(TokenType type, const double& left,const double& right);
    public:
        Evaluator(std::vector<Token>& tokens);

        double Evaluate(const double& x);
    };
}
