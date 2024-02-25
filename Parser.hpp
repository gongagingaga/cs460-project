//
// Created by candy on 2/24/2024.
//

#ifndef TOKENIZER_PARSER_HPP
#define TOKENIZER_PARSER_HPP
#include "Tokenizer.hpp"
#include <vector>

class Parser {
public:
    Parser(const std::string fileName): tokenizer{Tokenizer(fileName)} {};
    void parseFile();
    void parseToken(Token token);
    std::vector<Token> getTokens() {return tokens;};
    void print();

private:
    std::vector<Token> tokens;
    Tokenizer tokenizer;
};


#endif //TOKENIZER_PARSER_HPP
