//
// Created by candy on 2/24/2024.
//

#ifndef TOKENIZER_TOKENIZER_HPP
#define TOKENIZER_TOKENIZER_HPP
#include "Token.hpp"
#include <fstream>

class Tokenizer {
public:
    explicit Tokenizer(const std::string &inputFile);
    void uncommentFile();

    Token getToken();
    Token getStringToken(char terminator);

private:
    std::string inputFileName;
    std::string uncommentedFile;
    int currChar;

};


#endif //TOKENIZER_TOKENIZER_HPP
