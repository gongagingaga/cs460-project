#include "Token.hpp"
#include "Tokenizer.hpp"

std::string removeComments(std::string filename){
    // open file
    std::ifstream inFile;
    inFile.open(filename);
    if(!inFile.is_open()){
        std::cout << "File cannot be opened." << std::endl;
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

int main(int argc, char* argv[]) {
    // checking for correct Input
    if(argc != 2){
        std::cerr << "Usage: ./cr [file_name]\n"
                  << "Optionally: ./cr [input filename] "
                  << ">> [output filename]"
                  << std::endl;
        exit(4);
    }

    Tokenizer tokenizer;
    std::string uncommentedFile = removeComments(argv[1]);
    std::vector<Token> tokens = tokenizer.tokenize(uncommentedFile);
    tokenizer.printTokens(tokens);

    return 0;
}
