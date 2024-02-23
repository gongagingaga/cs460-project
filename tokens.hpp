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

class Token{
	public:
	std::string BNFtoString(BNF bnf){
		switch(bnf) {
			case CHARACTER:
				return "CHARACTER";
			case ESCAPED_CHARACTER:
				return "ESCAPED_CHARACTER";
			case LETTER:
				return "LETTER";
			case DIGIT:
				return "DIGIT";
			case HEX_DIGIT:
				return "HEX_DIGIT";
			case L_PAREN:
				return "L_PAREN";
			case R_PAREN:
				return "R_PAREN";
			case L_BRACKET:
				return "L_BRACKET";
			case R_BRACKET:
				return "R_BRACKET";
			case L_BRACE:
				return "L_BRACE";
			case R_BRACE:
				return "R_BRACE";
			case DOUBLE_QUOTE:
				return "DOUBLE_QUOTE";
			case SINGLE_QUOTE:
				return "SINGLE_QUOTE";
			case SEMICOLON:
				return "SEMICOLON";
			case COMMA:
				return "COMMA";
			case ASSIGNMENT_OPERATOR:
				return "ASSIGNMENT_OPERATOR";
			case PLUS:
				return "PLUS";
			case MINUS:
				return "MINUS";
			case ASTERISK:
				return "ASTERISK";
			case DIVIDE:
				return "DIVIDE";
			case MODULO:
				return "MODULO";
			case CARET:
				return "CARET";
			case LT:
				return "LT";
			case GT:
				return "GT";
			case LT_EQUAL:
				return "LT_EQUAL";
			case GT_EQUAL:
				return "GT_EQUAL";
			case BOOLEAN_AND:
				return "BOOLEAN_AND";
			case BOOLEAN_OR:
				return "BOOLEAN_OR";
			case BOOLEAN_NOT:
				return "BOOLEAN_NOT";
			case BOOLEAN_EQUAL:
				return "BOOLEAN_EQUAL";
			case BOOLEAN_NOT_EQUAL:
				return "BOOLEAN_NOT_EQUAL";
			case BOOLEAN_TRUE:
				return "BOOLEAN_TRUE";
			case BOOLEAN_FALSE:
				return "BOOLEAN_FALSE";
			case STRING:
				return "STRING";
			case DOUBLE_QUOTED_STRING:
				return "DOUBLE_QUOTED_STRING";
			case SINGLE_QUOTED_STRING:
				return "SINGLE_QUOTED_STRING";
			case LETTER_UNDERSCORE:
				return "LETTER_UNDERSCORE";
			case LETTER_DIGIT_UNDERSCORE:
				return "LETTER_DIGIT_UNDERSCORE";
			case WHOLE_NUMBER:
				return "WHOLE_NUMBER";
			case INTEGER:
				return "INTEGER";
			case IDENTIFIER:
				return "IDENTIFIER";
			case IDENTIFIER_LIST:
				return "IDENTIFIER_LIST";
			case IDENTIFIER_ARRAY_LIST:
				return "IDENTIFIER_ARRAY_LIST";
			case IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST:
				return "IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST";
			case DATATYPE_SPECIFIER:
				return "DATATYPE_SPECIFIER";
			case NUMERICAL_OPERAND:
				return "NUMERICAL_OPERAND";
			case NUMERICAL_OPERATOR:
				return "NUMERICAL_OPERATOR";
			case BOOLEAN_OPERATOR:
				return "BOOLEAN_OPERATOR";
			case EQUALITY_EXPRESSION:
				return "EQUALITY_EXPRESSION";
			case RELATIONAL_EXPRESSION:
				return "RELATIONAL_EXPRESSION";
			case NUMERICAL_EXPRESSION:
				return "NUMERICAL_EXPRESSION";
			case BOOLEAN_EXPRESSION:
				return "BOOLEAN_EXPRESSION";
			case INITIALIZATION_EXPRESSION:
				return "INITIALIZATION_EXPRESSION";
			case EXPRESSION:
				return "EXPRESSION";
			case SELECTION_STATEMENT:
				return "SELECTION_STATEMENT";
			case ITERATION_STATEMENT:
				return "ITERATION_STATEMENT";
			case ASSIGNMENT_STATEMENT:
				return "ASSIGNMENT_STATEMENT";
			case PRINTF_STATEMENT:
				return "PRINTF_STATEMENT";
			case GETCHAR_FUNCTION:
				return "GETCHAR_FUNCTION";
			case USER_DEFINED_FUNCTION:
				return "USER_DEFINED_FUNCTION";
			case DECLARATION_STATEMENT:
				return "DECLARATION_STATEMENT";
			case RETURN_STATEMENT:
				return "RETURN_STATEMENT";
			case STATEMENT:
				return "STATEMENT";
			case COMPOUND_STATEMENT:
				return "COMPOUND_STATEMENT";
			case BLOCK_STATEMENT:
				return "BLOCK_STATEMENT";
			case PARAMETER_LIST:
				return "PARAMETER_LIST";
			case FUNCTION_DECLARATION:
				return "FUNCTION_DECLARATION";
			case PROCEDURE_DECLARATION:
				return "PROCEDURE_DECLARATION";
			case MAIN_PROCEDURE:
				return "MAIN_PROCEDURE";
			case PROGRAM:
				return "PROGRAM";
			default:
				return "UNKNOWN";
		}
		return "";
	}


