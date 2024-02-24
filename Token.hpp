#include <cctype>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

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
    Token() {}

    //if needed for some reason, we can create boolean functions to re-identify what tokens are:
    bool isCharacter() { return _bnfValue == CHARACTER; }
    bool isQuotedString() { return _bnfValue == DOUBLE_QUOTED_STRING || _bnfValue == SINGLE_QUOTED_STRING; }
    bool isDigit() { return _bnfValue == DIGIT; }
    bool isboolean() { return _bnfValue == BOOLEAN_FALSE || _bnfValue == BOOLEAN_TRUE; }
    bool isIdentifier() { return _bnfValue == IDENTIFIER; }
    bool isDatatypeSpecifier() { return _bnfValue == DATATYPE_SPECIFIER; }

    /*
     * these functions allow you to store values and retrieve them:
     * token.character() = 'c';
     * char a = token.character();
    */
    int &bnfValue() { return _bnfValue; }
    char &character() { return _character; }
    std::string &booleanOperator() { return _booleanOperator; }
    std::string &quotedString() { return _quotedString; }
    int &digit() { return _digit; }
    bool &boolean() { return _boolean; }

    std::string toString();
private:
    int _bnfValue;
    char _character = '\0';             //storage for CHARACTER, ESCAPED_CHARACTER, LETTER, HEX_DIGIT and others (L_PAREN, R_PAREN, L_BRACKET, etc.)
    std::string _booleanOperator;
    std::string _quotedString;          //storage for DOUBLE_QUOTED_STRING, SINGLE_QUOTED_STRING
    int _digit = NULL;                  //storage for DIGIT
    bool _boolean = NULL;               //storage for BOOLEAN_TRUE and BOOLEAN_FALSE
    std::string _name;                  //storage for IDENTIFIER, DATATYPE_SPECIFIER
};
