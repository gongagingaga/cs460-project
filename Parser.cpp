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


//not on qivi
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

//parsefunctiondecl
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

//parseparamlist
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
    int savedIdx = currToken;
    if(parseMainProcedure()){
        return true;
    }
    currToken = savedIdx;
    if(parseFunctionDeclaration() && parseProgram()){
        return true;
    }
    currToken = savedIdx;
    if(parseProcedureDeclaration() && parseProgram()){
        return true;
    }
    currToken = savedIdx;
    if(parseDeclarationStatement() && parseProgram()){
        return true;
    }
    currToken = savedIdx;
    return false;
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
    parseCompoundStatement();//should be block-----------------------------------------------------------------------------------------------------
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    currToken++;
    return true;
}

bool Parser::parseProcedureDeclaration() {
    //Expects first token parsed
    if (!(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool")) {
        std::cout << "Expected a datatype specifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
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
    parseCompoundStatement();//should be block -----------------------------------------------------------------------------------------------------
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
    parseCompoundStatement();//block statement-----------------------------------------------------------------------------------------------------
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    currToken++;
    return true;
}

bool Parser::parseParameterList() {
    int savedIdx = currToken;
    if(parseDatatypeSpecifier() && parseIdentifier()){
        return true;
    }
    currToken = savedIdx;
    if(parseDatatypeSpecifier() && parseIdentifier() && parseParameterList()){
        return true;
    }
    currToken = savedIdx;
    return false;
}

//to do --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Parser::parseCompoundStatement() {
    //block of code refers to this
    //while not end of block, read statements
    while(tokens[currToken].isChar() && tokens[currToken].charValue() == '}'){
        parseStatement();
    }
    return true;
}

bool Parser::parseStatement() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "return"){
        parseReturnStatement();
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "printf"){
        parsePrintfStatement();
    }else if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "for" || tokens[currToken].stringValue() == "while")){ //should be for iteration statement
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


//do these guys-----------------PLS CHECK THESE-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//also check the error statemetns
//need to find out where currtoken++




//0-12 child/preteen\
//13-18 teen/ older child
//18-25 young adult also acceptable 18-30
//25-60 middle ages depends on person really
//60-end of life, older adult



bool Parser::parseReturnStatement() {
    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "return")){
        return false;
    }
    currToken++;
    int savedIdx = currToken;
    if (parseExpression() && parseSemicolon()) { //return <EXPRESSION> <SEMICOLON>
        return true;
    }
    currToken = savedIdx;
    if (parseSingleQuotedStr() && parseSemicolon()){ //return <SINGLE_QUOTED_STRING> <SEMICOLON>
        return true;
    }
    currToken = savedIdx;
    if (parseDoubleQuotedStr() && parseSemicolon()) { //return <DOUBLE_QUOTED_STRING> <SEMICOLON>
        return true;
    }
    currToken = savedIdx;
    return false;
}


bool Parser::parseDeclarationStatement() {
    int savedIdx = currToken;
    if ( parseDatatypeSpecifier() && parseIdentifier() && tokens[currToken].stringValue() == ";") {
        return true;
    }
    currToken = savedIdx;
    if (parseDatatypeSpecifier() && parseIdentifierAndIdentifierArrayList() && tokens[currToken].stringValue() == ";") {
        return true;
    }
    currToken = savedIdx;
    std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
    exit(2);
}

//do we need this? It would be doing the same as the regualr function no?
bool Parser::parseUserDefinedFunction() {//<DATATYPE_SPECIFIER> <IDENTIFIER><SEMICOLON> | <DATATYPE_SPECIFIER><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <SEMICOLON>
    if (parseIdentifier() && tokens[currToken].stringValue() == ";"){
        return true;
    }
    if (parseIdentifierAndIdentifierArrayList() &&  && tokens[currToken].stringValue() == ";") {
        return true;
    }
    std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
    exit(2);
}

