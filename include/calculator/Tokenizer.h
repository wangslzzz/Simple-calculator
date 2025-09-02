#ifndef Calculator_Tokenizer_h
#define Calculator_Tokenizer_h

#include <vector>
#include <string>

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen,
    End
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &v = "") : type(t), value(v) {}
};

class Tokenizer {
private:
    std::string input_;
    size_t pos_ = 0;
    void skipWhitespace();
    char peek();
    char consume();

public:
    std::vector<Token> tokenize();
    explicit Tokenizer(const std::string &input);
};

#endif