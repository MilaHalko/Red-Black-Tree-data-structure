#pragma once
#include "library.hpp"

enum Colors {
    BLACK,
    RED
};

class Node {
    int key;
    string data;
    bool color;     // 0 - black    1 - red
    Node *left,
         *right,
         *parent;
    
    Node(int key = -1, string data = "", Node *parent = nullptr, bool color = RED, Node *left = nullptr, Node *right = nullptr ) {
        this->key = key;
        this->data = data;
        this->color = color;
        this->left = left;
        this->parent = parent;
        this->right = right;
    };
    
    friend class RBTree;
};

class RBTree {
    Node *root;
    
    // GET RELATIVES functions
    Node* sibling(Node*);
    Node* grandparent(Node*);
    Node* uncle(Node*);
    bool isLeft(Node*);
    bool isRight(Node*);
    
    // REBALANCE functions
    void leftRotate(Node*);     //   Node which goes up..
    void rightRotate(Node*);    //.. should be an argument
    
    // GENERATION functions
    void generateDB();
    
    // INSERT functions
    void checkTree(Node*);
    
    // DELETE-NODE functions
    void rebaseNodes(Node* &, Node* &);
    void delete_case1(Node*);
    void delete_case2(Node*);
    void delete_case3(Node*);
    void delete_case4(Node*);
    void delete_case5(Node*);
    void delete_case6(Node*);
    
public:
    RBTree(): root(nullptr) {}
    void insert(int, string);
    void deleteNode(int);
    friend void generateDB(RBTree);
};

void RBTree::generateDB() {
    
}
