#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


//comment remover
//takes in a filename, removes comments and reduces them to newlines, then 
//returns a new file name with the changes applied. At this point this may
//be merely for debug purposes, might be void later.
void removeComments(std::string filename, std::string newfile){
	//open file for reading
	std::ifstream file(filename); 
	if(!file.is_open()){ 
		std::cerr << "unable to open file" << std::endl;
		exit(1);
	}
	
	//open file for rewritting
	std::ofstream newFile(newfile);
	if(!newFile.is_open()){ 
		std::cerr << "unable to open file" << std::endl;
		exit(1);
	}

	char c;
	file.get(c);
	while(!file.eof()) {
		//both branches start at a /
		if(c == '/'){
			file.get(c);
			//check if double slash comment
			if(c == '/'){
				while(c != '\n' && !file.eof()){
					file.get(c);
				}
				newFile << '\n';
				file.get(c);
				continue; //stops after \n

			//check if /* comment
			}else if(c == '*'){
				file.get(c);
				do{	//do-while to not repeat code
					if(c == '*' && !file.eof()){
						file.get(c);
						if(c == '/'){ //checks for end of comment
							if(isspace(c))file.get(c); //eats the newline
													   //after the /
							file.get(c); //reads the actual next value
							break;

						}
						continue; //ignore if just a * in the comment

					}else if(c == '\n') {
						//we want to keep the line numbers the same
						//so keep the new lines in
						newFile << c;

					}
					file.get(c); //iterate
				}while(!file.eof());
			}
		}
		
		newFile << c; //irrelevant character or one passed in after the */ 
		file.get(c); //iterate
	}
	newFile.close();
}

int main(int argc, char* argv[]){
	if(argc != 3){
		std::cerr << "Usage: ./aaa [input filename] [output filename]" 
			<< std::endl;
		exit(2);
	}
	std::string a = argv[1];
	std::string b = argv[2];
	removeComments(a, b);
}
