#include "SymbolTableNode.hpp"

SymbolTableNode::SymbolTableNode() : nextNode(nullptr) {
    variableName = "";
    variableDataType = "";
    dataTypeIsArray = false;
    arraySize = 0;
    scope = 0;                  //change this??
    procedureName = "";
    functionName = "";
    functionReturnDataType = "";
    parameterListHead = nullptr;
}


/*
SymbolTableNode::SymbolTableNode( std::string varName, std::string varDataType, bool isArray, int arrSize, int varScope ){
    variableName = varName;
    variableDataType = varDataType;
    dataTypeIsArray = isArray;
    arraySize = arrSize;
    scope = varScope;
}



SymbolTableNode::SymbolTableNode( std::string procName , SymbolTableNode *paramListHead, int procScope ) {
    procedureName = procName;
    parameterListHead = paramListHead;
    scope = procScope;
    arraySize = 0;
}



SymbolTableNode::SymbolTableNode( std::string functName, std::string functRetDataType , SymbolTableNode *paramListHead, int functScope ) {
    functionName = functName;
    functionReturnDataType = functRetDataType;
    parameterListHead = paramListHead;
    scope = functScope;
    arraySize = 0;
}
*/


SymbolTableNode* SymbolTableNode::next() {
    return nextNode;
}



void SymbolTableNode::next( SymbolTableNode *node ) {
    if( node != nullptr ) {
        nextNode = node;
    } else {
        std::cout << "Tried to add a nullptr SymbolTableNode, terminating...";
        exit(3);
    }
}



bool SymbolTableNode::isVariable() {
    return !variableName.empty();
}



bool SymbolTableNode::isFunction() {
    return !functionName.empty();
}



bool SymbolTableNode::isProcedure() {
    return !procedureName.empty();
}



// Returns true if there is nothing in the parameter list, false otherwise
bool SymbolTableNode::paramListEmpty() {
    return parameterListHead == nullptr;
}



void SymbolTableNode::printNode() {
    if( isFunction() ) {
        std::cout << "IDENTIFIER_NAME: ";
        std::cout << functionName << std::endl;
        std::cout << "IDENTIFIER_TYPE: ";
        std::cout << "function" << std::endl;
        std::cout << "DATATYPE: ";
        std::cout << functionReturnDataType << std::endl;
        std::cout << "DATATYPE_IS_ARRAY: ";
        if( dataTypeIsArray ) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
        std::cout << "DATATYPE_ARRAY_SIZE: ";
        std::cout << arraySize << std::endl;
        std::cout << "SCOPE: ";
        std::cout << scope << std::endl;

    }
    else if( isProcedure() ) {
        std::cout << "IDENTIFIER_NAME: ";
        std::cout << procedureName << std::endl;
        std::cout << "IDENTIFIER_TYPE: ";
        std::cout << "procedure" << std::endl;
        std::cout << "DATATYPE: ";
        std::cout << "NOT APPLICABLE" << std::endl;
        std::cout << "DATATYPE_IS_ARRAY: ";
        std::cout << "no" << std::endl;
        std::cout << "DATATYPE_ARRAY_SIZE: ";
        std::cout << arraySize << std::endl;
        std::cout << "SCOPE: ";
        std::cout << scope << std::endl;

    }
    else if( isVariable() ) {
        std::cout << "IDENTIFIER_NAME: ";
        std::cout << variableName << std::endl;
        std::cout << "IDENTIFIER_TYPE: ";
        std::cout << "datatype" << std::endl;
        std::cout << "DATATYPE: ";
        std::cout << variableDataType << std::endl;
        std::cout << "DATATYPE_IS_ARRAY: ";
        if( dataTypeIsArray ) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
        std::cout << "DATATYPE_ARRAY_SIZE: ";
        std::cout << arraySize << std::endl;
        std::cout << "SCOPE: ";
        std::cout << scope << std::endl;

    }
    else {
        std::cout << "Invalid SymbolTableNode, not a valid type (function, procedure, variable). Terminating...";
        exit(3);
    }
}



void SymbolTableNode::printParamNode() {
    if( !isVariable() ) {
        std::cout << "SymbolTableNode::printParamNode(): Tried to print an invalid parameter. Terminating...";
        exit(3);
    }
    std::cout << "IDENTIFIER_NAME: ";
    std::cout << variableName << std::endl;
    std::cout << "DATATYPE: ";
    std::cout << variableDataType << std::endl;
    std::cout << "DATATYPE_IS_ARRAY: ";
    if( dataTypeIsArray ) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
    std::cout << "DATATYPE_ARRAY_SIZE: ";
    std::cout << arraySize << std::endl;
    std::cout << "SCOPE: ";
    std::cout << scope << std::endl;
}



std::string SymbolTableNode::getVariableName() {
    return variableName;
}

std::string SymbolTableNode::getProcedureName() {
    return procedureName;
}

std::string SymbolTableNode::getVariableDataType() {
    return variableDataType;
}

bool SymbolTableNode::getDataTypeIsArray() {
    return dataTypeIsArray;
}

int SymbolTableNode::getArraySize() {
    return arraySize;
}

int SymbolTableNode::getScope() {
    return scope;
}

std::string SymbolTableNode::getFunctionName() {
    return functionName;
}

std::string SymbolTableNode::getFunctionReturnDataType() {
    return functionReturnDataType;
}

SymbolTableNode * SymbolTableNode::getparameterList() {
    return parameterListHead;
}



void SymbolTableNode::setVariableName( std::string varName ) {
    variableName = varName;
}

void SymbolTableNode::setProcedureName( std::string procName ) {
    procedureName = procName;
}

void SymbolTableNode::setVariableDataType( std::string varDataType ) {
    variableDataType = varDataType;
}

void SymbolTableNode::setDataTypeIsArray( bool isArray ) {
    dataTypeIsArray = isArray;
}

void SymbolTableNode::setArraySize( int arrSize ) {
    arraySize = arrSize;
}

void SymbolTableNode::setScope( int symbolScope ) {
    scope = symbolScope;
}

void SymbolTableNode::setFunctionName( std::string functName ) {
    functionName = functName;
}

void SymbolTableNode::setFunctionReturnDataType( std::string functRetDataType ) {
    functionReturnDataType = functRetDataType;
}

void SymbolTableNode::addParameter( SymbolTableNode *paramNode ) {
    if( parameterListHead == nullptr ) {
        parameterListHead = parameterListTail = paramNode;
    } else {
        parameterListTail->next( paramNode );
        parameterListTail = paramNode;
    }
}



bool SymbolTableNode::isEmptyNode() {
    return !isProcedure() && !isVariable() && !isFunction();
}


