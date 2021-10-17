#include "library.hpp"
enum Colors {
    BLACK,
    RED
};

class Node {
    int key;
    string data;
    bool color;     // 0 - black    1 - red
    Node *lChild,
         *rChild;
    
    Node(int key = -1, string data = "", bool color = RED, Node *lChild = nullptr, Node *rChild = nullptr ) {
        this->key = key;
        this->data = data;
        this->color = color;
        this->lChild = lChild;
        this->rChild = rChild;
    };
    
    friend class RBTree;
};

class RBTree {
    Node *root;
    
public:
    RBTree(): root(nullptr) {}
    void insert(int, string);
    void prettyPrint();
    void printHelper(Node*, string, bool);
};

void RBTree::insert(int key, string data = "") {
    if (root == nullptr) {
        root = new Node(key, data, BLACK);
    }
    else {
        Node* current = root;
        Node* prev = nullptr;
        
        while (current != nullptr) {
            prev = current;
            key < current->key ? current = current->lChild : current = current->rChild;
        }
        
        current = new Node(key, data);
        prev->key > current->key ? prev->lChild = current : prev->rChild = current;
    }
    
}

void RBTree::prettyPrint() {
    if (root) {
        printHelper(root, "", true);
    }
}

void RBTree::printHelper(Node* root, string indent, bool last) {
       if (root != nullptr) {
       cout<<indent;
       if (last) {
          cout<<"R----";
          indent += "     ";
       } else {
          cout<<"L----";
          indent += "|    ";
       }
        
       string sColor = root->color?"RED":"BLACK";
       cout<<root->data<<"("<<sColor<<")"<<endl;
       printHelper(root->lChild, indent, false);
       printHelper(root->rChild, indent, true);
    }
}
int main() {
    
    RBTree bst;
    bst.insert(8, "8");
    bst.insert(18, "18");
    bst.insert(5, "5");
    bst.insert(15, "15");
    bst.insert(17, "17");
    bst.insert(25, "25");
    bst.insert(40, "40");
    bst.insert(80, "80");
    bst.prettyPrint();
    return 0;
}
