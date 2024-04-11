#include "SymbolTable.hpp"

SymbolTable::SymbolTable() : head(nullptr), _tail(nullptr) {

}



bool SymbolTable::empty() {
    return head == nullptr;
}




void SymbolTable::printSymbolTable() {
    for( SymbolTableNode* curr = head; curr != nullptr; curr = curr->next() ) {
        curr->printNode();
        std::cout << std::endl;
    }
    //now, print the parameter lists
    for( SymbolTableNode* curr = head; curr != nullptr; curr = curr->next() ) {
        if( ( curr->isFunction() || curr->isProcedure() )&& !curr->paramListEmpty() ) {
            std::cout << "PARAMETER LIST FOR: ";
            if( curr->isProcedure() )
                std::cout << curr->getProcedureName();
            else
                std::cout << curr->getFunctionName();
            std::cout << std::endl;
            for( SymbolTableNode *node = curr->getparameterList(); node != nullptr ;node = node->next() ) {
                node->printParamNode();
                std::cout << std::endl;
            }
        }
    }
}


/*
void SymbolTable::addNode( std::string varName, std::string varDataType, bool isArray, int arrSize, int varScope ) {
    SymbolTableNode *newNode = new SymbolTableNode( varName, varDataType, isArray, arrSize, varScope );
    if( empty() ) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next( newNode );
        tail = newNode;
    }
}



void SymbolTable::addNode( std::string procName, SymbolTableNode *paramListHead, int procScope ) {
    SymbolTableNode *newNode = new SymbolTableNode( procName, paramListHead, procScope );
    if( empty() ) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next( newNode );
        tail = newNode;
    }
}



void SymbolTable::addNode( std::string functName, std::string functRetDataType, SymbolTableNode *paramListHead, int functScope ) {
    SymbolTableNode *newNode = new SymbolTableNode( functName, functRetDataType, paramListHead, functScope );
    if( empty() ) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next( newNode );
        tail = newNode;
    }
}
*/


void SymbolTable::addNode( SymbolTableNode *newNode ) {
    if( newNode == nullptr ) {
        std::cout << "Invalid SymbolTableNode added to SymbolTable, terminating...";
        exit(3);
    }
    if( empty() ) {
        head = newNode;
        _tail = newNode;
    } else {
        _tail->next( newNode );
        _tail = newNode;
    }
}



void SymbolTable::removeNode( ) {
    //add if needed
}



void SymbolTable::printParameterList() {
    //future issue: when to print the parameter list!!
}



SymbolTableNode* &SymbolTable::tail() {
    return _tail;
}