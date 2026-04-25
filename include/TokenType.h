//
// Created by XXX on 25.04.2026.
//
//
#pragma once
#include <string>

namespace StoneMath {

    enum class TokenType {
        Number,
        Plus,
        Minus,
        Multiply,
        Divide,
        LParen,   // (
        RParen,   // )
        Variable, // x, y
        EOF_Type  // Koniec stringa
    };

    struct Token {
        TokenType type;
        std::string value;
    };

}