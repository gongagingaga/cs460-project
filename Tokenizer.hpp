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
    void printTokens(std::vector<Token> tokens);
    std::vector<Token> tokenize(std::string input);
private:

};
