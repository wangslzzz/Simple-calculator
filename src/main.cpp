#include <iostream>
#include <string>
#include "calculator/Tokenizer.h"
#include "calculator/Parser.h"

int main() {
    std::cout << "Simple calculator (type 'quit' to exit)" << std::endl;

    while(true) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        if(input == "quit") break;
        if(input.empty()) continue;

        try {
            Tokenizer t(input);
            Parser p(t.tokenize());
            auto ast = p.parse();
            double result = ast->evaluate();
            std::cout << "= " << result << std::endl;
        } catch(std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}