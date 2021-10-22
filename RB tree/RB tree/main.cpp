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
    
public:
    RBTree(): root(nullptr) {}
    Node* sibling(Node*);
    Node* grandparent(Node*);
    Node* uncle(Node*);
    void insert(int, string);
    void deleteNode(Node*);
    
    bool isLeft(Node*);
    bool isRight(Node*);
    void leftRotate(Node*);     //   Node which goes up..
    void rightRotate(Node*);    //.. should be an argument
    void checkTree(Node*);
};

void RBTree::deleteNode(Node* node) {
    //CASE_1 node is BLACK & has a RED child
    if (node->color == BLACK) {
        Node* red;
        if (node->left) {red = (node->left->color == RED) ? node->left : nullptr;}
        else {
            if (node->right) {red = (node->right->color == RED) ? node->right : nullptr;}
        }
        
        if (red) {
            if (isLeft(red)) {
                red->right = node->right;
                if (node->right) {node->right->parent = red;}
            }
            red->parent = node->parent;
            isLeft(node) ? node->parent->left = red : node->parent->right = red;
            delete node;
        }
    }
}


void RBTree::insert(int key, string data = "") {
    // CASE_1: first node - root (BLACK)
    if (!root) {root = new Node(key, data, nullptr, BLACK);}
    else {
        Node* node = root;
        Node* p = nullptr;   // parent
        
        while (node) {
            p = node;
            key < node->key ? node = node->left : node = node->right;
        }
        
        node = new Node(key, data, p);
        isLeft(node) ? p->left = node : p->right = node;
        checkTree(node);
    }
}

void RBTree::checkTree(Node* node) {
        // CASE_2: p == RED
    if (node->parent->color == RED) {
        Node* p = node->parent;
        Node* u = uncle(node);
        Node* g = grandparent(node);
        
        // CASE_3: u == p == RED
        if (u  &&  u->color == p->color == RED) {
            u->color = p->color = BLACK;                            // recolor u&p to BLACK
            if (g != root) {
                g->color = RED;                                     // recolor g   to RED   (if not a root)
                if (g->parent->color == RED) {checkTree(g);}
            }
        }
        
        // CASE_4: check g->l == p  && p->l == node (mirror)
        else {
            bool rotated = false;
            if ((isLeft(node) && isRight(p))  ||  (isRight(node) && isLeft(p))) {
                isRight(node) ? leftRotate(node) : rightRotate(node);
                p = node->parent;
                g = grandparent(node);
                u = uncle(node);
                rotated = true;
            }
            
            // CASE_5: p == RED,  u == BLACK
            if (rotated) {
                isLeft(node) ? rightRotate(node) : leftRotate(node);
                p->color = RED;
                node->color = BLACK;
            }
            else {
                isLeft(node) ? rightRotate(p) : leftRotate(p);
                p->color = BLACK;
                g->color = RED;
            }
        }
    }
}

void RBTree::rightRotate(Node* node) {
    Node* g = grandparent(node);  // future parent
    Node* p = node->parent;       // future right child
    
    node->parent = g;
    if (g) {isLeft(p) ? g->left = node : g->right = node;}
    
    p->left = node->right;
    if (node->right) {node->right->parent = p;}
    
    p->parent = node;
    node->right = p;
}

void RBTree::leftRotate(Node* node) {
    Node* g = grandparent(node);  // future parent
    Node* p = node->parent;       // future left child
    
    node->parent = g;
    if (g) {isLeft(p) ? g->left = node : g->right = node;}
    
    p->right = node->left;
    if (node->left) {node->left->parent = p;}
    
    p->parent = node;
    node->left = p;
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
    return 0;
}



Node* RBTree::grandparent(Node* node) {
    Node* g;
    node->parent->parent ? g = node->parent->parent : g = nullptr;
    return g;
}

Node* RBTree::uncle(Node* node) {
    Node* u = nullptr;
    if (grandparent(node)) {
        isLeft(node->parent) ? u = grandparent(node)->right : u = grandparent(node)->left;
    }
    return u;
}

Node* RBTree::sibling(Node* node) {
    Node* s;
    Node* p = node->parent;
    if (p) {s = isLeft(node) ? p->right : p->left;}
    return s;
}


bool RBTree::isLeft(Node* node) {
    if (node->parent->key > node->key) {return true;}
    return false;
}
bool RBTree::isRight(Node* node) {
    if (node->parent->key > node->key) {return false;}
    return true;
}
