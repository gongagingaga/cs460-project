#include "Parser.hpp"

void Parser::parseFile() {
    tokenizer.uncommentFile();
    Token token = tokenizer.getToken();
    while(token.bnfValue() != EOF){
        parseToken(token);
        token = tokenizer.getToken();
    }
}

void Parser::parseToken(Token token) {
    if(token.bnfValue() == DOUBLE_QUOTE){
        tokens.push_back(token);
        token = tokenizer.getStringToken('"');
        tokens.push_back(token);
        token = tokenizer.getToken();
        if(token.bnfValue() != DOUBLE_QUOTE){
            std::cout << "Error with double quote" << std::endl;
            exit(4);
        }
    }
    if(token.bnfValue() == SINGLE_QUOTE){
        tokens.push_back(token);
        token = tokenizer.getStringToken('\'');
        tokens.push_back(token);
        token = tokenizer.getToken();
        if(token.bnfValue() != SINGLE_QUOTE){
            std::cout << "Error with single quote" << std::endl;
            exit(4);
        }
    }
    tokens.push_back(token);
}

void Parser::print() {
	std::cout << "Token list:\n" << std::endl;
    for(int i = 0; i < tokens.size(); i++){
        tokens[i].printValue();
		std::cout << std::endl;
    }
	std::cout << std::endl;
}

