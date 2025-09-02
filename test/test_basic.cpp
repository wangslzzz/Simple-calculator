#include <iostream>
#include <vector>
#include "calculator/Tokenizer.h"
#include "calculator/Parser.h"

void testTokenizer() {
    std::cout << "\n ===Testing Tokenizer=== " << std::endl;
    std::string input = "(1 + 23.5) * 4 - 5";
    Tokenizer t(input);
    auto tokens = t.tokenize();

    for(const auto& token : tokens) 
        std::cout << "Token: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
}

void testParser() {
    std::cout << "\n === Testing Parser ===" << std::endl;
    std::string input = "(1 + 2) * 3 - 4 / 2";
    Tokenizer t(input);
    auto tokens = t.tokenize();
    Parser p(tokens);
    
    try {
        auto ast = p.parse();
        double result = ast->evaluate();
        std::cout << "Expression: " << input << std::endl;
        std::cout << "Result: " << result << std::endl;

        std::vector<std::string> testExpressions = {
            "1 + 2 * 3",
            "(1 + 2) * 3",
            "10 / 2 - 1",
            "2 * (3 + 4) / 2"
        };

        for(const auto& expr : testExpressions) {
            Tokenizer t(expr);
            Parser p(t.tokenize());
            auto ast = p.parse();
            std::cout << expr << " = " << ast->evaluate() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Parser error" << e.what() << std::endl; 
    }
}

int main() {
    testTokenizer();
    testParser();
    return 0;
}