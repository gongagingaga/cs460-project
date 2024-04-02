//
// Created by candy on 2/24/2024.
//

#ifndef TOKENIZER_PARSER_HPP
#define TOKENIZER_PARSER_HPP
#include "Tokenizer.hpp"
#include <vector>

class Node {
public:
    Node(std::string inputValue) : value(inputValue), leftChild(nullptr), rightChild(nullptr) {};
    Node(char inputValue) : leftChild(nullptr), rightChild(nullptr) {
        value = std::to_string(inputValue);
    };
    Node* getLeftChild() {return leftChild;};
    Node* getRightChild() {return rightChild;};
    void setLeftChild(Node* inputLeftChild) {leftChild = inputLeftChild;};
    void setRightChild(Node* inputRightChild) {rightChild = inputRightChild;};

private:
    Node* leftChild;
    Node* rightChild;
    std::string value;
};

class Parser {
public:
    Parser(const std::string fileName): tokenizer{Tokenizer(fileName)}, CST(nullptr) {
        startNode = new Node("start");
        currNode = startNode;
    };
    void parseFile();
    void parseToken(Token token);
    std::vector<Token> getTokens() {return tokens;};
    void print();
    void checkFunctionDeclaration();
    void checkParameterList();

    bool parseProgram();
    bool parseMainProcedure(bool error);
    bool parseProcedureDeclaration(bool error);
    bool parseFunctionDeclaration(bool error);
    bool parseParameterList(bool error);
    bool parseBlockStatement(bool error);
    bool parseCompoundStatement(bool error);
    bool parseStatement(bool error);
    bool parseReturnStatement(bool error);
    bool parseDeclarationStatement(bool error);
    bool parseUserDefinedFunction(bool error);
    bool parseGetcharFunction(bool error);
    bool parsePrintfStatement(bool error);
    bool parseAssignmentStatement(bool error);
    bool parseIterationStatement(bool error);
    bool parseSelectionStatement(bool error);
    bool parseExpression(bool error);
    bool parseInitializationExpression(bool error);
    bool parseBooleanExpression(bool error);
    bool parseNumericalExpression(bool error);
    bool parseRelationalExpression(bool error);
    bool parseEqualityExpression(bool error);
    bool parseBooleanOperator(bool error);
    bool parseNumericalOperator(bool error);
    bool parseNumericalOperand(bool error);
    bool parseDatatypeSpecifier(bool error);
    bool parseIdentifierAndIdentifierArrayList(bool error);
    bool parseIdentifierArrayList(bool error);
    bool parseIdentifierList(bool error);
    bool parseIdentifier(bool error);
    bool parseInteger(bool error);
    bool parseWholeNum(bool error);
    bool parseLetterDigitUnderscore(bool error);
    bool parseLetterUnderscore(bool error);
    bool parseSingleQuotedStr(bool error);
    bool parseDoubleQuotedStr(bool error);
    bool parseString();
    bool parseBooleanFalse();
    bool parseBooleanTrue();
    bool parseBooleanNotEqual();
    bool parseBooleanEqual();
    bool parseBooleanNot();
    bool parseBooleanOr();
    bool parseBooleanAnd();
    bool parseGTequal();
    bool parseLTequal();
    bool parseGT();
    bool parseLT();
    bool parseCaret();
    bool parseModulo();
    bool parseDivide();
    bool parseAsterisk();
    bool parseMinus();
    bool parsePlus();
    bool parseAssignmentOperator();
    bool parseComma();
    bool parseSemicolon();
    bool parseSingleQuote();
    bool parseDoubleQuote();
    bool parseRBrace();
    bool parseLBrace();
    bool parseRParenthesis();
    bool parseLParenthesis();
    bool parseRBracket();
    bool parseLBracket();
    bool parseHexDigit();
    bool parseDigit();
    bool parseLetter();
    bool parseEscapeCharacter();
    bool parseCharacter();


//private:
    std::vector<Token> tokens;
    Tokenizer tokenizer;
    int currToken = 0;
    Node* CST;
    Node* currNode;
    Node* startNode;
};


#endif //TOKENIZER_PARSER_HPP
