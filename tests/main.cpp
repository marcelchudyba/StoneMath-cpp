#include <iostream>
#include <string>
#include <cmath>
#include "StoneMath.h"

void RunTest(int id, const std::string& equation, bool should_fail, double expected_result = 0.0) {
    std::cout << "Test #" << id << ": [" << equation << "] -> ";

    try {
        StoneMath::StoneMath engine = StoneMath::StoneMath(equation);

        double result = engine.Evaluate(0);

        if (should_fail) {
            std::cout << "[FAILURE] Program calculated, but should have thrown an error!" << "\n";
        } else {
            if (std::abs(result - expected_result) < 0.000001) {
                std::cout << "[SUCCESS] Result: " << result << "\n";
            } else {
                std::cout << "[FAILURE] Bad result! Expected " << expected_result << ", got " << result <<  "\n";
            }
        }
    }
    catch (const std::exception& e) {
        if (should_fail) {
            std::cout <<  "[SUCCESS] Caught expected error: " << e.what() << "\n";
        } else {
            std::cout <<  "[FAILURE] Unexpected crash: " << e.what() <<  "\n";
        }
    }
}

int main() {
    std::cout << "=== TURBO TESTS START ===\n\n";

    // CATEGORY 1: Basics and left-associativity (what we fixed >=)
    std::cout << "--- 1. BASIC MATH ---\n";
    RunTest(1, "2 + 2", false, 4.0);
    RunTest(2, "10 - 2 - 3", false, 5.0); // If it returns 11, you have the '>' instead of '>=' bug again
    RunTest(3, "100 / 10 / 2", false, 5.0);
    RunTest(4, "2 + 3 * 4 - 5 / 2", false, 11.5);

    // CATEGORY 2: Parentheses and nesting
    std::cout << "\n--- 2. PARENTHESES AND NESTING ---\n";
    RunTest(5, "(2 + 3) * 4", false, 20.0);
    RunTest(6, "10 / (5 - 3)", false, 5.0);
    RunTest(7, "(((((5 + 3) * 2) - 4) / 3) + 10) * 2", false, 28.0); // Total stack stress-test

    // CATEGORY 3: Edge cases and spaces
    std::cout << "\n--- 3. EDGE CASES ---\n";
    RunTest(8, "   2  +   2   ", false, 4.0); // Lexer must ignore spaces
    RunTest(9, "0.5 * 2", false, 1.0);
    RunTest(10, "0 / 5", false, 0.0);

    // CATEGORY 4: Unary minus (a tough nut to crack)
    std::cout << "\n--- 4. NEGATIVE NUMBERS ---\n";
    RunTest(11, "-5 + 3", false, -2.0); // Minus at the beginning
    RunTest(12, "10 * (-2)", false, -20.0); // Minus in parentheses
    RunTest(13, "-2.5 * -4", true, 10.0); // If you handled "5 * -2" without parentheses, this must pass
    RunTest(14, "-(-5)", false, 5.0); // Extreme: 0 - (0 - 5)

    // CATEGORY 5: Errors (MUST throw an exception!)
    std::cout << "\n--- 5. ERROR TESTS (MUST CATCH CRASH) ---\n";
    // Lexer Errors
    RunTest(15, "2 + a", true);
    RunTest(16, "12.34.56 + 1", true);
    // Parser Errors
    RunTest(17, "* 5 + 2", true);
    RunTest(18, "2 + + 2", true);
    RunTest(19, "5 * / 2", true);
    RunTest(20, "4 + ", true);
    // Parentheses algorithm errors
    RunTest(21, "(2 + 3", true);
    RunTest(22, "2 + 3)", true);
    RunTest(23, "2 + ()", true);
    // Evaluator Errors
    RunTest(24, "5 / 0", true);
    RunTest(25, "5 / (2 - 2)", true);

    // CATEGORY 6: Exponentiation (Right-associative operator!)
    // NOTE: ^ works differently than + or *. 2^3^2 is 2^(3^2) = 512, not (2^3)^2 = 64.
    std::cout << "\n--- 6. EXPONENTIATION ---\n";
    RunTest(26, "2 ^ 3", false, 8.0);
    RunTest(27, "5 * 2 ^ 2", false, 20.0); // Exponentiation has higher precedence than multiplication!
    RunTest(28, "2 ^ 3 ^ 2", false, 512.0); // Right-associativity test (requires modification in Parser)

    // CATEGORY 7: Math functions (Single argument)
    std::cout << "\n--- 7. MATH FUNCTIONS ---\n";
    // Assuming sin() and cos() take radians, as C++ defaults to in <cmath>
    RunTest(29, "sin(0)", false, 0.0);
    RunTest(30, "cos(0)", false, 1.0);
    RunTest(31, "sqrt(16)", false, 4.0);
    RunTest(32, "sqrt(9) + 2", false, 5.0);
    RunTest(33, "sqrt( 10 - 1 )", false, 3.0); // Expression inside function
    RunTest(34, "2 * sin(0) + sqrt(4)", false, 2.0);

    // CATEGORY 8: Complex nightmares (Stress Test)
    std::cout << "\n--- 8. COMPLEX NIGHTMARES ---\n";
    RunTest(35, "sqrt(3 ^ 2 + 4 ^ 2)", false, 5.0); // Pythagorean theorem: sqrt(9 + 16) = 5
    RunTest(36, "100 / (10 + 15 * (sqrt(4) - 2))", false, 10.0); // Nesting + functions

    // CATEGORY 9: Function errors (Must throw an exception!)
    std::cout << "\n--- 9. NEW ERROR TESTS ---\n";
    RunTest(37, "sin", true);       // Function itself without parentheses and argument
    RunTest(38, "sin()", true);     // Empty function
    RunTest(39, "sqrt(-4)", true);  // Square root of a negative number (Evaluator must catch that it's NaN - Not a Number)
    RunTest(40, "2 ^ ", true);      // Truncated exponentiation

    RunTest(41, "2x + sin ", true);

    RunTest(42, "10sin", true);
    RunTest(43, "(2x + 2)^ + 2", true);
    RunTest(44, "10(sin)", true);

    std::cout << "\n=== END OF TESTS ===\n";
    return 0;
}