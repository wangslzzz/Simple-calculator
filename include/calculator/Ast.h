#ifndef Calculator_Ast_h
#define Calculator_Ast_h

#include <memory>
#include <limits>
#include <stdexcept>
#include <cmath>

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
            case '/': 
                if(std::abs(rval) < std::numeric_limits<double>::epsilon())
                    throw std::runtime_error("Division by zero");
                return lval / rval;
            default : 
                throw std::runtime_error("Unknown operator: " + std::string(1, op_));
        }
    }
};

#endif