#include "../include/Parser.h"
#include <iostream>
#include <vector> // <-- TEGO BRAKOWAŁO

#include "StoneMath.h"


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

    for (auto token: input_tokens) {
        if(token.type == TokenType::Number || token.type == TokenType::Variable) {
            output_queue.push_back(token);
        }
        else if(token.type == TokenType::EOF_Type) {
            while(!operator_stack.empty()) {
                Token top_stack = operator_stack.top();
                operator_stack.pop();
                output_queue.push_back(top_stack);
            }
        }
        else if(token.type == TokenType::RParen) {
                while(operator_stack.top().type != TokenType::LParen) {
                    Token top_stack = operator_stack.top();
                    operator_stack.pop();
                    output_queue.push_back(top_stack);
                }
                operator_stack.pop();

                if(!operator_stack.empty() && operator_stack.top().type == TokenType::Function) {
                    Token top_stack = operator_stack.top();
                    operator_stack.pop();
                    output_queue.push_back(top_stack);
                }
            }
        else if(token.type == TokenType::LParen || token.type == TokenType::Function) {
            operator_stack.push(token);
        }
        else {
            if(!operator_stack.empty() && GetPrecedence(operator_stack.top().type) > GetPrecedence(token.type)) {
                Token top = operator_stack.top();
                operator_stack.pop();
                output_queue.push_back(top);
                operator_stack.push(token);
            }
            else{
            operator_stack.push(token);
            }
        }
    }
    return output_queue;
}

