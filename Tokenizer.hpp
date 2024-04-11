#ifndef TOKENIZER_TOKENIZER_HPP
#define TOKENIZER_TOKENIZER_HPP
#include "Token.hpp"
#include <fstream>

class Tokenizer {
public:
    explicit Tokenizer(const std::string &inputFile);
    void uncommentFile();
    void printUncommentedFile(){std::cout << uncommentedFile << std::endl;};

    Token getToken();
    Token getStringToken(char terminator);

private:
    std::string inputFileName;
    std::string uncommentedFile;
    int currChar = 0;
    int currLine = 1;

};


#endif //TOKENIZER_TOKENIZER_HPP
