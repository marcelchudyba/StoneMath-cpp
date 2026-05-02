#pragma once
#include <vector>

#include "TokenType.h"

namespace StoneMath {
    class Lexer {
        std::string text;
        int position;
        char currentChar;


    public:
        Lexer(const std::string& text);
        std::vector<Token> Tokenize();

    };
}