	//im pretty sure this has to return the tokenized objects
	std::vector<std::pair<std::string, BNF>> Tokenizer(std::string input){
		std::vector<std::pair<std::string, BNF>> tokens;	
		std::string dqs;
		for ( long unsigned int curr = 0; curr < input.size(); curr++){
			if (input.at(curr) == ' ' || input.at(curr) == '\n'){
				continue;
			}
			switch (input[curr]) {
				case '(':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::L_PAREN));
					break;
				case ')':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::R_PAREN));
					break;
				case '{':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::L_BRACE));
					break;
				case '}':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::R_BRACE));
					break;
				case ';':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::SEMICOLON));
					break;
				case '[':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::L_BRACKET));
					break;
				case ']':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::R_BRACKET));
					break;
				case ',':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::COMMA));
					break;
				case '+':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::PLUS));
					break;
				case '-':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::MINUS));
					break;
				case '*':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::ASTERISK));
					break;
				case '/':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::DIVIDE));
					break;
				case '%':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::MODULO));
					break;
				case '^':
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::CARET));
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

					tokens.push_back(std::pair<std::string, BNF>
							(dqs, BNF::DOUBLE_QUOTED_STRING));
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
					
					tokens.push_back(std::pair<std::string, BNF>
							(dqs, BNF::SINGLE_QUOTED_STRING));
					dqs = "";
					break;
				case '=':
					if(input[curr+1] == '='){
						tokens.push_back(std::pair<std::string, BNF> 
								("==", BNF::EQUALITY_EXPRESSION));
						curr++;
						break;
					}
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::ASSIGNMENT_OPERATOR));
					break;
				case '<':
					if(input[curr+1] == '='){
						tokens.push_back(std::pair<std::string, BNF>
								("<=", BNF::LT_EQUAL));
						curr++;
						break;
					}
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::LT));
					break;
				case '>':
					if(input[curr+1] == '='){
						tokens.push_back(std::pair<std::string, BNF>
								(">=", BNF::GT_EQUAL));
						curr++;
						break;
					}
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::GT));
					break;

				case '|':
					if(input[curr+1] == '|'){
						tokens.push_back(std::pair<std::string, BNF>
								("||", BNF::BOOLEAN_OR));
						curr++;
						break;
					}
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::UNKNOWN));
					break;

				case '&':
					if(input[curr+1] == '&'){
						tokens.push_back(std::pair<std::string, BNF>
								("&&", BNF::BOOLEAN_AND));
						curr++;
						break;
					}
					//maybe i should actually return an error here, check in with other about this
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::UNKNOWN)); // both this and | dont have a meaning on their own i think(?)
					break;

				case '!':
					if(input[curr+1] == '='){
						tokens.push_back(std::pair<std::string, BNF>
								("!=", BNF::BOOLEAN_NOT_EQUAL));
						curr++;
						break;
					}
					tokens.push_back(std::pair<std::string, BNF>
							(std::string(1, input[curr]), BNF::BOOLEAN_NOT));
					break;
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

	void printTokens(std::vector<std::pair<std::string, BNF>> tokens){
		for(auto token : tokens){
			std::cout << "[ " << token.first << ", " << BNFtoString(token.second) << " ]\n";
		}
	}
	std::string removeComments(std::string filename){
    // open file
    std::ifstream inFile;
    inFile.open(filename);
    if(!inFile.is_open()){
        std::cout << "File cannot be openned." << std::endl;
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


	return output;

}
};
