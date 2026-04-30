#include <iostream>

#include "Evaluator.h"
#include "../include/Parser.h"
#include "Lexer.h"
#include "Parser.h"
#include "StoneMath.h"

int main() {
    StoneMath::StoneMath math = StoneMath::StoneMath();

    std::string equation;

    while (true) {
        std::cout << "Wpisz rownanie (lub wpisz 'q' zeby wyjsc): ";
        std::getline(std::cin, equation);

        if (equation == "q") {
            break;
        }

        try {
            StoneMath::StoneMath engine;
            double result = engine.GetResult(equation,2);
            std::cout << "Wynik: " << result << std::endl;

        }
        catch (const std::exception& e) {
            std::cerr << "--- BLAD: " << e.what() << " ---\n";
        }

        std::cout << "-----------------------------------" << std::endl;
    }

    std::cout << "Zamkniecie programu" << std::endl;
}
