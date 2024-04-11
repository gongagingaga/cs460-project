#include "Parser.hpp"
#include <string>

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
        if(token.isChar() && token.bnfValue() != DOUBLE_QUOTE){
            std::cout << "Syntax error: missing ending \"" << std::endl;
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

//parsefunctiondecl
void Parser::checkFunctionDeclaration() {
    if(!(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"))){
        std::cout << "Expected a datatype on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    if(!(tokens[currToken].isString() && (tokens[currToken].stringValue() != "getchar" || tokens[currToken].stringValue() != "printf"))){
        std::cout << "Expected an identifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    checkParameterList();
    if(!(tokens[currToken].isChar() && (tokens[currToken].charValue() == '{'))){
        std::cout << "Expected an ( on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
//    checkCompoundStatement();
}

//parseparamlist
void Parser::checkParameterList() {
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Expected an ( on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }

    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "void"){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        if(tokens[currToken].isChar() && tokens[currToken].charValue() == ')'){
            insert(std::string(1, tokens[currToken].charValue()), false);
            currToken++;
            return;
        }else{
            std::cout << "Expected an ) on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
    }
    while(!(tokens[currToken].isChar() && tokens[currToken].charValue() != ')')){
        if(tokens[currToken].isString()){
            insert(tokens[currToken].stringValue(), false);
        }else{
            insert(std::string(1, tokens[currToken].charValue()), false);
        }
    }
    symbolTable.tail()->addParameter( paramListHead );
}

bool Parser::parseProgram() {
    if(currToken == tokens.size()){
        return true;
    }
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "function"){
        parseFunctionDeclaration(true);
        parseProgram();
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "procedure"){
        if(tokens[currToken+1].isString() && tokens[currToken+1].stringValue() == "main"){
            parseMainProcedure(true);
            parseProgram();
        }else{
            parseProcedureDeclaration(true);
            parseProgram();
        }
    }else if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "bool" || tokens[currToken].stringValue() == "int")){
        parseDeclarationStatement(false);
        parseProgram();
    }else{
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + "Expected function or procedure";
    }
    return true;
}

bool Parser::parseMainProcedure(bool error) {
    /* change - Dawson */
    parserScope++;

    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "procedure")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected procedure in main";
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;

    /* change - Dawson */
    currSymbolTableNode = new SymbolTableNode();
    currSymbolTableNode->setScope( parserScope );
    currSymbolTableNode->setProcedureName( tokens[currToken].stringValue() );

    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "main")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected main in main";
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected (";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "void")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected void in main parameter list";
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == ')')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected )";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '{')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected {";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;

    /* change - Dawson */
    symbolTable.addNode( currSymbolTableNode );
    currSymbolTableNode = nullptr;

    parseCompoundStatement(true);//should be block-----------------------------------------------------------------------------------------------------
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;
    return true;
}

bool Parser::parseProcedureDeclaration( bool error) {

    /* change - Dawson */
    parserScope++;

    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "procedure")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected procedure in main";
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;

    /* change - Dawson */
    currSymbolTableNode = new SymbolTableNode();
    currSymbolTableNode->setScope( parserScope );
    currSymbolTableNode->setProcedureName( tokens[currToken].stringValue() );

    if(!(tokens[currToken].isString())){
        std::cout << "Expected an identifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    if(tokens[currToken].stringValue() == "getchar"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : getchar is a reserved identifier";
        exit(2);
    }
    if(tokens[currToken].stringValue() == "printf"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : printf is a reserved identifier";
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected (";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;

    if(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"){
        parseParameterList(true);
    }else if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "void")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected void in parameter list";
        exit(2);
    }else{
        insert(tokens[currToken].stringValue(), true);
        currToken++;
    }
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == ')')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected )";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '{')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected {";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;

    /* change - Dawson */
    symbolTable.addNode( currSymbolTableNode );
    currSymbolTableNode = nullptr;

    parseCompoundStatement(true);//should be block -----------------------------------------------------------------------------------------------------
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;
    return true;
}

bool Parser::parseFunctionDeclaration(bool error) {

    /* change - Dawson */
    parserScope++;

    if(!tokens[currToken].isString() && !(tokens[currToken].stringValue() == "function")){
        std::cout << "Expected a datatype specifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;

    /* change - Dawson */
    currSymbolTableNode = new SymbolTableNode();
    currSymbolTableNode->setScope( parserScope );
    currSymbolTableNode->setFunctionReturnDataType( tokens[currToken].stringValue() );

    if(!tokens[currToken].isString() && !(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool")){
        std::cout << "Expected a datatype specifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;

    /* change - Dawson */
    currSymbolTableNode->setFunctionName( tokens[currToken].stringValue() );

    if(!(tokens[currToken].isString())){
        std::cout << "Expected an identifier on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    if(tokens[currToken].stringValue() == "getchar"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : getchar is a reserved identifier";
        exit(2);
    }
    if(tokens[currToken].stringValue() == "printf"){
        std::cout << "Sytax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + " : printf is a reserved identifier";
        exit(2);
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '(')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected (";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    if(tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool"){
        parseParameterList(true);
    }else if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "void")){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected void in main parameter list";
        exit(2);
    }else{
        insert(tokens[currToken].stringValue(), true);
        currToken++;
    }
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == ')')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected )";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '{')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected {";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;

    /* change - Dawson */
    symbolTable.addNode( currSymbolTableNode );
    currSymbolTableNode = nullptr;

    parseCompoundStatement(true);//block statement-----------------------------------------------------------------------------------------------------
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;

    return true;
}

