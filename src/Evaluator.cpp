#include "Evaluator.h"

#include <regex>
StoneMath::Evaluator::Evaluator(std::vector<Token>& tokens) {
    this->rpn_tokens = tokens;
}
double StoneMath::Evaluator::Operation_Type(TokenType type, const double& left,const double& right) {
    switch (type) {
        case TokenType::Multiply:
            return left*right;
        case TokenType::Divide:
         if(right == 0) {
             throw std::runtime_error("Mathematical Error: Dividing by zero!");
         }
                        return left/right;
        case TokenType::Minus:
            return left-right;
        case TokenType::Plus:
            return left+right;
        case TokenType::Power:
            return pow(left,right);
        default:
            break;
    }
}
double StoneMath::Evaluator::Function_Type(std::string function_name,  const double& top) {
    if (function_name == "sin") {
        return std::sin(top);
    }
    if (function_name == "cos") {
        return std::cos(top);
    }
    if (function_name == "tan" || function_name == "tg") {
        return std::tan(top);
    }
    if(function_name == "ctg") {
        return 1/std::tan(top);
    }
    if (function_name == "sqrt") {
        return std::sqrt(top);
    }

    return 0.0;
}

double StoneMath::Evaluator::Evaluate(const double& x) {
    for(int i = 0; i < this->rpn_tokens.size(); i++) {
        if(rpn_tokens[i].type == TokenType::Variable) {
            if(rpn_tokens[i].value == "x") {
                numbers_stack.push(x);
            }
            else {
                throw std::runtime_error("Mathematical Error: Variable does not exist!");
            }
        }
        else if(rpn_tokens[i].type == TokenType::Function) {
            double top = numbers_stack.top();
            numbers_stack.pop();

            double result = Function_Type(rpn_tokens[i].value, top);

            numbers_stack.push(result);

        }
        else if(rpn_tokens[i].type == TokenType::Number) {
            double current_number = std::stod(rpn_tokens[i].value);
            numbers_stack.push(current_number);
        }
        else {
            double right = numbers_stack.top();
            numbers_stack.pop();
            double left = numbers_stack.top();
            numbers_stack.pop();

            TokenType current_operator = rpn_tokens[i].type;

            double output = Operation_Type(current_operator, left, right);

            numbers_stack.push(output);
        }
    }

    return numbers_stack.top();


}


