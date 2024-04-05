#include <string>
struct node {
	node(){
		value = "";
		rightChild = nullptr;
		leftChild = nullptr;
	}
	node(std::string val){
		value = val;
		rightChild = nullptr;
		leftChild = nullptr;
	}


	std::string value;
	node* rightChild;
	node* leftChild;
};


class cst {
public:
	cst(){
		size = 0;
		first = nullptr;
		last = nullptr;
	}
	bool insert(std::string val, std::string direction);
	bool deleteLast();
	bool deleteRange(int howManyFromEnd);
	void print();

private:
	int size = 0;
	node* first;
	node* last;
};
