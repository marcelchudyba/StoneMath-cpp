#include "StoneMath.h"
#include <iostream>

StoneMath::StoneMath::StoneMath(const std::string& expr) {
    this->expr = expr;
    Lexer lexer = Lexer(this->expr);

    tokenized_expr = lexer.Tokenize();

    Parser parser = Parser(tokenized_expr);

    parsed_expr = parser.Parse();
};

double StoneMath::StoneMath::Evaluate(const double &x) {
    Evaluator evaluator = Evaluator(parsed_expr);
    return evaluator.Evaluate(x);
}

std::vector<StoneMath::Token> StoneMath::StoneMath::GetTokenizedExpr() {
    return this->tokenized_expr;
}

std::vector<StoneMath::Token> StoneMath::StoneMath::GetParsedExpr() {
    return this->parsed_expr;
}


