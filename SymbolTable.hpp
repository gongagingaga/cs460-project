#ifndef TOKENIZERPROJECT_SYMBOLTABLE_HPP
#define TOKENIZERPROJECT_SYMBOLTABLE_HPP

#include "SymbolTableNode.hpp"

class SymbolTable {
public:
    SymbolTable();
    bool empty();
    void printSymbolTable();
    /* No use for these currently, saved just in case
    void addNode( std::string varName, std::string varDataType, bool isArray, int arrSize, int varScope );
    void addNode( std::string procName, SymbolTableNode *paramListHead, int procScope );
    void addNode( std::string functName, std::string functRetDataType, SymbolTableNode *paramListHead, int functScope );
    */
    void addNode( SymbolTableNode *newNode );
    void removeNode();
    bool sameScoping( std::string varName, int varScope );

    void printParameterList();
    SymbolTableNode* &tail();
private:
    SymbolTableNode *head;
    SymbolTableNode *_tail;
};


#endif //TOKENIZERPROJECT_SYMBOLTABLE_HPP
