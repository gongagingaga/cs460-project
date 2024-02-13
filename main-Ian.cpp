#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void checkBlockEnd(){

}

int main() {
    string fileString = "";
    char thing;
    ifstream myFile;
    int lineNumber = 1;
    bool inQuote = false;

    myFile.open("programFile.c");
    if(!myFile.is_open()){
        return 1;
    }

    while(myFile.get(thing)){
        if(thing == '/' && !inQuote){
            myFile.get(thing);
            if(thing == '/'){
                string spaces = "  ";
                while(myFile.get(thing)){
                    if(thing == '\n'){
                        lineNumber++;
                        spaces += '\n';
                        break;
                    }
                    spaces += ' ';
                }
                fileString += spaces;
            }else if(thing == '*'){
                string spaces = "  ";
                int newLines = 0;
                while(myFile.get(thing)){
                    if(thing == '*'){
                        if(myFile.peek() == '/'){
                            myFile.get(thing);
                            spaces += "  ";
                            break;
                        }
                    }
                    if(thing == '\n'){
                        newLines++;
                        spaces += '\n';
                    }else {
                        spaces += ' ';
                    }
                }
                if(myFile.eof()){
                    cout << "There is an unclosed comment on line number ";
                    cout << lineNumber << endl;
                    exit(2);
                }
                fileString += spaces;
                lineNumber += newLines;
            }else{
                fileString += "/";
                fileString += thing;
            }
        }else{
            if(thing == '\'' || thing == '"'){
                inQuote = !inQuote;
            }
            fileString += thing;
            if(thing == '\n'){
                lineNumber++;
            }
        }
    }

    cout << fileString;

    return 0;
}
