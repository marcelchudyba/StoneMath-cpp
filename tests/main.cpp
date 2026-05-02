#include <iostream>
#include <string>
#include <cmath>
#include "StoneMath.h"


void RunTest(int id, const std::string& equation, bool should_fail, double expected_result = 0.0) {
    std::cout << "Test #" << id << ": [" << equation << "] -> ";

    try {
        StoneMath::StoneMath engine;
        double result = engine.GetResult(equation,0);

        if (should_fail) {
            std::cout << "[PORAZKA] Program policzyl, a powinien rzucic bledem!" << "\n";
        } else {
            if (std::abs(result - expected_result) < 0.000001) {
                std::cout << "[SUKCES] Wynik: " << result << "\n";
            } else {
                std::cout << "[PORAZKA] Zly wynik! Oczekiwano " << expected_result << ", otrzymano " << result <<  "\n";
            }
        }
    }
    catch (const std::exception& e) {
        if (should_fail) {
            std::cout <<  "[SUKCES] Zlapano spodziewany blad: " << e.what() << "\n";
        } else {
            std::cout <<  "[PORAZKA] Niespodziewany crash: " << e.what() <<  "\n";
        }
    }
}

int main() {
    std::cout << "=== START TESTOW TURBO ===\n\n";

    // KATEGORIA 1: Podstawy i łączność lewostronna (to co naprawialiśmy >=)
    std::cout << "--- 1. PODSTAWY MATEMATYKI ---\n";
    RunTest(1, "2 + 2", false, 4.0);
    RunTest(2, "10 - 2 - 3", false, 5.0); // Jeśli wyjdzie 11, masz znowu błąd ze znakiem '>' zamiast '>='
    RunTest(3, "100 / 10 / 2", false, 5.0);
    RunTest(4, "2 + 3 * 4 - 5 / 2", false, 11.5);

    // KATEGORIA 2: Nawiasy i zagnieżdżenia
    std::cout << "\n--- 2. NAWIASY I ZAGNIEZDZENIA ---\n";
    RunTest(5, "(2 + 3) * 4", false, 20.0);
    RunTest(6, "10 / (5 - 3)", false, 5.0);
    RunTest(7, "(((((5 + 3) * 2) - 4) / 3) + 10) * 2", false, 28.0); // Totalny stres-test stosu

    // KATEGORIA 3: Przypadki brzegowe i spacje
    std::cout << "\n--- 3. PRZYPADKI BRZEGOWE ---\n";
    RunTest(8, "   2  +   2   ", false, 4.0); // Lexer musi ignorować spacje
    RunTest(9, "0.5 * 2", false, 1.0);
    RunTest(10, "0 / 5", false, 0.0);

    // KATEGORIA 4: Unarny minus (twardy orzech do zgryzienia)
    std::cout << "\n--- 4. LICZBY UJEMNE ---\n";
    RunTest(11, "-5 + 3", false, -2.0); // Minus na początku
    RunTest(12, "10 * (-2)", false, -20.0); // Minus w nawiasie
    RunTest(13, "-2.5 * -4", true, 10.0); // Jeśli obsłużyłeś "5 * -2" bez nawiasów, to to musi przejść
    RunTest(14, "-(-5)", false, 5.0); // Ekstremum: 0 - (0 - 5)

    // KATEGORIA 5: Błędy (To MUSI rzucić wyjątkiem!)
    std::cout << "\n--- 5. TESTY BLEDOW (MUSZA WYLAPAC CRASH) ---\n";
    // Błędy Lexera
    RunTest(15, "2 + a", true);
    RunTest(16, "12.34.56 + 1", true);
    // Błędy Parsera
    RunTest(17, "* 5 + 2", true);
    RunTest(18, "2 + + 2", true);
    RunTest(19, "5 * / 2", true);
    RunTest(20, "4 + ", true);
    // Błędy algorytmu nawiasów
    RunTest(21, "(2 + 3", true);
    RunTest(22, "2 + 3)", true);
    RunTest(23, "2 + ()", true);
    // Błędy Evaluatora
    RunTest(24, "5 / 0", true);
    RunTest(25, "5 / (2 - 2)", true);

    // KATEGORIA 6: Potęgowanie (Operator prawostronnie łączny!)
    // UWAGA: ^ działa inaczej niż + czy *. 2^3^2 to 2^(3^2) = 512, a nie (2^3)^2 = 64.
    std::cout << "\n--- 6. POTEGOWANIE ---\n";
    RunTest(26, "2 ^ 3", false, 8.0);
    RunTest(27, "5 * 2 ^ 2", false, 20.0); // Potęgowanie ma wyższy priorytet niż mnożenie!
    RunTest(28, "2 ^ 3 ^ 2", false, 512.0); // Test łączności prawostronnej (wymaga modyfikacji w Parserze)

    // KATEGORIA 7: Funkcje matematyczne (Jeden argument)
    std::cout << "\n--- 7. FUNKCJE MATEMATYCZNE ---\n";
    // Zakładamy, że sin() i cos() przyjmują u Ciebie radiany, bo tak domyślnie robi C++ w <cmath>
    RunTest(29, "sin(0)", false, 0.0);
    RunTest(30, "cos(0)", false, 1.0);
    RunTest(31, "sqrt(16)", false, 4.0);
    RunTest(32, "sqrt(9) + 2", false, 5.0);
    RunTest(33, "sqrt( 10 - 1 )", false, 3.0); // Wyrażenie wewnątrz funkcji
    RunTest(34, "2 * sin(0) + sqrt(4)", false, 2.0);

    // KATEGORIA 8: Złożone koszmary (Stress Test)
    std::cout << "\n--- 8. ZLOZONE KOSZMARY ---\n";
    RunTest(35, "sqrt(3 ^ 2 + 4 ^ 2)", false, 5.0); // Twierdzenie Pitagorasa: sqrt(9 + 16) = 5
    RunTest(36, "100 / (10 + 15 * (sqrt(4) - 2))", false, 10.0); // Zagnieżdżenia + funkcje

    // KATEGORIA 9: Błędy funkcji (Muszą rzucić wyjątkiem!)
    std::cout << "\n--- 9. NOWE TESTY BLEDOW ---\n";
    RunTest(37, "sin", true);       // Sama funkcja bez nawiasów i argumentu
    RunTest(38, "sin()", true);     // Pusta funkcja
    RunTest(39, "sqrt(-4)", true);  // Pierwiastek z liczby ujemnej (Evaluator musi wyłapać, że to NaN - Not a Number)
    RunTest(40, "2 ^ ", true);      // Ucięte potęgowanie
    std::cout << "\n=== KONIEC TESTOW ===\n";
    return 0;
}