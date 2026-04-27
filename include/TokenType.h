//
// Created by XXX on 25.04.2026.
//
//
#pragma once
#include <string>

namespace StoneMath {

    enum class TokenType {
        Number,
        Plus,     // +
        Minus,    // -
        Multiply, // *
        Divide,   // /
        Power,    // ^
        LParen,   // (
        RParen,   // )
        Variable, // x, y
        Function, // sin, cos, sqrt
        EOF_Type, // end of string
        Error     // for incorect char
    };

    struct Token {
        TokenType type;
        std::string value;
    };

}