#ifndef TOKENIZER_PARSER_HPP
#define TOKENIZER_PARSER_HPP
#include "Tokenizer.hpp"
#include <string>
#include <vector>
#include "cst.hpp"
#include "SymbolTable.hpp"

class Parser {
public:
    Parser(const std::string fileName): tokenizer{Tokenizer(fileName)}, paramListHead{nullptr}, paramListTail{nullptr}, parserScope{0} {
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
    bool parseStatement(bool error, bool blockStatement);
    bool parseReturnStatement(bool error);
    bool parseDeclarationStatement(bool error, bool blockStatement);
    bool parseUserDefinedFunction(bool error);
    bool parseGetcharFunction(bool error);
    bool parsePrintfStatement(bool error);
    bool parseAssignmentStatement(bool error, bool blockStatement);
    bool parseIterationStatement(bool error);
    bool parseSelectionStatement(bool error);
    bool parseExpression(bool error, bool blockStatement);
    bool parseInitializationExpression(bool error, bool blockStatement);
    bool parseBooleanExpression(bool error, bool blockStatement);
    bool parseNumericalExpression(bool error);
    bool parseRelationalExpression(bool error);
    bool parseEqualityExpression(bool error);
    bool parseBooleanOperator(bool error);
    bool parseNumericalOperator(bool error);
    bool parseNumericalOperand(bool error);
    bool parseDatatypeSpecifier(bool error);
    bool parseIdentifierAndIdentifierArrayList(bool error, bool blockStatement);
    bool parseIdentifierArrayList(bool error, bool blockStatement);
    bool parseIdentifierList(bool error, bool blockStatement);
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

    void printTokens() {
        for(auto token: tokens) {
            token.printValue();
            std::cout << " ---> ";
        }
    }

    //cst insert wrapper that also handles the switching of the direction
    void insert(std::string value, bool nextDir){
        CST.insert(value, nextDir);
    }

    void deleteRange(int howMany){
        CST.deleteRange(howMany);

        // because we update the currToken only after we call the delete function
        // we need the switchDir() to think that it's a few tokens back
        tempCurrToken = currToken;
        currToken = currToken - howMany;
        //switchDir();
        currToken = tempCurrToken;
    }

    void printTree(){
        std::cout << "Printing:\n";
        CST.print();
    }

    //should probably be private

    int tempCurrToken;
    std::vector<Token> tokens;
    Tokenizer tokenizer;
    int currToken = 0;
    cst CST;
    std::string nextDir = "right";
    bool inForLoop = false;

    /* change - Dawson */
    SymbolTable symbolTable;
    SymbolTableNode *currSymbolTableNode;
    SymbolTableNode *paramListHead, *paramListTail;
    int parserScope;
};


#endif //TOKENIZER_PARSER_HPP