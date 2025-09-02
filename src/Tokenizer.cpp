#include "calculator/Tokenizer.h"
#include <cctype>
#include <stdexcept>

Tokenizer::Tokenizer(const std::string &input) : input_(input) {}

void Tokenizer::skipWhitespace() {
    while(pos_ < input_.size() && std::isspace(input_[pos_])) pos_++;
}

char Tokenizer::peek() {
    return (pos_ < input_.size()) ? input_[pos_] : '\0';
}

char Tokenizer::consume() {
    return (pos_ < input_.size()) ? input_[pos_++] : '\0';
}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    while(pos_ < input_.size()) {
        skipWhitespace();
        char current = peek();
        if(current == '\0') break;

        if(std::isdigit(current)) {
            std::string numStr;
            while(std::isdigit(peek()) || peek() == '.')
                numStr += consume();
            tokens.emplace_back(TokenType::Number, numStr);
        }else if(current == '+' || current == '-' || current == '*' || current == '/') {
            tokens.emplace_back(TokenType::Operator, std::string(1, consume()));
        }else if(current == '(') {
            consume();
            tokens.emplace_back(TokenType::LeftParen, "(");
        }else if(current == ')') {
            consume();
            tokens.emplace_back(TokenType::RightParen, ")");
        }else {
            throw std::runtime_error("Unknown character: '" + std::string(1, current) + "'");
        }
    }
    tokens.emplace_back(TokenType::End);
    return tokens;
}