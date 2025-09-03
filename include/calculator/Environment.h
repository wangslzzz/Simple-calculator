#ifndef Calculator_Environment_h
#define Calculator_Environment_h

#include <string>
#include <stdexcept>
#include <unordered_map>

class Environment {
private:
    std::unordered_map<std::string, double> variables_;

public:
    double get(const std::string& name) const {
        auto it = variables_.find(name);
        if(it != variables_.end()) return it->second;
        throw std::runtime_error("Undefined variable: " + name);
    }

    void assign(const std::string& name, double value) {
        variables_[name] = value;
    }
};

#endif