#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // cheking for correct Input
    if(argc != 2){
        std::cerr << "Usage: ./cr [file_name]\n" 
	        << "Optionally: ./cr [input filename] "
            << ">> [output filename]" 
            << std::endl;
        exit(4);
    }
    
    // open file
    std::ifstream inFile;
    inFile.open(argv[1]);
    if(!inFile.is_open()){
        std::cout << "File cannot be openned." << std::endl;
        return 1;
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
                std::cerr << "ERROR1: Program contains C-style, " 
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
    std::cout << output;

    return 0;
}
