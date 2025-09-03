#include <stdexcept>
#include "calculator/Parser.h"

Parser::Parser(const std::vector<Token> tokens) : tokens_(tokens) {}

const Token& Parser::peek() const {
    return tokens_[current_];
}

const Token& Parser::consume() {
   if(isAtEnd())    
        throw std::runtime_error("Unexpected end of input");
   return tokens_[current_++];
}

bool Parser::match(TokenType type) const {
    return !isAtEnd() && peek().type == type;
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::End;
}

std::unique_ptr<ExprNode> Parser::assignment() {
    if(match(TokenType::Identifier) && 
        current_ + 1 < tokens_.size() && tokens_[current_ + 1].type == TokenType::Assign) {
        
        std::string varName = consume().value;
        consume();
        auto value = assignment();
        return std::make_unique<AssignmentNode>(varName, std::move(value));
    }
    return expression();
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
    if(match(TokenType::Operator) && (peek().value == "+" || peek().value == "-")) {
        std::string op = consume().value;
        auto operand = factor();
        return std::make_unique<UnaryOpNode>(op[0], std::move(operand));
    }

    if(match(TokenType::Number)) {
        double value = std::stod(consume().value);
        return std::make_unique<NumberNode>(value);
    }

    if(match(TokenType::Identifier)) {
        std::string varName = consume().value;
        return std::make_unique<VariableNode>(varName);
    }

    if(match(TokenType::LeftParen)) {
        consume();
        auto expr = assignment();
        if (!match(TokenType::RightParen)) {
            throw std::runtime_error("Expect ')' after expression.");
        }
        consume();
        return expr;
    }

    throw std::runtime_error("Unexpected token: " + peek().value + 
        " (expected number, identifier, or expression)");
}

std::unique_ptr<ExprNode> Parser::parse() {
    auto expr = assignment();

    if (!isAtEnd()) {
        throw std::runtime_error("Unexpected token: " + peek().value);
    }

    return expr;
}