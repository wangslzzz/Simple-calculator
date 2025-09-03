#include <cctype>
#include <stdexcept>
#include "calculator/Tokenizer.h"

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
            while(std::isalnum(peek()) || peek() == '.') {
                if(std::isalpha(peek())) 
                    throw std::runtime_error("Variable cannot start with a number");
                numStr += consume();
            }
            tokens.emplace_back(TokenType::Number, numStr);
        }
        else if(isalpha(current) || current == '_') {
            std::string iden;
            while(std::isalnum(peek()) || peek() == '_') 
                iden += consume();
            tokens.emplace_back(TokenType::Identifier, iden);
        }
        else if(current == '=') {
            consume();
            tokens.emplace_back(TokenType::Assign, "=");
        }
        else if(current == '+' || current == '-' || current == '*' || current == '/') {
            tokens.emplace_back(TokenType::Operator, std::string(1, consume()));
        }
        else if(current == '(') {
            consume();
            tokens.emplace_back(TokenType::LeftParen, "(");
        }
        else if(current == ')') {
            consume();
            tokens.emplace_back(TokenType::RightParen, ")");
        }
        else {
            throw std::runtime_error("Unknown character: " + std::string(1, current));
        }
    }
    tokens.emplace_back(TokenType::End);
    return tokens;
}