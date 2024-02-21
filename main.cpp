#include "tokens.hpp"

int main(int argc, char* argv[]) {
    // cheking for correct Input
    if(argc != 2){
        std::cerr << "Usage: ./cr [file_name]\n" 
	        << "Optionally: ./cr [input filename] "
            << ">> [output filename]" 
            << std::endl;
        exit(4);
    }   
    
	Token a;
	std::string uncommentedFile = a.removeComments(argv[1]);
	std::vector<std::pair<std::string, BNF>> tokens = a.Tokenizer(uncommentedFile);
    a.printTokens(tokens);

  	return 0;
}
