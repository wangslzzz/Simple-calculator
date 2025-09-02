#include <iostream>
#include <vector>
#include <cassert>
#include "calculator/Tokenizer.h"
#include "calculator/Parser.h"

std::string tokenTypeToString(TokenType type) {
    switch(type) {
        case TokenType::Number: return "Number";
        case TokenType::Operator: return "Operator";
        case TokenType::LeftParen: return "LeftParen";
        case TokenType::RightParen: return "RightParen";
        case TokenType::End: return "End";
        default: return "Unknown";
    }
}

bool testTokenizer() {
    bool AllPassed = true;

    std::cout << "\n===Testing Tokenizer===\n";

    std::vector<std::string> testCases = {
        "(1 + 23.5) * 4 - 5",
    };

    for(const auto& input : testCases) {
        try {
            Tokenizer t(input);
            auto tokens = t.tokenize();
            std::cout << "[PASS] Input: " << input << std::endl;
            for(const auto& token : tokens)
                std::cout << "Token: " << tokenTypeToString(token.type) << ", Value: " << token.value << std::endl;
        } catch(const std::exception& e) {
            std::cerr << "[FAIL] " << input << " -> Error: " << e.what() << std::endl; 
            AllPassed = false;
        }
        std::cout << std::endl;
    }

    std::vector<std::string> errorCases = {
        "1 & 2",
    };

    for(const auto& errorInput : errorCases) {
        try {
            Tokenizer t(errorInput);
            auto tokens = t.tokenize();
            std::cerr << "[FAIL] Input: " << errorInput << " should have thrown but got\n";
            for(const auto& token : tokens)
                std::cout << "Token: " << tokenTypeToString(token.type) << ", Value: " << token.value << std::endl;
            AllPassed = false;
        } catch(const std::exception& e) {
            std::cout << "[PASS] " << errorInput << " correctly threw: " << e.what() << std::endl; 
        }
        std::cout << std::endl;
    }
    return AllPassed;
}

bool testParser() {
    bool AllPassed = true;

    std::cout << "\n=== Testing Parser ===\n";
    
    std::vector<std::pair<std::string, double>> testCases = {
        {"1 + 2 * 3", 7},
        {"(1 + 2) * 3", 9},
        {"10 / 2 - 1", 4},
        {"2 * (3 + 4) / 2", 7},
        {"(1 + 2) * 3 - 4 / 2", 7},
        {"3.14 * 2", 6.28},
        {"((1 + ((1 + 1)) * (3 - 1)))", 5}
    };

    for(const auto& input : testCases) {
        try {
            Tokenizer t(input.first);
            Parser p(t.tokenize());
            auto ast = p.parse();
            double result = ast->evaluate();
            assert(result == input.second);
            std::cout << "[PASS] " << input.first << " = " << result << std::endl;
        } catch(const std::exception& e) {
            std::cerr << "[FAIL] " << input.first << " -> Error: " << e.what() << std::endl; 
            AllPassed = false;
        }
    }

    std::vector<std::string> errorCases = {
        "1 + ",
        "* 5",
        "1 + 2)",
        "1 / 0",
        "1 & 2",
    };

    for (const auto& errorInput : errorCases) {
        try {
            Tokenizer t(errorInput);
            Parser p(t.tokenize());
            auto ast = p.parse();
            double result = ast->evaluate();
            std::cerr << "[FAIL] " << errorInput << " should have thrown but got: " << result << std::endl;
            AllPassed = false;
        } catch (const std::exception& e) {
            std::cout << "[PASS] " << errorInput << " correctly threw: " << e.what() << std::endl;
        }
    }
    return AllPassed;
}

int main() {
    bool Pass1 = testTokenizer();
    bool Pass2 = testParser();
    std::cout << "\n\n";
    if(Pass1 == false) std::cout << "Tokenizer have error!\n";
    if(Pass2 == false) std::cout << "Parser have error!\n";
    if(Pass1 && Pass2) std::cout << "All Passed!\n";
    return 0;
}