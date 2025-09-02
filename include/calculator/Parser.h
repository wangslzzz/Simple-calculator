#ifndef Calculator_Parser_h
#define Calculator_Parser_h

#include <vector>
#include <memory>
#include "calculator/Ast.h"
#include "calculator/Tokenizer.h"

class Parser {
private:
    std::vector<Token> tokens_;
    size_t current_ = 0;
    const Token& peek() const;
    const Token& consume();
    bool match(TokenType type) const;
    bool check(TokenType type) const;
    bool isAtEnd() const;

    std::unique_ptr<ExprNode> expression();
    std::unique_ptr<ExprNode> term();
    std::unique_ptr<ExprNode> factor();

public:
    std::unique_ptr<ExprNode> parse();
    explicit Parser(const std::vector<Token> tokens);
};

#endif