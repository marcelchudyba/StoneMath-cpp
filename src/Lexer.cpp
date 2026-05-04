#include "Lexer.h"

#include <chrono>
#include <vector>

StoneMath::Lexer::Lexer(const std::string &text) {
    this->text = text;
}

std::vector<StoneMath::Token> StoneMath::Lexer::Tokenize() {
    std::vector<StoneMath::Token> tokenized_vector = std::vector<StoneMath::Token>();

    //this is a lambda
    auto InjectMultiplyIfNeeded = [&]() {
        if (!tokenized_vector.empty()) {

            TokenType last_token = tokenized_vector.back().type;

              if(last_token == TokenType::Number || last_token == TokenType::RParen) {
                 tokenized_vector.push_back(Token{TokenType::Multiply,"*"});
              }
        }
    };


    //main loop loops around the input expresion
    for(int i = 0; i < text.length(); i++) {
        currentChar = text[i];

        //skips the space
        if(currentChar == ' ') {
            continue;
        }
        //create a token based on the currentChar
        if(currentChar == '+') {
            tokenized_vector.push_back(Token{TokenType::Plus,"+"});
        }
        else if(currentChar == '-') {
            tokenized_vector.push_back(Token{TokenType::Minus,"-"});
        }
        else if(currentChar == '*') {
            tokenized_vector.push_back(Token{TokenType::Multiply,"*"});
        }
        else if(currentChar == '/') {
            tokenized_vector.push_back(Token{TokenType::Divide,"/"});
        }
        else if(currentChar == '^') {
            tokenized_vector.push_back(Token{TokenType::Power,"^"});
        }
        else if(currentChar == '(') {
            InjectMultiplyIfNeeded();
            tokenized_vector.push_back(Token{TokenType::LParen,"("});
        }
        else if(currentChar == ')') {
            tokenized_vector.push_back(Token{TokenType::RParen,")"});
        }
        else if(isdigit(currentChar)) {
            //reads numbers
            std::string accumulator = "";
            int number_of_dots = 0;
            while(i < text.length() && (isdigit(text[i]) || text[i] == '.')) {
                if(text[i] == '.') {
                    number_of_dots++;
                }
                accumulator += text[i];
                i++;
            }
            if(number_of_dots > 1) {
                throw std::invalid_argument("Lexer Error: Invalid Number Format");
            }
            i--;

            tokenized_vector.push_back(Token{TokenType::Number,accumulator});
        }
        else if(isalpha(currentChar)) {
            //this is for the functions or variables
            std::string accumulator = "";
            while(i < text.length() && (isalpha(text[i]))) {
                accumulator += text[i];
                i++;
            }
            i--;
            InjectMultiplyIfNeeded();
            if(accumulator == "sin" || accumulator == "cos" || accumulator == "tan" || accumulator == "tg" || accumulator == "ctg" || accumulator == "sqrt") {
                if((i + 1 < text.length() && text[i+1] != '(') || i + 1 == text.length()) {
                    throw std::invalid_argument("Lexer Error: After a function must be a parenthesis");
                }
                tokenized_vector.push_back(Token{TokenType::Function,accumulator});
            }
            else {
                tokenized_vector.push_back(Token{TokenType::Variable,accumulator});
            }
        }
        else {
            throw std::invalid_argument(std::string("Lexer Error: Undefined character: ") + currentChar);
        }
    }

    if(tokenized_vector.empty()) {
        throw std::invalid_argument("Lexer Error: Empty input");
    }

    tokenized_vector.push_back(Token{TokenType::EOF_Type,""});

    return tokenized_vector;

};