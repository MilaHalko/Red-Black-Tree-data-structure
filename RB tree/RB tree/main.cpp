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
         *rChild,
         *parent;
    
    Node(int key = -1, string data = "", Node *parent = nullptr, bool color = RED, Node *lChild = nullptr, Node *rChild = nullptr ) {
        this->key = key;
        this->data = data;
        this->color = color;
        this->lChild = lChild;
        this->parent = parent;
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
    bool isLChild(Node*, Node*);
    void leftRotate(Node*);     // Node which goes up
    void rightRotate(Node*);    //
};

void RBTree::insert(int key, string data = "") {
    if (root == nullptr) {
        root = new Node(key, data, nullptr, BLACK);
    }
    else {
        Node* current = root;
        Node* prev = nullptr;
        
        while (current != nullptr) {
            prev = current;
            key < current->key ? current = current->lChild : current = current->rChild;
        }
        
        current = new Node(key, data, prev);
        prev->key > current->key ? prev->lChild = current : prev->rChild = current;
        
        if (prev->color == RED) {
            Node* uncle;
            isLChild(prev, prev->parent) ? uncle = prev->parent->rChild : uncle = prev->parent->lChild;
            
            if (uncle != nullptr  &&  uncle->color == RED) {
                uncle->color = prev->color = BLACK;
                prev->parent != root ? prev->parent->color = RED : prev->parent->color = BLACK;
            }
            else {
                
                if (!isLChild(prev, prev->parent)) {
                    if (isLChild(current, prev)) {
                        rightRotate(current);
                        leftRotate(current);
                        current->color = BLACK;
                        current->lChild->color = RED;
                    }
                    else {
                        leftRotate(prev);
                        current->parent->color = BLACK;
                        current->parent->lChild->color = RED;
                    }
                }
                
                else {
                    if (!isLChild(current, prev)) {
                        leftRotate(current);
                        rightRotate(current);
                        current->color = BLACK;
                        current->rChild->color = RED;
                    }
                    else {
                        leftRotate(prev);
                        current->parent->color = BLACK;
                        current->parent->rChild->color = RED;
                    }
                }
            }
        }
    }
    root->color = BLACK;
}

void RBTree::rightRotate(Node* node) {
    Node* G = node->parent->parent; // G - future grand (used to be parent's parent)
    Node* C = node->parent;         // C - future right child (used to be parent)
    Node* currRChild = node->rChild;
    
    G->rChild = node;
    node->parent = G;
    
    C->parent = node;
    node->rChild = C;
    
    Node* current = node->rChild;
    while (current != nullptr) {
        current = current->lChild;
    }
    current = currRChild;
    currRChild->parent = current->parent;
}

void RBTree::leftRotate(Node* node) {
    Node* G = node->parent->parent; // G - future grand (used to be parent's parent)
    Node* C = node->parent;         // C - future left child (used to be parent)
    Node* currLChild = node->lChild;
    
    G->rChild = node;
    node->parent = G;
    
    C->parent = node;
    node->lChild = C;
    
    Node* current = node->lChild;
    while (current != nullptr) {
        current = current->rChild;
    }
    current = currLChild;
    currLChild->parent = current->parent;
}

bool RBTree::isLChild(Node* current, Node* prev) {
    bool IsLeftChild;
    if (prev->key > current->key) {
        IsLeftChild = true;
        prev->lChild = current;
    }
    else {
        IsLeftChild = false;
        prev->rChild = current;
    }
    return IsLeftChild;
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
