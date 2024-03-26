//
// Created by candy on 2/24/2024.
//

#ifndef TOKENIZER_PARSER_HPP
#define TOKENIZER_PARSER_HPP
#include "Tokenizer.hpp"
#include <vector>

class Node {
public:
    Node(const std::string inputValue) : value(inputValue), leftChild(nullptr), rightChild(nullptr) {};
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
    Parser(const std::string fileName): tokenizer{Tokenizer(fileName)}, CST(nullptr), currNode(nullptr) {};
    void parseFile();
    void parseToken(Token token);
    std::vector<Token> getTokens() {return tokens;};
    void print();
    void createCST();
    void checkFunctionDeclaration();
    void checkParameterList();
    bool parseProgram();
    bool parseMainProcedure();
    bool parseProcedureDeclaration();
    bool parseFunctionDeclaration();
    bool parseParameterList();
    bool parseBlockStatement();
    bool parseCompoundStatement();
    bool parseStatement();
    bool parseReturnStatement();
    bool parseDeclarationStatement();
    bool parseUserDefinedFunction();
    bool parseGetcharFunction();
    bool parsePrintfStatement();
    bool parseAssignmentStatement();
    bool parseIterationStatement();
    bool parseSelectionStatement();
    bool parseExpression();
    bool parseInitializationExpression();
    bool parseBooleanExpression();
    bool parseNumericalExpression();
    bool parseRelationalExpression();
    bool parseEqualityExpression();
    bool parseBooleanOperator();
    bool parseNumericalOperator();
    bool parseNumericalOperand();
    bool parseDatatypeSpecifier();
    bool parseIdentifierAndIdentifierArrayList();
    bool parseIdentifierArrayList();
    bool parseIdentifierList();


private:
    std::vector<Token> tokens;
    Tokenizer tokenizer;
    int currToken = 0;
    Node* CST;
    Node* currNode;
    bool hasMain = false;
};


#endif //TOKENIZER_PARSER_HPP