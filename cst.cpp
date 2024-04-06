#include "cst.hpp"
#include <string>
#include <iostream>

bool cst::insert(std::string val, bool direction){
	std::cout << "inserting " << val << " size " << size << std::endl;
	node* newNode = new node(val, direction);
	if(last == nullptr && first == nullptr){
		last = newNode;
		first = newNode;
		size++;
		return true;
	}
	if(first != nullptr){
		if(last->nextChildRight){
			last->rightChild = newNode;
			last = newNode;
			size++;
			return true;
		}else if (!last->nextChildRight) {
			last->leftChild = newNode;
			last = newNode;
			size++;
			return true;
		}
		return false;
	}
	return false;
}


bool cst::deleteLast(){
	node* newLast = first;
	
	for(int i = 0; i < size; ++i){
		if(newLast->rightChild == last){
			delete last;
			last = newLast;
			size--;
			return true;
		}else if(newLast->leftChild == last){
			delete last;
			last = newLast;
			size--;
			return true;
		}

		if(newLast->rightChild != nullptr){
			newLast = newLast->rightChild;
		}else if(newLast->leftChild != nullptr){
			newLast = newLast->leftChild;
		}
		else{
			//something is horribly wrong
			return false;
		}
	}
	return false;
}



bool cst::deleteRange(int range){
	//std::cout << "deleting " << range << " things\n";
	for(int i = 0; i < range; ++i){
		deleteLast();
	}
	return true;
}

void cst::print(){
	node* temp = first;
	std::cout << "size?? " << size << std::endl;
	for(int i = 0; i < size; ++i){
		if(temp == nullptr){
			std::cout << "list empty!! ahaahahah\n";
			return;
		}
		if (last == first){
			std::cout << temp->value << std::endl;
			return;
		}
		std::cout << temp->value;
		if(temp->rightChild != nullptr){
			std::cout << " -> ";
			temp = temp->rightChild;
		}else if(temp->leftChild != nullptr){
			std::cout << " v \n";
			temp = temp->leftChild;
		}else{
			std::cout << "\n";
			return;
		}
	}
}
