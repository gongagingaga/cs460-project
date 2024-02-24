#ifndef TOKENIZERPROJECT_TOKENIZER_HPP
#define TOKENIZERPROJECT_TOKENIZER_HPP

#include <cctype>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include "Token.hpp"


class Tokenizer {
public:
    Tokenizer() = default;
    void printTokens();
    std::vector<Token> tokenize(std::string input);
private:
    std::vector<Token> tokens;
};


#endif //TOKENIZERPROJECT_TOKENIZER_HPP
