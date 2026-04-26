//
// Created by XXX on 25.04.2026.
//
#include "Lexer.h"

#include <vector>


StoneMath::Lexer::Lexer(const std::string &text) {
    this->text = text;
}


std::vector<StoneMath::Token> StoneMath::Lexer::Tokenize() {

    std::vector<StoneMath::Token> tokenized_vector = std::vector<StoneMath::Token>();

    for(int i = 0; i < text.length(); i++) {
        currentChar = text[i];

        if(currentChar == ' ') {
            continue;
        }

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
        else if(currentChar == '=') {
            tokenized_vector.push_back(Token{TokenType::Equals,"="});
        }
        else if(currentChar == '(') {
            tokenized_vector.push_back(Token{TokenType::LParen,"("});
        }
        else if(currentChar == ')') {
            tokenized_vector.push_back(Token{TokenType::RParen,")"});
        }
        else if(isdigit(currentChar)) {
            std::string accumulator = "";

            while(i < text.length() && (isdigit(text[i]) || text[i] == '.')) {
                accumulator += text[i];
                i++;
            }
            i--;

            tokenized_vector.push_back(Token{TokenType::Number,accumulator});
        }
        else if(isalpha(currentChar)) {
            std::string accumulator = "";
            while(i < text.length() && (isalpha(text[i]))) {
                accumulator += text[i];
                i++;
            }
            i--;

            if(accumulator == "sin" || accumulator == "cos" || accumulator == "tan" || accumulator == "sqrt") {
                tokenized_vector.push_back(Token{TokenType::Function,accumulator});
            }
            else {
                tokenized_vector.push_back(Token{TokenType::Variable,accumulator});
            }
        }




    }
    tokenized_vector.push_back(Token{TokenType::EOF_Type,""});


    return tokenized_vector;

}




