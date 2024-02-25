#include <iostream>
#include "Parser.hpp"

int main() {
    Parser parser("Test2.c");
    parser.parseFile();
    parser.print();
}
