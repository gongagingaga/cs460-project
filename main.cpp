#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string fileString = "";
    char thing;
    ifstream myFile;
    int lineNumber = 1;
    bool inQuote = false;

    myFile.open(argv[1]);
    if(!myFile.is_open()){
        cout << "File cannot be openned." << endl;
        return 1;
    }

    while(myFile.get(thing)){
        if(thing == '*'){
            char c = myFile.peek();
            if(c == '/'){
                cout << "There is a close block comment on line ";
                cout << lineNumber;
                cout << " with no open block comment." << endl;
                exit(3);
            }
        }
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