bool Parser::parseParameterList(bool error) {
    int savedIdx = currToken;

    /* change - Dawson */
    if( paramListHead == nullptr ) {
        paramListHead = paramListTail = new SymbolTableNode();
        paramListTail->setScope( currSymbolTableNode->getScope() );
        paramListTail->setVariableDataType( tokens[currToken].stringValue() );
    } else {
        SymbolTableNode *curr = new SymbolTableNode();
        curr->setScope( currSymbolTableNode->getScope() );
        paramListTail->next( curr );
        paramListTail = curr;
        paramListTail->setVariableDataType( tokens[currToken].stringValue() );
    }

    currToken = savedIdx;
    if(parseDatatypeSpecifier(false)){

        /* change - Dawson */
        if( tokens[currToken].isString() ) {
            paramListTail->setVariableName( tokens[currToken].stringValue() );
        } else if( tokens[currToken].isChar() ) {
            paramListTail->setVariableName( std::string{ tokens[currToken].charValue() } );
        }

        //AAAAAAAAHHHHHHHHHHHHHHH - my internal monologue currently

        if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "bool" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "void")){
            std::cout << "Syntax error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": reserved word " + tokens[currToken].stringValue() + " cannot be used for the name of a variable";
            exit(2);
        }
        if(parseIdentifierArrayList(false) || parseIdentifier(false)){
            savedIdx = currToken;

            /* change - Dawson */
            if( currSymbolTableNode != nullptr && ( currSymbolTableNode->isFunction() || currSymbolTableNode->isProcedure() ) ) {
                currSymbolTableNode->addParameter( paramListHead );
                paramListHead = paramListTail = nullptr;
            }

            if(parseComma()){
                if(parseParameterList(false)){
                    return true;
                }
                return false;
            }
            deleteRange(currToken-savedIdx);
            currToken = savedIdx;
            return true;
        }else if(error){
            std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected Identifier in the parameter list";
            exit(2);
        }
    }else if(error){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected Datatype specifier in the parameter list";
        exit(2);
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

bool Parser::parseCompoundStatement(bool error) {
    //block of code refers to this
    //while not end of block, read statements
    while(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        parseStatement(true);
    }
    return true;
}

bool Parser::parseStatement(bool error) {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "return"){
        parseReturnStatement(true);
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "printf"){
        parsePrintfStatement(true);
    }else if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "for" || tokens[currToken].stringValue() == "while")){ //should be for iteration statement
        parseIterationStatement(true);
    }else if(tokens[currToken].isString() && tokens[currToken].stringValue() == "if"){
        parseSelectionStatement(true);
    }else if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "bool")){
        parseDeclarationStatement(true);
    }else if(tokens[currToken].isString() || tokens[currToken].isChar()){
        int savedIdx = currToken;
        if(parseUserDefinedFunction(false) && tokens[currToken].isChar() && tokens[currToken].charValue() == ';'){
            insert(std::string(1, tokens[currToken].charValue()), false);
            currToken++;
            return true;
        }
        deleteRange(currToken-savedIdx);
        currToken = savedIdx;
        parseAssignmentStatement(true);
    }else if(error){
        std::cout << "Expected Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }else{
        return false;
    }
    return true;
}



