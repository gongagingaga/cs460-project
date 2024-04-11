#include <string>
struct node {
    node(){
        value = "";
        rightChild = nullptr;
        leftChild = nullptr;
    }
    node(std::string val, bool direction){
        value = val;
        nextChildRight = direction;
        rightChild = nullptr;
        leftChild = nullptr;
    }

    bool nextChildRight;
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
    bool insert(std::string val, bool direction);
    bool deleteLast();
    bool deleteRange(int howManyFromEnd);
    void print();

private:
    int size = 0;
    node* first;
    node* last;
};