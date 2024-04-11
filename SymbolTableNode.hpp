#ifndef TOKENIZERPROJECT_SYMBOLTABLENODE_HPP
#define TOKENIZERPROJECT_SYMBOLTABLENODE_HPP


#include <string>
#include <iostream>

class SymbolTableNode {
public:
    SymbolTableNode();
    /*
    SymbolTableNode( std::string varName, std::string varDataType, bool isArray, int arrSize, int varScope );  //used to create a variable in Symbol Table
    SymbolTableNode( std::string procName, SymbolTableNode *paramListHead, int procScope );            //used to create a procudure in Symbol Table
    SymbolTableNode( std::string functName, std::string functRetDataType, SymbolTableNode *paramListHead, int functScope ); //used to create a function in Symbol Table
    */

    SymbolTableNode* next();
    void next( SymbolTableNode *node );

    bool isVariable();
    bool isFunction();
    bool isProcedure();
    bool paramListEmpty();

    void printNode();
    void printParamNode();

    std::string getVariableName();
    std::string getProcedureName();
    std::string getVariableDataType();
    bool getDataTypeIsArray();
    int getArraySize();
    int getScope();
    std::string getFunctionName();
    std::string getFunctionReturnDataType();
    SymbolTableNode * getparameterList();

    void setVariableName( std::string varName );
    void setProcedureName( std::string procName );
    void setVariableDataType( std::string varDataType );
    void setDataTypeIsArray( bool isArray );
    void setArraySize( int arrSize );
    void setScope( int symbolScope );
    void setFunctionName( std::string functName );
    void setFunctionReturnDataType( std::string functRetDataType );
    void addParameter( SymbolTableNode *paramNode );

    bool isEmptyNode();
private:
    SymbolTableNode *nextNode;

    std::string variableName;
    std::string variableDataType;
    bool dataTypeIsArray;
    int arraySize;
    int scope;

    std::string procedureName;      //procedure and function need a parameter list

    std::string functionName;
    std::string functionReturnDataType;

    //Need to create an array/linked list of parameters (for a function)
    SymbolTableNode *parameterListHead;
    SymbolTableNode *parameterListTail;
};


#endif //TOKENIZERPROJECT_SYMBOLTABLENODE_HPP
