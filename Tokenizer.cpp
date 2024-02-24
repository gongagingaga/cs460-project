#include "Tokenizer.hpp"

void Tokenizer::printTokens(){
    for(auto token : tokens){
        std::cout << "[ " << token.toString() << " ]\n";
    }
}

std::vector<Token> Tokenizer::tokenize(std::string input){
    std::vector<Token> tokens;
    std::string dqs;
    for ( long unsigned int curr = 0; curr < input.size(); curr++){
        Token newToken;
        if (input.at(curr) == ' ' || input.at(curr) == '\n'){
            continue;
        }
        switch (input[curr]) {

            case '(':
                newToken.bnfValue() = L_PAREN;
                newToken.character() = '(';
                tokens.push_back(newToken);
                break;
            case ')':
                newToken.bnfValue() = R_PAREN;
                newToken.character() = ')';
                tokens.push_back(newToken);
                break;
            case '{':
                newToken.bnfValue() = L_BRACE;
                newToken.character() = '{';
                tokens.push_back(newToken);
                break;
            case '}':
                newToken.bnfValue() = R_BRACE;
                newToken.character() = '}';
                tokens.push_back(newToken);
                break;
            case ';':
                newToken.bnfValue() = SEMICOLON;
                newToken.character() = ';';
                tokens.push_back(newToken);
                break;
            case '[':
                newToken.bnfValue() = L_BRACKET;
                newToken.character() = '[';
                tokens.push_back(newToken);
                break;
            case ']':
                newToken.bnfValue() = R_BRACKET;
                newToken.character() = ']';
                tokens.push_back(newToken);
                break;
            case ',':
                newToken.bnfValue() = COMMA;
                newToken.character() = ',';
                tokens.push_back(newToken);
                break;
            case '+':
                newToken.bnfValue() = PLUS;
                newToken.character() = '+';
                tokens.push_back(newToken);
                break;
            case '-':
                newToken.bnfValue() = MINUS;
                newToken.character() = '-';
                tokens.push_back(newToken);
                break;
            case '*':
                newToken.bnfValue() = ASTERISK;
                newToken.character() = '*';
                tokens.push_back(newToken);
                break;
            case '/':
                newToken.bnfValue() = DIVIDE;
                newToken.character() = '/';
                tokens.push_back(newToken);
                break;
            case '%':
                newToken.bnfValue() = MODULO;
                newToken.character() = '%';
                tokens.push_back(newToken);
                break;
            case '^':
                newToken.bnfValue() = CARET;
                newToken.character() = '^';
                tokens.push_back(newToken);
                break;
            case '"':
                dqs += '"';
                curr++;
                while(input[curr] != '"' && curr != input.size() && input[curr] != '\n'){
                    dqs += input[curr];
                    curr++;
                }

                dqs += '"';

                // unterminated string
                if(curr == input.size() ||  input[curr] == '\n') exit(5);

                newToken.bnfValue() = DOUBLE_QUOTED_STRING;
                newToken.quotedString() = dqs;
                tokens.push_back(newToken);
                dqs = "";
                break;

            case '\'':
                dqs += '\'';
                curr++;
                while(input[curr] != '\'' && curr != input.size() && input[curr] != '\n'){
                    dqs += input[curr];
                    curr++;
                }

                dqs += '\'';

                // unterminated string
                if(curr == input.size() || input[curr] == '\n') exit(5);

                newToken.bnfValue() = SINGLE_QUOTED_STRING;
                newToken.quotedString() = dqs;
                tokens.push_back(newToken);
                dqs = "";
                break;
            case '=':
                if(input[curr+1] == '='){
                    newToken.bnfValue() = EQUALITY_EXPRESSION;
                    newToken.booleanOperator() = "==";
                    tokens.push_back(newToken);
                    curr++;
                    break;
                }
                newToken.bnfValue() = ASSIGNMENT_OPERATOR;
                newToken.character() = '=';
                tokens.push_back(newToken);
                break;
            case '<':
                if(input[curr+1] == '='){
                    newToken.bnfValue() = LT_EQUAL;
                    newToken.booleanOperator() = "<=";
                    tokens.push_back(newToken);
                    curr++;
                    break;
                }
                newToken.bnfValue() = LT;
                newToken.booleanOperator() = "<";
                break;
            case '>':
                if(input[curr+1] == '='){
                    newToken.bnfValue() = GT_EQUAL;
                    newToken.booleanOperator() = ">=";
                    tokens.push_back(newToken);
                    curr++;
                    break;
                }
                newToken.bnfValue() = GT;
                newToken.booleanOperator() = ">";
                tokens.push_back(newToken);
                break;

            case '|':
                if(input[curr+1] == '|'){
                    newToken.bnfValue() = BOOLEAN_OR;
                    newToken.booleanOperator() = "||";
                    tokens.push_back(newToken);
                    curr++;
                    break;
                }
                newToken.bnfValue() = UNKNOWN;
                tokens.push_back(newToken);
                break;

            case '&':
                if(input[curr+1] == '&'){
                    newToken.bnfValue() = BOOLEAN_AND;
                    newToken.booleanOperator() = "&&";
                    tokens.push_back(newToken);
                    curr++;
                    break;
                }
                //maybe i should actually return an error here, check in with other about this
                newToken.bnfValue() = UNKNOWN;
                tokens.push_back(newToken); // both this and | dont have a meaning on their own i think(?)
                break;

            case '!':
                if(input[curr+1] == '='){
                    newToken.bnfValue() = BOOLEAN_NOT_EQUAL;
                    newToken.booleanOperator() = "!=";
                    tokens.push_back(newToken);
                    curr++;
                    break;
                }
                newToken.bnfValue() = BOOLEAN_NOT;
                newToken.booleanOperator() = "!";
                tokens.push_back(newToken);
                break;



                /*
                * NOTE: NOTHING BELOW HERE HAS BEEN REFACTORED TO THE TOKENIZER CLASS LAYOUT!!!
                */

            default:
                if(std::isalpha(input[curr])){
                    dqs += '"';
                    curr++;
                    while(input[curr] != ' ' && curr != input.size() && input[curr] != '\n' && isalpha(input[curr])){
                        dqs += input[curr];
                        curr++;
                    }
                    //at this point it must be a string of something, could be anything though
                    // but we need to go through and check for every possible string here
                    // this is also where we would put identifiers, but we need to check for a
                    // data type before this, which im pretty sure isn't a token
                    if(dqs == "true") {
                        tokens.push_back(std::pair<std::string, BNF>
                                                 ("!=", BNF::BOOLEAN_NOT_EQUAL));
                        break;
                    }
                    else if(dqs == "false"){
                        tokens.push_back(std::pair<std::string, BNF>
                                                 ("!=", BNF::BOOLEAN_NOT_EQUAL));
                        break;

                    }
                }
        }
    }
    return tokens;
}
