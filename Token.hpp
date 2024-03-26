//
// Created by candy on 2/24/2024.
//

#ifndef TOKENIZER_TOKEN_HPP
#define TOKENIZER_TOKEN_HPP
#include <string>
#include <iostream>

enum BNF{
    CHARACTER,
    ESCAPED_CHARACTER,
    LETTER,
    DIGIT,
    HEX_DIGIT,
    L_PAREN,
    R_PAREN,
    L_BRACKET,
    R_BRACKET,
    L_BRACE,
    R_BRACE,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    SEMICOLON,
    COMMA,
    ASSIGNMENT_OPERATOR,
    PLUS,
    MINUS,
    ASTERISK,
    DIVIDE,
    MODULO,
    CARET,
    LT,
    GT,
    LT_EQUAL,
    GT_EQUAL,
    BOOLEAN_AND,
    BOOLEAN_OR,
    BOOLEAN_NOT,
    BOOLEAN_EQUAL,
    BOOLEAN_NOT_EQUAL,
    BOOLEAN_TRUE,
    BOOLEAN_FALSE,
    STRING,
    DOUBLE_QUOTED_STRING,
    SINGLE_QUOTED_STRING,
    LETTER_UNDERSCORE,
    LETTER_DIGIT_UNDERSCORE,
    WHOLE_NUMBER,
    INTEGER,
    IDENTIFIER,
    IDENTIFIER_LIST,
    IDENTIFIER_ARRAY_LIST,
    IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST,
    DATATYPE_SPECIFIER,
    NUMERICAL_OPERAND,
    NUMERICAL_OPERATOR,
    BOOLEAN_OPERATOR,
    EQUALITY_EXPRESSION,
    RELATIONAL_EXPRESSION,
    NUMERICAL_EXPRESSION,
    BOOLEAN_EXPRESSION,
    INITIALIZATION_EXPRESSION,
    EXPRESSION,
    SELECTION_STATEMENT,
    ITERATION_STATEMENT,
    ASSIGNMENT_STATEMENT,
    PRINTF_STATEMENT,
    GETCHAR_FUNCTION,
    USER_DEFINED_FUNCTION,
    DECLARATION_STATEMENT,
    RETURN_STATEMENT,
    STATEMENT,
    COMPOUND_STATEMENT,
    BLOCK_STATEMENT,
    PARAMETER_LIST,
    FUNCTION_DECLARATION,
    PROCEDURE_DECLARATION,
    MAIN_PROCEDURE,
    PROGRAM,
    UNKNOWN
};

class Token {
public:
    Token(): _isChar{false}, _isString{false}, _isInt{false}, _isFloat{false}, _isBool{false}, _isEOF{false} {};
	
	std::string BNFtoString(int bnf);

    void printValue();

    int &bnfValue() { return _bnf; };
    char &charValue() { return _charValue; };
    bool &boolValue() {return _boolValue; };
    float &floatValue() {return _floatValue;};
    int &intValue() {return _intValue;};
    std::string &stringValue() { return _stringValue; };

    bool &isChar() { return _isChar; };
    bool &isString() { return _isString; };
    bool &isInt() { return _isInt; };
    bool &isFloat() { return _isFloat; };
    bool &isBool() { return _isBool; };
    bool &isEOF() { return _isEOF; };

    void setLineNumber(int lineNum) {_lineNumber = lineNum;};
    int getLineNumber() {return _lineNumber;};

private:
    int _intValue;
    float _floatValue;
    char _charValue;
    bool _boolValue;
    std::string _stringValue;
    int _bnf;
    bool _isChar, _isString, _isInt, _isFloat, _isBool, _isEOF;
    int _lineNumber;
};


#endif //TOKENIZER_TOKEN_HPP
