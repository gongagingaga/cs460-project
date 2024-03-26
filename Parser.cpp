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



void Parser::createCST() {
    while(currToken < tokens.size()){
        if(tokens[currToken].isString() && tokens[currToken].stringValue() == "function"){
            currToken++;
            checkFunctionDeclaration();
        }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "procedure"){

        }else{
            std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + "Expected function or procedure";
        }
    }
}

void Parser::checkFunctionDeclaration() {
    if(!(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"))){
        std::cout << "Expected a datatype on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isString() && (tokens[currToken].stringValue() != "getchar" || tokens[currToken].stringValue() != "printf"))){
        std::cout << "Expected an identifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    currToken++;
    checkParameterList();
    if(!(tokens[currToken].isChar() && (tokens[currToken].charValue() == '{'))){
        std::cout << "Expected an ( on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    checkCompoundStatement();
}

void Parser::checkParameterList() {
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Expected an ( on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    currToken++;
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "void"){
        currToken++;
        if(tokens[currToken].isChar() && tokens[currToken].charValue() == ')'){
            currToken++;
            return;
        }else{
            std::cout << "Expected an ) on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
    }
    while(!(tokens[currToken].isChar() && tokens[currToken].charValue() != ')')){

    }
}

bool Parser::parseProgram() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "procedure" ){
        if(tokens[currToken+1].isString() && tokens[currToken+1].stringValue() == "main"){
            currToken += 2;
            parseMainProcedure();
            return true;
        }else{
            currToken++;
            parseProcedureDeclaration();
            parseProgram();
        }
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "function"){
        currToken++;
        parseFunctionDeclaration();
        parseProgram();
    }else if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool")){
        currToken++;
        parseDeclarationStatement();
        parseProgram();
    }
}

bool Parser::parseMainProcedure() {
    //Assume parsed first 2 tokens
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected (";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "void")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected void in main parameter list";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == ')')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected )";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '{')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected {";
        exit(2);
    }
    currToken++;
    parseCompoundStatement();
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    currToken++;
    return true;
}

bool Parser::parseProcedureDeclaration() {
    //Expects first token parsed
    if(!(tokens[currToken].isString())){
        std::cout << "Expected an identifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    if(tokens[currToken].stringValue() != "getchar"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : getchar is a reserved identifier";
        exit(2);
    }
    if(tokens[currToken].stringValue() != "printf"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : printf is a reserved identifier";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected (";
        exit(2);
    }
    currToken++;
    if(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"){
        parseParameterList();
    }else if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "void")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected void in main parameter list";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == ')')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected )";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '{')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected {";
        exit(2);
    }
    currToken++;
    parseCompoundStatement();
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    currToken++;
    return true;
}

bool Parser::parseFunctionDeclaration() {
    //Expects first token parsed
    if(!(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool")){
        std::cout << "Expected a datatype specifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isString())){
        std::cout << "Expected an identifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    if(tokens[currToken].stringValue() != "getchar"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : getchar is a reserved identifier";
        exit(2);
    }
    if(tokens[currToken].stringValue() != "printf"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : printf is a reserved identifier";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected (";
        exit(2);
    }
    currToken++;
    if(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"){
        parseParameterList();
    }else if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "void")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected void in main parameter list";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == ')')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected )";
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '{')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected {";
        exit(2);
    }
    currToken++;
    parseCompoundStatement();
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    currToken++;
    return true;
}

bool Parser::parseParameterList() {
    if(!(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool")){
        std::cout << "Expected a datatype specifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    currToken++;
    if(!(tokens[currToken].isString())){
        std::cout << "Expected an identifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    currToken++;
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"){
        parseParameterList();
    }
    return true;
}

bool Parser::parseCompoundStatement() {

}

bool Parser::parseStatement() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "return"){
        parseReturnStatement();
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "printf"){
        parsePrintfStatement();
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "for"){
        parseIterationStatement();
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "if"){
        parseSelectionStatement();
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"){
        parseDeclarationStatement();
    }else if(tokens[currToken].isString()){
        parseAssignmentStatement();
    }else{
        std::cout << "Expected Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    return true;
}

bool Parser::parseReturnStatement() {
    return false;
}

bool Parser::parseDeclarationStatement() {
    return false;
}

bool Parser::parseUserDefinedFunction() {
    return false;
}

bool Parser::parseGetcharFunction() {
    return false;
}

bool Parser::parsePrintfStatement() {
    return false;
}

bool Parser::parseAssignmentStatement() {
    return false;
}

bool Parser::parseIterationStatement() {
    return false;
}

bool Parser::parseSelectionStatement() {
    return false;
}

bool Parser::parseExpression() {
    return false;
}

bool Parser::parseInitializationExpression() {
    return false;
}

bool Parser::parseBooleanExpression() {
    return false;
}

bool Parser::parseNumericalExpression() {
    return false;
}

bool Parser::parseRelationalExpression() {
    return false;
}

bool Parser::parseEqualityExpression() {
    return false;
}

bool Parser::parseBooleanOperator() {
    return false;
}

bool Parser::parseNumericalOperator() {
    return false;
}

bool Parser::parseNumericalOperand() {
    return false;
}

bool Parser::parseDatatypeSpecifier() {
    return false;
}

bool Parser::parseIdentifierAndIdentifierArrayList() {
    return false;
}

bool Parser::parseIdentifierArrayList() {
    return false;
}

bool Parser::parseIdentifierList() {
    return false;
}

