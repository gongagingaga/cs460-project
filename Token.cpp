//
// Created by candy on 2/24/2024.
//

#include "Token.hpp"
#include <ostream>
std::string Token::BNFtoString(int bnf){
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
			return "LEFT_PARENTHESIS";
		case R_PAREN:
			return "RIGHT_PARENTHESIS";
		case L_BRACKET:
			return "LEFT_BRACKET";
		case R_BRACKET:
			return "RIGHT_BRACKET";
		case L_BRACE:
			return "LEFT_BRACE";
		case R_BRACE:
			return "RIGHT_BRACE";
		case DOUBLE_QUOTE:
			return "DOUBLE_QUOTE";
		case SINGLE_QUOTE:
			return "SINGLE_QUOTE";
		case SEMICOLON:
			return "SEMICOLON";
		case COMMA:
			return "COMMA";
		case ASSIGNMENT_OPERATOR:
			return "ASSIGNMENT";
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

void Token::printValue() {
    if(_isBool){
		std::cout << "Token type: " << BNFtoString(_bnf) << std::endl ;
        std::cout << "Token:      " <<  _boolValue << std::endl;
    }else if(_isChar){
		std::cout << "Token type: " << BNFtoString(_bnf) << std::endl ;
        std::cout << "Token:      " <<  _charValue << std::endl;
    }else if(_isFloat){
		std::cout << "Token type: " << BNFtoString(_bnf) << std::endl ;
        std::cout << "Token:      " << _floatValue << std::endl;
    }else if(_isInt){
		std::cout << "Token type: " << BNFtoString(_bnf) << std::endl ;
        std::cout << "Token:      " <<  _intValue << std::endl;
    }else if(_isString){
		std::cout << "Token type: " << BNFtoString(_bnf) << std::endl ;
        std::cout << "Token:      " << _stringValue << std::endl;
    }else{
        std::cout << "Invalid token" << std::endl;
    }
}
