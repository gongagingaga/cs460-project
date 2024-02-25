//
// Created by candy on 2/24/2024.
//

#include "Token.hpp"

void Token::printValue() {
    if(_isBool){
        std::cout << std::to_string(_boolValue);
    }else if(_isChar){
        std::cout << _charValue;
    }else if(_isFloat){
        std::cout << _floatValue;
    }else if(_isInt){
        std::cout << _intValue;
    }else if(_isString){
        std::cout << _stringValue;
    }else{
        std::cout << "Invalid Token";
    }
}
