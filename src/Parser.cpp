#include "../include/Parser.h"

#include <stdexcept>
#include <vector>

StoneMath::Parser::Parser(const std::vector<Token>& tokens) : input_tokens(tokens) {};

int StoneMath::Parser::GetPrecedence(TokenType type) {
    if(type == TokenType::Plus || type == TokenType::Minus) {
        return 1;
    }
    if(type == TokenType::Divide || type == TokenType::Multiply) {
        return 2;
    }
    if(type == TokenType::Power) {
        return 3;
    }
    return 0;
}


std::vector<StoneMath::Token> StoneMath::Parser::Parse() {

    int i = 0;
    Token previous_token = input_tokens[i];

    int lParen_i = 0;
    int rParen_i = 0;

    bool open_parenthesis = false;

    for (auto token: input_tokens) {
        if(token.type == TokenType::Number || token.type == TokenType::Variable) {
            output_queue.push_back(token);
        }
        else if(token.type == TokenType::EOF_Type) {
            //for the end of file we are throwing everything from the stack to output_queue

            while(!operator_stack.empty()) {
                Token top_stack = operator_stack.top();
                operator_stack.pop();
                output_queue.push_back(top_stack);
            }
        }
        else if(token.type == TokenType::LParen) {

            lParen_i++;

            // throw std::invalid_argument("Parser Error: Previous parenthesis needs to be closed first");

            //with no hesitation we always push LParen and Function type to the stack
            operator_stack.push(token);
        }
        else if(token.type == TokenType::Function){
            operator_stack.push(token);
        }
        else if(token.type == TokenType::RParen) {
                rParen_i++;


                if(!operator_stack.empty() && operator_stack.top().type == TokenType::LParen && previous_token.type != TokenType::Variable && previous_token.type != TokenType::Function && previous_token.type != TokenType::Number) {
                    throw std::invalid_argument("Parser Error: Empty parenthesis");
                }

                if(lParen_i < rParen_i) {
                    throw std::invalid_argument("Parser Error: Missing left parenthesis");

                }

                //for right Paren we need to look on the stack and throw everything till the L_Paren
                while(!operator_stack.empty() && operator_stack.top().type != TokenType::LParen) {
                    Token top_stack = operator_stack.top();
                    operator_stack.pop();
                    output_queue.push_back(top_stack);
                }
                if(!operator_stack.empty()) {
                    operator_stack.pop();
                }
                //we are checking if its a function before parens if it its we throw it to the queue
                if(!operator_stack.empty() && operator_stack.top().type == TokenType::Function) {
                    Token top_stack = operator_stack.top();
                    operator_stack.pop();
                    output_queue.push_back(top_stack);
                }
            }

        else {


            if(i == 0 && token.type != TokenType::Minus) {
            //this is for the negative numbers in the start of eqaution
                throw std::invalid_argument("Parser Error: Eqauation cannot start with this operator.");
            }

            bool prev_condition = (previous_token.type == TokenType::Minus || previous_token.type == TokenType::Plus || previous_token.type == TokenType::Divide || previous_token.type == TokenType::Multiply);

            if(i == 0) {
                output_queue.push_back(Token{TokenType::Number, "0"});
            }
            if(i > 0  && prev_condition) {
              throw std::invalid_argument("Parser Error: Operators cannot be next to each other");

            }

            //this is for a negative number we are only accepting those in betweeen brackets
            if(!operator_stack.empty() && previous_token.type == TokenType::LParen) {
                if(input_tokens[i + 1].type == TokenType::RParen) {
                    throw std::invalid_argument("Parser Error: You cannot write only operator in the brackets");
                }

                if(token.type == TokenType::Minus ) {
                    output_queue.push_back(Token{TokenType::Number, "0"});
                }
            }


            //there are going operators

            int current_prec = GetPrecedence(token.type);

            while (!operator_stack.empty() && operator_stack.top().type != TokenType::LParen) {

                int stack_prec = GetPrecedence(operator_stack.top().type);
                bool should_pop = false;

                if (current_prec == 3) {
                    // for power >
                    should_pop = (stack_prec > current_prec);
                } else {
                    // for other operators (+, -, *, /) we use >=
                    should_pop = (stack_prec >= current_prec);
                }

                if (should_pop) {
                    Token top = operator_stack.top();
                    operator_stack.pop();
                    output_queue.push_back(top);
                } else {
                    break;
                }
            }
            operator_stack.push(token);

            if(input_tokens[i + 1].type == TokenType::RParen || input_tokens[i + 1].type == TokenType::EOF_Type) {
                throw std::invalid_argument("Parser Error: Equation cannot end with Operator");
            }
        }
        previous_token = token;
        i++;
    }
    if(lParen_i != rParen_i) {
        throw std::invalid_argument("Parser Error: Open parenthesis not allowed here");
    }

    return output_queue;
}

