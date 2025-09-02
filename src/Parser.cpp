#include "calculator/Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token> tokens) : tokens_(tokens) {}

const Token& Parser::peek() const {
    return tokens_[current_];
}

const Token& Parser::consume() {
   if(!isAtEnd()) current_++;
   return tokens_[current_ - 1];
}

bool Parser::match(TokenType type) const {
    return !isAtEnd() && peek().type == type;
}

bool Parser::check(TokenType type) const {
    return !isAtEnd() && peek().type == type;
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::End;
}

std::unique_ptr<ExprNode> Parser::expression() {
    auto expr = term();
    while(match(TokenType::Operator) && (peek().value == "+" || peek().value == "-")) {
        std::string op = consume().value;
        auto right = term();
        expr = std::make_unique<BinaryOpNode>(op[0], std::move(expr), std::move(right));
    }
    return expr;
}

std::unique_ptr<ExprNode> Parser::term() {
    auto expr = factor();
    while(match(TokenType::Operator) && (peek().value == "*" || peek().value == "/")) {
        std::string op = consume().value;
        auto right = factor();
        expr = std::make_unique<BinaryOpNode>(op[0], std::move(expr), std::move(right));
    }
    return expr;
}

std::unique_ptr<ExprNode> Parser::factor() {
    if(match(TokenType::Number)) {
        double value = std::stod(consume().value);
        return std::make_unique<NumberNode>(value);
    }

    if(match(TokenType::LeftParen)) {
        consume();
        auto expr = expression();
        if (!match(TokenType::RightParen)) {
            throw std::runtime_error("Expect ')' after expression.");
        }
        consume();
        return expr;
    }

    throw std::runtime_error("Unexpected token.");
}

std::unique_ptr<ExprNode> Parser::parse() {
    auto expr = expression();

    if (!isAtEnd()) {
        throw std::runtime_error("Unexpected token: " + peek().value);
    }

    return expr;
}