//<IDENTIFIER> <L_PAREN><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <R_PAREN> | <IDENTIFIER><L_PAREN> <EXPRESSION> <R_PAREN>
bool Parser::parseGetcharFunction() {
    if (parseIdentifier() && tokens[currToken].stringValue() == "(") {
        if (parseIdentifierAndIdentifierArrayList() && tokens[currToken].stringValue() == ")") {
            return true;
        }
        else if (parseExpression() && tokens[currToken].stringValue() == ")") {
            return true;
        }
    } else {
        std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    return false;
}

//printf <L_PAREN> <DOUBLE_QUOTED_STRING> <R_PAREN><SEMICOLON> |
//printf <L_PAREN> <SINGLE_QUOTED_STRING> <R_PAREN><SEMICOLON> |
//printf <L_PAREN> <DOUBLE_QUOTED_STRING> <COMMA><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <R_PAREN> <SEMICOLON> |
//printf<L_PAREN> <SINGLE_QUOTED_STRING> <COMMA><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <R_PAREN> <SEMICOLON>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Fixed by qivi
bool Parser::parsePrintfStatement() {
    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "printf")){
        return false;
    }
    currToken++;
    int savedIdx = currToken;
    if (parseLParenthesis() && parseDoubleQuotedStr() && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    currToken = savedIdx;
    if (parseLParenthesis() && parseSingleQuotedStr() && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    currToken = savedIdx;
    if (parseLParenthesis() && parseDoubleQuotedStr() && parseComma() && parseIdentifierAndIdentifierArrayList() && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    if (parseLParenthesis() && parseSingleQuotedStr() && parseComma() && parseIdentifierAndIdentifierArrayList() && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    currToken = savedIdx;
    return false;
}

//<IDENTIFIER> <ASSIGNMENT_OPERATOR><EXPRESSION> <SEMICOLON> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR><SINGLE_QUOTED_STRING> <SEMICOLON> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR> <DOUBLE_QUOTED_STRING> <SEMICOLON>
bool Parser::parseAssignmentStatement() {
    if (parseIdentifier() && tokens[currToken].stringValue() == "=") {
        if (parseSingleQuotedStr()) {
            currToken += 2;
            return true;
        }
        else if (parseDoubleQuotedStr()) {
            currToken += 2;
            return true;
        }
        else if (parseExpression() && tokens[currToken].stringValue() == ";") {
            currToken += 2;
            return true;
        }
        else {
            std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
    }
    else {
        std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    return false;
}

//for <L_PAREN> <INITIALIZATION_EXPRESSION><SEMICOLON> <BOOLEAN_EXPRESSION> <SEMICOLON> <EXPRESSION> <R_PAREN><STATEMENT> |
//for <L_PAREN> <INITIALIZATION_EXPRESSION> <SEMICOLON><BOOLEAN_EXPRESSION> <SEMICOLON> <EXPRESSION> <R_PAREN><BLOCK_STATEMENT> |
//while <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><STATEMENT> |
//while <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><BLOCK_STATEMENT>
bool Parser::parseIterationStatement() {
    //cannot assume for or while were parsed
    if (tokens[currToken].stringValue() == "for") {
        if (tokens[currToken].stringValue() != "(") {
            std::cout << "Expected ( . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (!parseInitializationExpression()) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (tokens[currToken].stringValue() != ";") {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (!parseBooleanExpression) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (tokens[currToken].stringValue() != ";") {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (!parseExpression) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        if (tokens[currToken].stringValue() != ")") {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (tokens[currToken].stringValue() != "{") {
            parseBlockStatement();
        }
        else {
            parseStatement();
        }
        return true;

    }
    else if (tokens[currToken].stringValue() == "while") {
        currToken++;
        if (tokens[currToken].stringValue() != "(") {
            std::cout << "Expected ( . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (!parseBooleanExpression()) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (tokens[currToken].stringValue() != ")") {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (tokens[currToken].stringValue() != "{") {
            parseBlockStatement();
        }
        else {
            parseStatement();
        }
        return true;

    }
    else {
        std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    return false;
}

//if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><STATEMENT> |
//if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <STATEMENT>else <STATEMENT> |
//if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><BLOCK_STATEMENT> |
//if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><BLOCK_STATEMENT> else <STATEMENT> |
//if <L_PAREN><BOOLEAN_EXPRESSION> <R_PAREN> <BLOCK_STATEMENT> else<BLOCK_STATEMENT> |
//if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><STATEMENT> else <BLOCK_STATEMENT>
bool Parser::parseSelectionStatement() {
    if (tokens[currToken].stringValue() == "if") {
        if (tokens[currToken].stringValue() != "(") {
            std::cout << "Expected ( . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (!parseBooleanExpression) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (tokens[currToken].stringValue() != ")") {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        currToken++;
        if (tokens[currToken].stringValue() == "{") {
            parseBlockStatement();
        }
        else {
            parseStatement();
        }
        if (tokens[currToken].stringValue() == "else") {
            currToken++;
            if (tokens[currToken].stringValue() == "{") {
                parseBlockStatement();
            }
            else {
                parseStatement();
            }
        }
        return true;
    }
    else {
        std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    return false;
}

//<BOOLEAN_EXPRESSION> | <NUMERICAL_EXPRESSION>
bool Parser::parseExpression() {
    int savedIdx = currToken;
    if (parseBooleanExpression()) {//would not work pls
        return true;
    }
    currToken = savedIdx;
    if(parseNumericalExpression()){
        return true;
    }
    currToken = savedIdx;
    return false;
}

//<IDENTIFIER> <ASSIGNMENT_OPERATOR><EXPRESSION> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR><SINGLE_QUOTED_STRING> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR><DOUBLE_QUOTED_STRING>
bool Parser::parseInitializationExpression() {
    if (parseIdentifier() && tokens[currToken].stringValue() == "=")) {

    }
    else {
        std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    return false;
}

//<BOOLEAN_TRUE> | <BOOLEAN_FALSE> | <IDENTIFIER>| <IDENTIFIER> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> |
//<L_PAREN><IDENTIFIER> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> <R_PAREN> |
//<NUMERICAL_EXPRESSION> <BOOLEAN_EQUAL> <NUMERICAL_EXPRESSION> |
//<NUMERICAL_EXPRESSION> <BOOLEAN_NOT_EQUAL> <NUMERICAL_EXPRESSION> |
//<NUMERICAL_EXPRESSION> <LT_EQUAL> <NUMERICAL_EXPRESSION> |
//<NUMERICAL_EXPRESSION> <GT_EQUAL> <NUMERICAL_EXPRESSION> |
//<NUMERICAL_EXPRESSION> <LT> <NUMERICAL_EXPRESSION> |
//<NUMERICAL_EXPRESSION> <GT> <NUMERICAL_EXPRESSION>
bool Parser::parseBooleanExpression() {
    return false;
}

//<NUMERICAL_OPERAND> | <L_PAREN><NUMERICAL_OPERAND> <R_PAREN> |
//<NUMERICAL_OPERAND><NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> |
//<L_PAREN><NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION><R_PAREN> |
//<NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN><NUMERICAL_EXPRESSION> <R_PAREN> <NUMERICAL_OPERAND><NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> |
//<L_PAREN><NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION><R_PAREN> |
//<NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN><NUMERICAL_EXPRESSION> <R_PAREN>
bool Parser::parseNumericalExpression() {
    return false;
}

//<LT> | <LT_EQUAL> | <GT> | <GT_EQUAL> |<BOOLEAN_EQUAL> | <BOOLEAN_NOT_EQUAL>
bool Parser::parseRelationalExpression() {
    if (tokens[currToken].isChar() && (tokens[currToken].charValue() == '<' || tokens[currToken].charValue() == '>')) {
        currToken++;
        return true;
    }
    if (tokens[currToken].isString() && (tokens[currToken].stringValue() == "<=" || tokens[currToken].stringValue() == ">=" || tokens[currToken].stringValue() == "==" || tokens[currToken].stringValue() == "!=")) {
        currToken++;
        return true;
    }
    return false;
}

//<BOOLEAN_EQUAL> | <BOOLEAN_NOT_EQUAL>
bool Parser::parseEqualityExpression() {
    return false;
}

//<BOOLEAN_AND_OPERATOR> | <BOOLEAN_OR_OPERATOR>
bool Parser::parseBooleanOperator() {
    return false;
}

//<PLUS> | <MINUS> | <ASTERISK> | <DIVIDE> |<MODULO> | <CARET>
bool Parser::parseNumericalOperator() {
    return false;
}

//<IDENTIFIER> | <INTEGER> | <GETCHAR_FUNCTION> |<USER_DEFINED_FUNCTION> | <SINGLE_QUOTE> <CHARACTER> <SINGLE_QUOTE> |
//<SINGLE_QUOTE> <ESCAPED_CHARACTER> <SINGLE_QUOTE> | <DOUBLE_QUOTE><CHARACTER> <DOUBLE_QUOTE> | <DOUBLE_QUOTE> <ESCAPED_CHARACTER>< DOUBLE_QUOTE
bool Parser::parseNumericalOperand() {
    if(tokens[currToken].isInt()){
        currToken++;
        return true;
    }
    int savedIdx = currToken;
    if(parseGetcharFunction()){
        return true;
    }
    currToken = savedIdx;
    if(parseUserDefinedFunction()){
        return true;
    }
    currToken = savedIdx;
    if(parseSingleQuote() && parseCharacter() && parseSingleQuote()){
        return true;
    }
    currToken = savedIdx;
    if(parseSingleQuote() && parseEscapeCharacter() && parseSingleQuote()){
        return true;
    }
    currToken = savedIdx;
    if(parseDoubleQuote() && parseCharacter() && parseDoubleQuote()){
        return true;
    }
    currToken = savedIdx;
    if(parseDoubleQuote() && parseCharacter() && parseDoubleQuote()){
        return true;
    }
    currToken = savedIdx;
    if(parseDoubleQuote() && parseEscapeCharacter() && parseDoubleQuote()){
        return true;
    }
    currToken = savedIdx;
    if(parseIdentifier()){
        return true;
    }
    return false;
}

//char | bool | int
bool Parser::parseDatatypeSpecifier() {
    return false;
}

//<IDENTIFIER_LIST> |<IDENTIFIER_ARRAY_LIST> | <IDENTIFIER_LIST> <IDENTIFIER_ARRAY_LIST> |<IDENTIFIER_ARRAY_LIST> < IDENTIFIER_LIST
bool Parser::parseIdentifierAndIdentifierArrayList() {
    return false;
}

//<IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER><R_BRACKET> | <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET><COMMA> <IDENTIFIER_ARRAY_LIST>
bool Parser::parseIdentifierArrayList() {
    return false;
}

//<IDENTIFIER> | <IDENTIFIER> <COMMA> |<IDENTIFIER_LIST>
bool Parser::parseIdentifierList() {
    int savedIdx = currToken;
    if(parseIdentifier() && parseComma() && parseIdentifierList()){
        return true;
    }
    currToken = savedIdx;
    if(parseIdentifier()){
        return true;
    }
    return false;
}

//<LETTER_UNDERSCORE> | <LETTER_UNDERSCORE><LETTER_DIGIT_UNDERSCORE> | <LETTER_UNDERSCORE><LETTER_DIGIT_UNDERSCORE> <IDENTIFIER>
bool Parser::parseIdentifier() {

}

//<WHOLE_NUMBER> | <PLUS> <WHOLE_NUMBER> | <MINUS><WHOLE_NUMBER>
bool Parser::parseInteger() {

}

//<DIGIT> | <DIGIT> <WHOLE_NUMBER>
bool Parser::parseWholeNum() {

}


//<SINGLE_QUOTE> <STRING> <SINGLE_QUOTE>
bool Parser::parseSingleQuotedStr() {

}

//<DOUBLE_QUOTE> <STRING> <DOUBLE_QUOTE>
bool Parser::parseDoubleQuotedStr() {

}

//<CHARACTER | <ESCAPED_CHARACTER> | <CHARACTER> <STRING> |<ESCAPED_CHARACTER> <STRING>
bool Parser::parseString() {
    currToken++;
    return true;
}

bool Parser::parseLetterDigitUnderscore() {
    if(tokens[currToken].isInt()){
        currToken++;
        return true;
    }
    if(!tokens[currToken].isChar()){
        return false;
    }
    if(tokens[currToken].isChar()){
        if(tokens[currToken].charValue() != '_' || !isalnum(tokens[currToken].charValue())){
            return false;
        }
    }
    currToken++;
    return true;
}

bool Parser::parseBooleanFalse() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "FALSE"){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanTrue() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "TRUE"){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanNotEqual() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "!="){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanEqual() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "=="){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanNot() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '!'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanOr() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "||"){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanAnd() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "&&"){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseGTequal() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == ">="){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLTequal() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "<="){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseGT() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '>'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLT() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '<'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseCaret() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '^'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseModulo() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '%'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseDivide() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '/'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseAsterisk() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '*'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseMinus() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '-'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parsePlus() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '+'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseAssignmentOperator() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '='){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseComma() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ','){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseSemicolon() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ';'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseSingleQuote() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '\''){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseDoubleQuote() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '"'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseRBrace() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '}'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLBrace() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '{'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseRParenthesis() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ')'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLParenthesis() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '('){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseRBracket() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ']'){
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLBracket() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '['){
        currToken++;
        return true;
    }
    return false;
}
