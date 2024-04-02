#include <iostream>
#include "Parser.hpp"

int main(int argc, char* argv[]) {
	if(argc != 2){
		std::cerr << "Usage: ./[exe] [filename]" << std::endl;
		exit(6);
	}
    Parser parser(argv[1]);
    parser.parseFile();
//    parser.tokenizer.printUncommentedFile();
    std::cout << parser.parseProgram();
//    parser.print();
}
