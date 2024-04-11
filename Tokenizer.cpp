#include "Tokenizer.hpp"
#include <iostream>

Tokenizer::Tokenizer(const std::string &inputFile): inputFileName{inputFile} {}

Token Tokenizer::getToken() {
    Token newToken;

    if( currChar >= uncommentedFile.length() ) {
        newToken.bnfValue() = EOF;
        newToken.isEOF() = true;
        newToken.setLineNumber(currLine);
        return newToken;
    }

    char c = uncommentedFile[currChar];

    if(c == '\n'){
        currLine++;
        currChar++;
        return getToken();
    }
    if(c == '('){
        newToken.bnfValue() = L_PAREN;
        newToken.charValue() = '(';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == ')') {
        newToken.bnfValue() = R_PAREN;
        newToken.charValue() = ')';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '{') {
        newToken.bnfValue() = L_BRACE;
        newToken.charValue() = '{';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '}') {
        newToken.bnfValue() = R_BRACE;
        newToken.charValue() = '}';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == ';') {
        newToken.bnfValue() = SEMICOLON;
        newToken.charValue() = ';';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '[') {
        newToken.bnfValue() = L_BRACKET;
        newToken.charValue() = '[';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == ']') {
        newToken.bnfValue() = R_BRACKET;
        newToken.charValue() = ']';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == ',') {
        newToken.bnfValue() = COMMA;
        newToken.charValue() = ',';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '+') {
        if(isdigit(uncommentedFile[currChar + 1])) {
            bool isFloat = false;
            std::string value = "";
            currChar++;
            c = uncommentedFile[currChar];
            while(c == '.' || isdigit(c)){
                if(c == '.' && !isFloat){
                    isFloat = true;
                }else if(c == '.'){
                    std::cout << "Error with float and int" << std::endl;
                    exit(2);
                }
                value += c;
                currChar++;
                c = uncommentedFile[currChar];
            }
            newToken.bnfValue() = INTEGER;
            newToken.intValue() = std::stoi(value);
            newToken.isInt() = true;
            newToken.setLineNumber(currLine);
            return newToken;
        }
        newToken.bnfValue() = PLUS;
        newToken.charValue() = '+';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '*') {
        newToken.bnfValue() = ASTERISK;
        newToken.charValue() = '*';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '/') {
        newToken.bnfValue() = DIVIDE;
        newToken.charValue() = '/';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '%') {
        newToken.bnfValue() = MODULO;
        newToken.charValue() = '%';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '^') {
        newToken.bnfValue() = CARET;
        newToken.charValue() = '^';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '"') {
        newToken.bnfValue() = DOUBLE_QUOTE;
        newToken.charValue() = '"';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }

    if(c == '\'') {
        newToken.bnfValue() = SINGLE_QUOTE;
        newToken.charValue() = '\'';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '=') {
        if(uncommentedFile[currChar + 1] == '='){
            newToken.bnfValue() = EQUALITY_EXPRESSION;
            newToken.stringValue() = "==";
            newToken.isString() = true;
            currChar += 2;
            newToken.setLineNumber(currLine);
            return newToken;
        }else {
            newToken.bnfValue() = ASSIGNMENT_OPERATOR;
            newToken.charValue() = '=';
            newToken.isChar() = true;
            currChar++;
            newToken.setLineNumber(currLine);
            return newToken;
        }
    }
    if(c == '<') {
        if(uncommentedFile[currChar + 1] == '='){
            newToken.bnfValue() = LT_EQUAL;
            newToken.stringValue() = "<=";
            newToken.isString() = true;
            currChar += 2;
            newToken.setLineNumber(currLine);
            return newToken;
        }else{
            newToken.bnfValue() = LT;
            newToken.charValue() = '<';
            newToken.isChar() = true;
            currChar++;
            newToken.setLineNumber(currLine);
            return newToken;
        }
    }
    if(c == '>') {
        if(uncommentedFile[currChar + 1] == '='){
            newToken.bnfValue() = GT_EQUAL;
            newToken.stringValue() = ">=";
            newToken.isString() = true;
            currChar += 2;
            newToken.setLineNumber(currLine);
            return newToken;
        }else{
            newToken.bnfValue() = GT;
            newToken.charValue() = '>';
            newToken.isChar() = true;
            currChar++;
            newToken.setLineNumber(currLine);
            return newToken;
        }
    }
    if(c == '|') {
        if(uncommentedFile[currChar + 1] == '|'){
            newToken.bnfValue() = BOOLEAN_OR;
            newToken.stringValue() = "||";
            newToken.isString();
            currChar += 2;
            newToken.setLineNumber(currLine);
            return newToken;
        }else {
            newToken.bnfValue() = UNKNOWN;
            currChar++;
            newToken.setLineNumber(currLine);
            return newToken;
        }
    }
    if(c == '&') {
        if(uncommentedFile[currChar + 1] == '&'){
            newToken.bnfValue() = BOOLEAN_AND;
            newToken.stringValue() = "&&";
            newToken.isString() = true;
            currChar += 2;
            newToken.setLineNumber(currLine);
            return newToken;
        }
        newToken.bnfValue() = UNKNOWN;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '!') {
        if (uncommentedFile[currChar + 1] == '=') {
            newToken.bnfValue() = BOOLEAN_NOT_EQUAL;
            newToken.stringValue() = "!=";
            newToken.isString() = true;
            currChar += 2;
            newToken.setLineNumber(currLine);
            return newToken;
        }
        newToken.bnfValue() = BOOLEAN_NOT;
        newToken.charValue() = '!';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(isalpha(c)){
        std::string value = "";
        value += c;
        currChar++;
        c = uncommentedFile[currChar];
        while(isalpha(c) || c == '_' || isdigit(c)){
            value += c;
            currChar++;
            c = uncommentedFile[currChar];
        }
        newToken.bnfValue() = IDENTIFIER;
        if(value.length() == 1){
            newToken.isChar() = true;
            newToken.charValue() = value[0];
        }else{
            newToken.isString() = true;
            newToken.stringValue() = value;
        }
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(isdigit(c)){
        bool isFloat = false;
        std::string value = "";
        value += c;
        currChar++;
        c = uncommentedFile[currChar];
        while(c == '.' || isdigit(c)){
            if(c == '.' && !isFloat){
                isFloat = true;
            }else if(c == '.'){
                std::cout << "Error with float and int" << std::endl;
                exit(2);
            }
            value += c;
            currChar++;
            c = uncommentedFile[currChar];
        }
        newToken.bnfValue() = INTEGER;
        newToken.intValue() = std::stoi(value);
        newToken.isInt() = true;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    if(c == '-') {
        if(isdigit(uncommentedFile[currChar + 1])) {
            bool isFloat = false;
            std::string value = "";
            value += c;
            currChar++;
            c = uncommentedFile[currChar];
            while(c == '.' || isdigit(c)){
                if(c == '.' && !isFloat){
                    isFloat = true;
                }else if(c == '.'){
                    std::cout << "Error with float and int" << std::endl;
                    exit(2);
                }
                value += c;
                currChar++;
                c = uncommentedFile[currChar];
            }
            newToken.bnfValue() = INTEGER;
            newToken.intValue() = std::stoi(value);
            newToken.isInt() = true;
            newToken.setLineNumber(currLine);
            return newToken;
        }
        newToken.bnfValue() = MINUS;
        newToken.charValue() = '-';
        newToken.isChar() = true;
        currChar++;
        newToken.setLineNumber(currLine);
        return newToken;
    }
    currChar++;
    return getToken();

}

Token Tokenizer::getStringToken(char terminator) {
    std::string value = "";
    char c = uncommentedFile[currChar];
    while(c != terminator){
        if(c == '\\'){
            value += c;
            currChar++;
            c = uncommentedFile[currChar];
        }
        value += c;
        currChar++;
        if(currChar == uncommentedFile.length()){
            std::cout << "Syntax Error on line " + std::to_string(currLine) + ": Unterminated double quote string.";
            exit(2);
        }
        c = uncommentedFile[currChar];
    }
    Token newToken;
    if(value.length() == 1){
        newToken.bnfValue() = CHARACTER;
        newToken.isChar() = true;
        newToken.charValue() = value[0];
    }else{
        newToken.bnfValue() = STRING;
        newToken.isString() = true;
        newToken.stringValue() = value;
    }
    newToken.setLineNumber(currLine);
    return newToken;
}

void Tokenizer::uncommentFile() {
    // open file
    std::ifstream inFile;
    inFile.open(inputFileName);
    if(!inFile.is_open()){
        std::cout << "File cannot be opened." << std::endl;
        exit(1);
    }

    int lineNumber = 1;
    bool inQuote = false;
    std::string output = "";
    char currChar;
    while(inFile.get(currChar)){
        // edge case of terminating block comment before starting one
        if(currChar == '*' && !inQuote){
            char c = inFile.peek();
            if(c == '/'){
                std::cerr << "ERROR: Program contains C-style, "
                          << "unterminated comment on line "
                          << lineNumber
                          << std::endl;
                exit(3);
            }
        }
        if(currChar == '/' && !inQuote){
            inFile.get(currChar);
            //start of single line comment
            if(currChar == '/'){
                std::string spaces = "  ";
                while(inFile.get(currChar)){
                    if(currChar == '\n'){
                        lineNumber++;
                        spaces += '\n';
                        break;
                    }
                    spaces += ' ';
                }
                output += spaces;

            }else if(currChar == '*'){ //start of multiline comment
                std::string spaces = "  ";
                int newLines = 0;
                while(inFile.get(currChar)){
                    if(currChar == '*'){
                        if(inFile.peek() == '/'){
                            inFile.get(currChar);
                            spaces += "  ";
                            break;
                        }
                    }
                    if(currChar == '\n'){
                        newLines++;
                        spaces += '\n';
                    }else {
                        spaces += ' ';
                    }
                }
                // checking for unterminated multiline comment
                if(inFile.eof()){
                    std::cerr << "ERROR: Program contains C-style, "
                              << "unterminated comment on line "
                              << lineNumber
                              << std::endl;
                    exit(2);
                }
                output += spaces;
                lineNumber += newLines;
            }else{
                output += "/";
                output += currChar;
            }
        }else{
            // checking edge case of comments in quotes
            if(currChar == '\'' || currChar == '"'){
                inQuote = !inQuote;
            }
            output += currChar;
            if(currChar == '\n'){
                lineNumber++;
            }
        }
    }

    // output new version of the file
    //std::cout << output;


    uncommentedFile = output;
}