bool Parser::parseReturnStatement(bool error) {
    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "return")){
        return false;
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    int savedIdx = currToken;
    if (parseExpression(false)) { //return <EXPRESSION> <SEMICOLON>
        if(!parseSemicolon()){
            if(error){
                std::cout << "Expected Semicolon at end of expression. failed on line " + std::to_string(tokens[currToken].getLineNumber());
                exit(2);
            }else{
                deleteRange(currToken-savedIdx);
                currToken = savedIdx;
                return false;
            }
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if (parseSingleQuotedStr(false)){ //return <SINGLE_QUOTED_STRING> <SEMICOLON>
        if(!parseSemicolon()){
            if(error){
                std::cout << "Expected Semicolon at end of expression. failed on line " + std::to_string(tokens[currToken].getLineNumber());
                exit(2);
            }else{
                return false;
            }
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if (parseDoubleQuotedStr(false)) { //return <DOUBLE_QUOTED_STRING> <SEMICOLON>
        if(!parseSemicolon()){
            if(error){
                std::cout << "Expected Semicolon at end of expression. failed on line " + std::to_string(tokens[currToken].getLineNumber());
                exit(2);
            }else{
                return false;
            }
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}



bool Parser::parseDeclarationStatement(bool error) {
    int savedIdx = currToken;
    int savedScope = parserScope;

    //somehow need to change scope if the declaration is not withing a function or procedure (Test 4 highlights this issue)

    /* change - Dawson */
    currSymbolTableNode = new SymbolTableNode();
    currSymbolTableNode->setScope( parserScope );
    currSymbolTableNode->setVariableDataType( tokens[currToken].stringValue() );

    if (parseDatatypeSpecifier(false)) {
        if(error && tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "bool" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "void")){
            std::cout << "Syntax error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": reserved word " + tokens[currToken].stringValue() + " cannot be used for the name of a variable";
            exit(2);
        }

        /* change - Dawson */
        if( tokens[currToken].isChar() ) {
            currSymbolTableNode->setVariableName( std::string{tokens[currToken].charValue()} );
        } else if( tokens[currToken].isString() ) {
            currSymbolTableNode->setVariableName( tokens[currToken].stringValue() );
        }


        if(parseIdentifierArrayList(false) || parseIdentifierList(false)) {
            if (tokens[currToken].charValue() == ';') {

                /*change - Dawson */
                symbolTable.addNode( currSymbolTableNode );
                currSymbolTableNode = nullptr;

                insert(std::string(1, tokens[currToken].charValue()), false);
                currToken++;
                return true;
            }
        }
        //Dont think code should ever get here
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }

    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(error){
        std::cout << "Syntax Error on line " + std::to_string(tokens[currToken].getLineNumber()) + "Not good declaration";
        exit(2);
    }

    return false;
}

bool Parser::parseUserDefinedFunction(bool error) {//<DATATYPE_SPECIFIER> <IDENTIFIER><SEMICOLON> | <DATATYPE_SPECIFIER><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <SEMICOLON>
    int savedIdx = currToken;
    if(!parseIdentifier(false)){
        return false;
    }
    if(!parseLParenthesis()){
        deleteRange(1);
        currToken--;
        return false;
    }
    if (!parseIdentifierAndIdentifierArrayList(false)){
        deleteRange(currToken-savedIdx);
        currToken = savedIdx;
        if(!parseExpression(false)){
            deleteRange(currToken-savedIdx);
            currToken = savedIdx;
            return false;
        }
    }
    if (parseRParenthesis()) {
        return true;
    }
    if(error){
        std::cout << "Expected User defined Function. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//<IDENTIFIER> <L_PAREN><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <R_PAREN> | <IDENTIFIER><L_PAREN> <EXPRESSION> <R_PAREN>
bool Parser::parseGetcharFunction(bool error) {
    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "getChar")){
        return false;
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    int savedIdx = currToken;
    if (tokens[currToken].charValue() == '(') {
        insert(std::string(1, tokens[currToken].charValue()), false);
        currToken++;
        if (parseIdentifierAndIdentifierArrayList(false) && tokens[currToken].charValue() == ')') {
            insert(std::string(1, tokens[currToken].charValue()), true);
            currToken++;
            return true;
        }
        else if (parseExpression(false) && tokens[currToken].charValue() == ')') {
            insert(std::string(1, tokens[currToken].charValue()), true);
            currToken++;
            return true;
        }
    } else if(error) {
        std::cout << "Expected getChar function. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//printf <L_PAREN> <DOUBLE_QUOTED_STRING> <R_PAREN><SEMICOLON> |
//printf <L_PAREN> <SINGLE_QUOTED_STRING> <R_PAREN><SEMICOLON> |
//printf <L_PAREN> <DOUBLE_QUOTED_STRING> <COMMA><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <R_PAREN> <SEMICOLON> |
//printf<L_PAREN> <SINGLE_QUOTED_STRING> <COMMA><IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <R_PAREN> <SEMICOLON>
bool Parser::parsePrintfStatement(bool error) {
    if(!(tokens[currToken].isString() && tokens[currToken].stringValue() == "printf")){
        return false;
    }
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    int savedIdx = currToken;
    if (parseLParenthesis() && parseDoubleQuotedStr(false) && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if (parseLParenthesis() && parseSingleQuotedStr(false) && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if (parseLParenthesis() && parseDoubleQuotedStr(false) && parseComma() && parseIdentifierAndIdentifierArrayList(false) && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if (parseLParenthesis() && parseSingleQuotedStr(false) && parseComma() && parseIdentifierAndIdentifierArrayList(false) && parseRParenthesis() && parseSemicolon()) {
        return true;
    }
    if(error){
        std::cout << "Expected printf function. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    deleteRange(currToken-savedIdx+1);
    currToken = savedIdx - 1;
    return false;
}

//<IDENTIFIER> <ASSIGNMENT_OPERATOR><EXPRESSION> <SEMICOLON> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR><SINGLE_QUOTED_STRING> <SEMICOLON> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR> <DOUBLE_QUOTED_STRING> <SEMICOLON>
bool Parser::parseAssignmentStatement(bool error) {
    int savedIdx = currToken;
    if(error && tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "bool" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "void")){
        std::cout << "Syntax error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": reserved word " + tokens[currToken].stringValue() + " cannot be used for the name of a variable";
        exit(2);
    }
    if ((parseIdentifierArrayList(false) || parseIdentifier(false)) && tokens[currToken].charValue() == '=') {
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        int savedIdx2 = currToken;
        if (parseSingleQuotedStr(false) && tokens[currToken].charValue() == ';') {
            insert(std::string(1, tokens[currToken].charValue()), false);
            currToken++;
            return true;
        }
        deleteRange(currToken-savedIdx2);
        currToken = savedIdx2;
        if (parseDoubleQuotedStr(false) && tokens[currToken].charValue() == ';') {
            insert(std::string(1, tokens[currToken].charValue()), false);
            currToken++;
            return true;
        }
        deleteRange(currToken-savedIdx2);
        currToken = savedIdx2;
        int currLine = tokens[currToken].getLineNumber();
        if (parseExpression(false) ){

            //this is assuming that there wont be a declaration like:
            // int a =
            //       10;

            while(tokens[currToken].getLineNumber() == currLine && tokens[currToken].charValue() != ';'){
                //this is where we want to add every element to the cst,
                //we currently just want it to move along
                if(tokens[currToken].isChar()){
                    insert(std::string(1, tokens[currToken].charValue()), true);
                }else if (tokens[currToken].isString()) {
                    insert(tokens[currToken].stringValue(), true);
                }else if (tokens[currToken].isInt()){
                    insert(std::to_string(tokens[currToken].intValue()), true);
                }
                currToken++;
            }
            if(tokens[currToken].isChar() && tokens[currToken].charValue() == ';'){
                insert(std::string(1, tokens[currToken].charValue()), false);
                currToken++;
                return true;
            }
        }
        deleteRange(savedIdx2-currToken);
        currToken = savedIdx2;
        if (parseUserDefinedFunction(false) && tokens[currToken].charValue() == ';'){
            insert(std::string(1, tokens[currToken].charValue()), false);
            currToken++;
            return true;
        }
        else if(error){
            std::cout << "Expected string or expression. failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        deleteRange(savedIdx2-currToken);
        currToken = savedIdx2;
        return false;
    }
    else if(error){
        std::cout << "Expected assignment Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//for <L_PAREN> <INITIALIZATION_EXPRESSION><SEMICOLON> <BOOLEAN_EXPRESSION> <SEMICOLON> <EXPRESSION> <R_PAREN><STATEMENT> |
//for <L_PAREN> <INITIALIZATION_EXPRESSION> <SEMICOLON><BOOLEAN_EXPRESSION> <SEMICOLON> <EXPRESSION> <R_PAREN><BLOCK_STATEMENT> |
//while <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><STATEMENT> |
//while <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN><BLOCK_STATEMENT>
bool Parser::parseIterationStatement(bool error) {
    //cannot assume for or while were parsed
    if (tokens[currToken].stringValue() == "for") {
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        if (error && tokens[currToken].charValue() != '(') {
            std::cout << "Expected ( . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        if (error && !parseInitializationExpression(false)) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        if (error && tokens[currToken].charValue() != ';') {
            std::cout << "Expected Semi-Colon . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        if (error && !parseBooleanExpression(false)) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        if (error && tokens[currToken].charValue() != ';') {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        if(parseIdentifier(false)){
            if(tokens[currToken].isChar() && tokens[currToken].charValue() == '='){
                insert(std::string(1, tokens[currToken].charValue()), true);
                currToken++;
            }else{
                deleteRange(1);
                currToken--;
            }
        }
        if (error && !parseExpression(false)) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        if (error && tokens[currToken].charValue() != ')') {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), false);
        currToken++;
        if (tokens[currToken].charValue() == '{') {
            parseBlockStatement(true);
        }
        else {
            parseStatement(true);
        }
        inForLoop = false;
        return true;

    }
    else if (tokens[currToken].stringValue() == "while") {
        currToken++;
        insert("while", true);
        if (tokens[currToken].charValue() != '(') {
            std::cout << "Expected ( . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        if (!parseBooleanExpression(false)) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        if (tokens[currToken].charValue() != ')') {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), false);
        currToken++;
        if (tokens[currToken].stringValue() != "{") {
            parseBlockStatement(false);
        }
        else {
            parseStatement(false);
        }
        return true;
    }
    else {
        std::cout << "Expected loop. failed on line " + std::to_string(tokens[currToken].getLineNumber());
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
bool Parser::parseSelectionStatement(bool error) {
    if (tokens[currToken].stringValue() == "if") {
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        if (tokens[currToken].charValue() != '(') {
            std::cout << "Expected ( . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        if (!parseBooleanExpression(false)) {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        if (tokens[currToken].charValue() != ')') {
            std::cout << "Expected Bool Expression . Failed on line " + std::to_string(tokens[currToken].getLineNumber());
            exit(2);
        }
        insert(std::string(1, tokens[currToken].charValue()), false);
        currToken++;
        if (tokens[currToken].charValue() == '{') {
            parseBlockStatement(true);
        }
        else {
            parseStatement(true);
        }
        if (tokens[currToken].stringValue() == "else") {
            insert(tokens[currToken].stringValue(), false);
            currToken++;
            if (tokens[currToken].charValue() == '{') {
                parseBlockStatement(true);
            }
            else {
                parseStatement(true);
            }
        }
        return true;
    }
    else if(error){
        std::cout << "Expected Return Statement. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    return false;
}

//<BOOLEAN_EXPRESSION> | <NUMERICAL_EXPRESSION>
bool Parser::parseExpression(bool error) {
    int savedIdx = currToken;
    if(parseNumericalExpression(false)){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if (parseBooleanExpression(false)) {//would not work pls
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//<IDENTIFIER> <ASSIGNMENT_OPERATOR><EXPRESSION> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR><SINGLE_QUOTED_STRING> |
//<IDENTIFIER> <ASSIGNMENT_OPERATOR><DOUBLE_QUOTED_STRING>
bool Parser::parseInitializationExpression(bool error) {
    if (!(parseIdentifier(false) && tokens[currToken].charValue() == '=')) {
        std::cout << "Expected Init Expression. failed on line " + std::to_string(tokens[currToken].getLineNumber());
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    int savedIdx = currToken;
    if(parseSingleQuotedStr(false)){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseDoubleQuotedStr(false)){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseExpression(false)){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
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
bool Parser::parseBooleanExpression(bool error) {
    if(parseBooleanNot()){
        return parseBooleanExpression(false);
    }
    if(parseBooleanTrue() || parseBooleanFalse()){
        if(parseBooleanOperator(error)){
            return parseBooleanExpression(error);
        }
        return true;
    }
    int savedIdx = currToken;
    if(parseIdentifier(false) && (parseBooleanEqual() || parseBooleanNotEqual() || parseLT() ||parseLTequal() || parseGT() || parseGTequal()) && parseSingleQuotedStr(false)){
        if(parseBooleanOperator(error)){
            return parseBooleanExpression(error);
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseIdentifier(false) && (parseBooleanEqual() || parseBooleanNotEqual() || parseLT() ||parseLTequal() || parseGT() || parseGTequal()) && parseDoubleQuotedStr(false)){
        if(parseBooleanOperator(error)){
            return parseBooleanExpression(error);
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseNumericalExpression(false)){
        if(parseBooleanEqual() || parseBooleanNotEqual() || parseLT() ||parseLTequal() || parseGT() || parseGTequal()){
            if(parseNumericalExpression(false)){
                if(parseBooleanOperator(error)){
                    return parseBooleanExpression(error);
                }
                return true;
            }else if(error){
                std::cout << "Error in bool expression.";
                exit(2);
            }
            deleteRange(currToken-savedIdx);
            currToken = savedIdx;
            return false;
        }
        deleteRange(currToken-savedIdx);
        currToken = savedIdx;
        if(parseIdentifierArrayList(false) || parseIdentifier(false)){
            if(parseBooleanOperator(error)){
                return parseBooleanExpression(error);
            }
            if(parseBooleanEqual() || parseBooleanNotEqual() || parseLT() ||parseLTequal() || parseGT() || parseGTequal()){
                if(parseSingleQuotedStr(false)){
                    if(parseBooleanOperator(error)){
                        return parseBooleanExpression(error);
                    }
                    return true;
                }
                return parseBooleanExpression(error);
            }
            if(parseLParenthesis()){
                if(parseIdentifier(false)){
                    if(parseRParenthesis()){
                        return true;
                    }
                    return true;
                }
                return parseBooleanExpression(error);
            }
            return true;
        }
        deleteRange(currToken-savedIdx);
        currToken = savedIdx;
        return false;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseLParenthesis() && parseBooleanExpression(false) && parseRParenthesis()){
        if(parseBooleanOperator(error)){
            return parseBooleanExpression(error);
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseBooleanExpression(false) && parseBooleanOperator(false) && parseBooleanExpression(false)){
        if(parseBooleanOperator(error)){
            return parseBooleanExpression(error);
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}


//<NUMERICAL_OPERAND> | <L_PAREN><NUMERICAL_OPERAND> <R_PAREN> |
//<NUMERICAL_OPERAND><NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> |
//<L_PAREN><NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION><R_PAREN> |
//<NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN><NUMERICAL_EXPRESSION> <R_PAREN> <NUMERICAL_OPERAND><NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> |
//<L_PAREN><NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION><R_PAREN> |
//<NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN><NUMERICAL_EXPRESSION> <R_PAREN>
bool Parser::parseNumericalExpression(bool error) {
    int savedIdx = currToken;
    if ( parseLParenthesis() ) {
        if( parseNumericalOperand(false) ) {
            if( parseRParenthesis() ) {
                if(parseNumericalOperand(false)){
                    if(parseNumericalExpression(false)){
                        return true;
                    }
                    deleteRange(currToken-savedIdx);
                    currToken = savedIdx;
                    return false;
                }
                return true;                                        //<L_PAREN> <NUMERICAL_OPERAND> <R_PAREN>
            }
            if( parseNumericalOperator(false) ) {
                if( parseNumericalExpression(false) ) {
                    if( parseRParenthesis() ) {
                        if(parseNumericalOperand(false)){
                            if(parseNumericalExpression(false)){
                                return true;
                            }
                            deleteRange(currToken-savedIdx);
                            currToken = savedIdx;
                            return false;
                        }
                        return true;                              //<L_PAREN> <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> <R_PAREN>
                    }
                    deleteRange(currToken-savedIdx);
                    currToken = savedIdx;
                    return false;
                }
                deleteRange(currToken-savedIdx);
                currToken = savedIdx;
                return false;
            }
            deleteRange(currToken-savedIdx);
            currToken = savedIdx;
            return false;
        }
        deleteRange(currToken-savedIdx);
        currToken = savedIdx;
        return false;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseNumericalOperand(false) ) {
        if( parseNumericalOperator(false) ) {
            if( parseNumericalExpression(false) ) {
                if( parseNumericalOperator(false) ) {
                    if(parseNumericalExpression(false)){
                        return true;
                    }
                    deleteRange(currToken-savedIdx);
                    currToken = savedIdx;
                    return false;
                }
                return true;                                        //<NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION>
            }
            deleteRange(currToken-savedIdx);
            currToken = savedIdx;
            return false;
        }
        return true;                                                //<NUMERICAL_OPERAND>
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//<LT> | <LT_EQUAL> | <GT> | <GT_EQUAL> |<BOOLEAN_EQUAL> | <BOOLEAN_NOT_EQUAL>
bool Parser::parseRelationalExpression(bool error) {
    if (tokens[currToken].isChar() && (tokens[currToken].charValue() == '<' || tokens[currToken].charValue() == '>')) {
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    if (tokens[currToken].isString() && (tokens[currToken].stringValue() == "<=" || tokens[currToken].stringValue() == ">=" || tokens[currToken].stringValue() == "==" || tokens[currToken].stringValue() == "!=")) {
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

//<BOOLEAN_EQUAL> | <BOOLEAN_NOT_EQUAL>
bool Parser::parseEqualityExpression(bool error) {
    if(parseBooleanEqual() || parseBooleanNotEqual()){
        return true;
    }
    return false;
}

//<BOOLEAN_AND_OPERATOR> | <BOOLEAN_OR_OPERATOR>
bool Parser::parseBooleanOperator(bool error) {
    if(parseBooleanOr() || parseBooleanAnd()){
        return true;
    }
    return false;
}

//<PLUS> | <MINUS> | <ASTERISK> | <DIVIDE> |<MODULO> | <CARET>
bool Parser::parseNumericalOperator(bool error) {
    if( parsePlus() ) {
        return true;
    } else if( parseMinus() ) {
        return true;
    } else if( parseAsterisk() ) {
        return true;
    } else if( parseDivide() ) {
        return true;
    } else if( parseModulo() ) {
        return true;
    } else if( parseCaret() ) {
        return true;
    }
    return false;
}

//<IDENTIFIER> | <INTEGER> | <GETCHAR_FUNCTION> |<USER_DEFINED_FUNCTION> | <SINGLE_QUOTE> <CHARACTER> <SINGLE_QUOTE> |
//<SINGLE_QUOTE> <ESCAPED_CHARACTER> <SINGLE_QUOTE> | <DOUBLE_QUOTE><CHARACTER> <DOUBLE_QUOTE> | <DOUBLE_QUOTE> <ESCAPED_CHARACTER>< DOUBLE_QUOTE
bool Parser::parseNumericalOperand(bool error) {
    if(tokens[currToken].isInt()){
        insert(std::to_string(tokens[currToken].intValue()), true);
        currToken++;
        return true;
    }
    int savedIdx = currToken;
    if(parseGetcharFunction(false)){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseUserDefinedFunction(false)){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseSingleQuote() && parseCharacter() && parseSingleQuote()){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseSingleQuote() && parseEscapeCharacter() && parseSingleQuote()){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseDoubleQuote() && parseCharacter() && parseDoubleQuote()){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseDoubleQuote() && parseCharacter() && parseDoubleQuote()){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseDoubleQuote() && parseEscapeCharacter() && parseDoubleQuote()){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseIdentifier(false)){
        return true;
    }
    return false;
}

//char | bool | int
bool Parser::parseDatatypeSpecifier(bool error) {
    if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "bool" || tokens[currToken].stringValue() == "int")){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

//<IDENTIFIER_LIST> |<IDENTIFIER_ARRAY_LIST> | <IDENTIFIER_LIST> <IDENTIFIER_ARRAY_LIST> |<IDENTIFIER_ARRAY_LIST> < IDENTIFIER_LIST
bool Parser::parseIdentifierAndIdentifierArrayList(bool error) {
    int savedIdx = currToken;
    if(parseIdentifierArrayList(false)){
        if(parseIdentifierList(false)){
            return true;
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseIdentifierList(false)){
        if(parseIdentifierArrayList(false)){
            return true;
        }
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//<IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER><R_BRACKET> | <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET><COMMA> <IDENTIFIER_ARRAY_LIST>
bool Parser::parseIdentifierArrayList(bool error) {
    int savedIdx = currToken;
    if( parseIdentifier(false) ) {
        if( parseLBracket() ) {

            /* change - Dawson */
            if( currSymbolTableNode != nullptr && !currSymbolTableNode->isFunction() && !currSymbolTableNode->isProcedure() ) {
                currSymbolTableNode->setDataTypeIsArray( true );
                currSymbolTableNode->setArraySize( tokens[currToken].intValue() );
            }
            if( currSymbolTableNode != nullptr && ( currSymbolTableNode->isFunction() || currSymbolTableNode->isProcedure() ) ) {
                if( paramListTail != nullptr ) {
                    paramListTail->setDataTypeIsArray( true );
                    paramListTail->setArraySize( tokens[currToken].intValue() );
                } else {
                    std::cout << "Error: Check Parser::parseIdentifierArrayList function. Terminating...";
                    exit(3);
                }
            }

            if( parseWholeNum(false) || parseIdentifier(false)) {
                if(tokens[currToken-1].isInt() && tokens[currToken-1].intValue() < 0){
                    std::cout << "Syntax Error on line " + std::to_string(tokens[currToken-1].getLineNumber()) + ": Array declaration must use a positive number";
                    exit(2);
                }
                if( parseRBracket() ) {
                    savedIdx = currToken;
                    if( parseComma() ) {

                        /* change - Dawson */
                        if( currSymbolTableNode != nullptr && !currSymbolTableNode->isFunction() && !currSymbolTableNode->isProcedure() ) {
                            symbolTable.addNode( currSymbolTableNode );
                            std::string tempDataType = currSymbolTableNode->getVariableDataType();
                            currSymbolTableNode = nullptr;
                            currSymbolTableNode = new SymbolTableNode();
                            currSymbolTableNode->setVariableDataType( tempDataType );
                            if( tokens[currToken].isString()) {
                                currSymbolTableNode->setVariableName( tokens[currToken].stringValue() );
                            } else if( tokens[currToken].isChar() ) {
                                currSymbolTableNode->setVariableName( std::string{ tokens[currToken].charValue() } );
                            }
                        }



                        if( parseIdentifierArrayList(false) ) {
                            return true;
                        }
                        deleteRange(currToken-savedIdx);
                        currToken = savedIdx;
                        return false;
                    }
                    deleteRange(currToken-savedIdx);
                    currToken = savedIdx;
                    return true;
                }
                deleteRange(currToken-savedIdx);
                currToken = savedIdx;
                return false;
            }
            deleteRange(currToken-savedIdx);
            currToken = savedIdx;
            return false;
        }
        deleteRange(currToken-savedIdx);
        currToken = savedIdx;
        return false;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//<IDENTIFIER> | <IDENTIFIER> <COMMA> |<IDENTIFIER_LIST>
bool Parser::parseIdentifierList(bool error) {
    int savedIdx = currToken;
    if(tokens[currToken].isString() && (tokens[currToken].stringValue() == "char" || tokens[currToken].stringValue() == "bool" || tokens[currToken].stringValue() == "int" || tokens[currToken].stringValue() == "void")){
        std::cout << "Syntax error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": reserved word " + tokens[currToken].stringValue() + " cannot be used for the name of a variable";
        exit(2);
    }

    // change - Dawson: had to split up the if statement into 3 parts for symbol table
    if(parseIdentifier(false)){
        if( parseComma() ) {

            /* change - Dawson */
            if( currSymbolTableNode != nullptr ) {
                symbolTable.addNode( currSymbolTableNode );
                std::string tempDataType = currSymbolTableNode->getVariableDataType();
                currSymbolTableNode = nullptr;
                currSymbolTableNode = new SymbolTableNode();
                currSymbolTableNode->setScope( parserScope );
                currSymbolTableNode->setVariableDataType( tempDataType );
                if( tokens[currToken].isString()) {
                    currSymbolTableNode->setVariableName( tokens[currToken].stringValue() );
                } else if( tokens[currToken].isChar() ) {
                    currSymbolTableNode->setVariableName( std::string{ tokens[currToken].charValue() } );
                }
            }

            savedIdx = currToken;
            if( parseIdentifierList(false) ) {
                return true;
            }
        }
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    if(parseIdentifier(false)){
        return true;
    }
    deleteRange(currToken-savedIdx);
    currToken = savedIdx;
    return false;
}

//<LETTER_UNDERSCORE> | <LETTER_UNDERSCORE><LETTER_DIGIT_UNDERSCORE> | <LETTER_UNDERSCORE><LETTER_DIGIT_UNDERSCORE> <IDENTIFIER>
bool Parser::parseIdentifier(bool error) {
    if(tokens[currToken].isString()){
        for(int i = 0; i < tokens[currToken].stringValue().length(); i++){
            if(!(isalnum(tokens[currToken].stringValue()[i]) || tokens[currToken].stringValue()[i] == '_')){
                return false;
            }
        }
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }else if(tokens[currToken].isChar()){
        if(isalnum(tokens[currToken].charValue()) || tokens[currToken].charValue() == '_'){
            insert(std::string(1, tokens[currToken].charValue()), true);
            currToken++;
            return true;
        }
    }
    return false;
}

//<WHOLE_NUMBER> | <PLUS> <WHOLE_NUMBER> | <MINUS><WHOLE_NUMBER>
bool Parser::parseInteger(bool error) {
    if(tokens[currToken].isInt()){
        insert(std::to_string(tokens[currToken].intValue()), true);
        currToken++;
        return true;
    }
    return false;
}

//<DIGIT> | <DIGIT> <WHOLE_NUMBER>
bool Parser::parseWholeNum(bool error) {
    if(tokens[currToken].isInt()){
        insert(std::to_string(tokens[currToken].intValue()), true);
        currToken++;
        return true;
    }
    return false;
}


//<SINGLE_QUOTE> <STRING> <SINGLE_QUOTE>
bool Parser::parseSingleQuotedStr(bool error) {
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '\'')){
        return false;
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    // parseString(); it must be a char so it will be one char
    if(!tokens[currToken].isString()){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
    } else{
        parseString();

    }
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '\'')){
        deleteRange(2);
        currToken -= 2;
        return false;
    }else if(error){
        std::cout << "error in single string";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    return true;
}

//<DOUBLE_QUOTE> <STRING> <DOUBLE_QUOTE>
bool Parser::parseDoubleQuotedStr(bool error) {
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '"')){
        return false;
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    parseString();
    if(currToken <= tokens.size() && !(tokens[currToken].isChar() && tokens[currToken].charValue() == '"')){
        deleteRange(2);
        currToken -= 2;
        return false;
    }else if(error){
        std::cout << "error in double string";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    return true;
}

//<CHARACTER | <ESCAPED_CHARACTER> | <CHARACTER> <STRING> |<ESCAPED_CHARACTER> <STRING>
bool Parser::parseString() {
    insert(tokens[currToken].stringValue(), true);
    currToken++;
    return true;
}

bool Parser::parseLetterDigitUnderscore(bool error) {
    if(tokens[currToken].isInt()){
        insert(std::to_string(tokens[currToken].intValue()), true);
        currToken++;
        return true;
    }
    if(!tokens[currToken].isChar()){
        insert(std::string(1, tokens[currToken].charValue()), true);
        return false;
    }
    if(tokens[currToken].isChar()){
        if(tokens[currToken].charValue() != '_' || !isalnum(tokens[currToken].charValue())){
            return false;
        }
    }
    insert(std::string(1, tokens[currToken].charValue()), true);
    currToken++;
    return true;
}

bool Parser::parseBooleanFalse() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "FALSE"){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanTrue() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "TRUE"){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanNotEqual() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "!="){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanEqual() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "=="){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanNot() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '!'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanOr() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "||"){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBooleanAnd() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "&&"){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseGTequal() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == ">="){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLTequal() {
    if(tokens[currToken].isString() && tokens[currToken].stringValue() == "<="){
        insert(tokens[currToken].stringValue(), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseGT() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '>'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLT() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '<'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseCaret() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '^'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseModulo() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '%'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseDivide() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '/'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseAsterisk() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '*'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseMinus() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '-'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parsePlus() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '+'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseAssignmentOperator() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '='){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseComma() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ','){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseSemicolon() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ';'){
        insert(std::string(1, tokens[currToken].charValue()), false);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseSingleQuote() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '\''){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseDoubleQuote() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '"'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseRBrace() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '}'){
        insert(std::string(1, tokens[currToken].charValue()), false);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLBrace() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '{'){
        insert(std::string(1, tokens[currToken].charValue()), false);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseRParenthesis() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ')'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLParenthesis() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '('){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseRBracket() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == ']'){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseLBracket() {
    if(tokens[currToken].isChar() && tokens[currToken].charValue() == '['){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseBlockStatement(bool error) {
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '{')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected {";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;
    parseCompoundStatement(true);//block statement-----------------------------------------------------------------------------------------------------
    if(!(tokens[currToken].isChar() && tokens[currToken].charValue() == '}')){
        std::cout << "Error on line " + std::to_string(tokens[currToken].getLineNumber()) + ": Expected }";
        exit(2);
    }
    insert(std::string(1, tokens[currToken].charValue()), false);
    currToken++;
    return true;
}

bool Parser::parseEscapeCharacter() {
    if(tokens[currToken].isChar()){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}

bool Parser::parseCharacter() {
    if(tokens[currToken].isChar()){
        insert(std::string(1, tokens[currToken].charValue()), true);
        currToken++;
        return true;
    }
    return false;
}