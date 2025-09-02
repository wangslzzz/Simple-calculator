#ifndef Calculator_Ast_h
#define Calculator_Ast_h

#include <memory>

class ExprNode {
public: 
    virtual ~ExprNode() = default;
    virtual double evaluate() const = 0;
};

class NumberNode : public ExprNode {
    double value_;
public:
    explicit NumberNode(double value) : value_(value) {}
    double evaluate() const override {return value_;}
};

class BinaryOpNode : public ExprNode {
    char op_;
    std::unique_ptr<ExprNode> left_;
    std::unique_ptr<ExprNode> right_;
public:
    BinaryOpNode(char op, std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right) :
        op_(op), left_(std::move(left)), right_(std::move(right)) {}
    double evaluate() const override {
        double lval = left_->evaluate();
        double rval = right_->evaluate();
        switch(op_) {
            case '+': return lval + rval;
            case '-': return lval - rval;
            case '*': return lval * rval;
            case '/': return lval / rval; // todo : division by zero check
            default : return 0.0; // unknown type
        }
    }
};

#endif