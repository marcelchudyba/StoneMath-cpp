#include <iostream>
#include "../include/Parser.h"
#include "Lexer.h"
#include "Parser.h"
#include "StoneMath.h"

int main() {
    StoneMath::Lexer lexer = StoneMath::Lexer("sin ( x ^ 2 ) * ( 2 + x ) - 5 / x");

    std::vector<StoneMath::Token> tokenized = lexer.Tokenize();

    std::cout << "tokenized: " << std::endl;

    for (auto value: tokenized) {
        std::cout << value.value << " ";
    }
    std::cout << std::endl;

    std::cout << "onp: " << std::endl;

    StoneMath::Parser parser = StoneMath::Parser(tokenized);

    std::vector<StoneMath::Token> onp_notation = parser.Parse();
    for (auto value: onp_notation) {
        std::cout << value.value << " ";
    }
}
