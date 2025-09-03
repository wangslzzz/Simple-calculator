#ifndef Calculator_Ast_h
#define Calculator_Ast_h

#include <memory>
#include <limits>
#include <stdexcept>
#include <cmath>
#include "calculator/Environment.h"

class ExprNode {
public: 
    virtual ~ExprNode() = default;
    virtual double evaluate(Environment& env) const = 0;
};

class VariableNode : public ExprNode {
    std::string name_;
public:
    explicit VariableNode(const std::string& name) : name_(name) {}
    double evaluate(Environment& env) const override {
        return env.get(name_);
    }
};

class NumberNode : public ExprNode {
    double value_;
public:
    explicit NumberNode(const double value) : value_(value) {}
    double evaluate(Environment& env) const override {
        return value_;
    }
};

class AssignmentNode : public ExprNode{
    std::string name_;
    std::unique_ptr<ExprNode> value_;
public:
    explicit AssignmentNode(const std::string& name, std::unique_ptr<ExprNode> value) :
        name_(name), value_(std::move(value)) {}
    double evaluate(Environment& env) const override {
        double value = value_->evaluate(env);
        env.assign(name_, value);
        return value;
    }
};

class UnaryOpNode : public ExprNode {
    char op_;
    std::unique_ptr<ExprNode> operand_;
public:
    UnaryOpNode(char op, std::unique_ptr<ExprNode> operand) :
        op_(op), operand_(std::move(operand)) {}
    double evaluate(Environment& env) const override {
        double rval = operand_->evaluate(env);
        switch(op_) {
            case '+': return rval;
            case '-': return -rval;
            default: 
                throw std::runtime_error("Unknown unary operator: " + std::string(1, op_));
        }
    }
};

class BinaryOpNode : public ExprNode {
    char op_;
    std::unique_ptr<ExprNode> left_;
    std::unique_ptr<ExprNode> right_;
public:
    BinaryOpNode(char op, std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right) :
        op_(op), left_(std::move(left)), right_(std::move(right)) {}
    double evaluate(Environment& env) const override {
        double lval = left_->evaluate(env);
        double rval = right_->evaluate(env);
        switch(op_) {
            case '+': return lval + rval;
            case '-': return lval - rval;
            case '*': return lval * rval;
            case '/': 
                if(std::abs(rval) < std::numeric_limits<double>::epsilon())
                    throw std::runtime_error("Division by zero");
                return lval / rval;
            default : 
                throw std::runtime_error("Unknown binary operator: " + std::string(1, op_));
        }
    }
};

#endif