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

void generateDB(RBTree);

void RBTree::deleteNode(int key) {
    bool deleted = false;
    Node* node = root;
    while (node) {
        if (node->key == key) {
            
            //Rebase node to node with 0-1 child(ren)
            if (node->left && node->right) {
                Node* cur = node->left;
                while (cur->right) {cur = cur->right;}
                rebaseNodes(node, cur);
            }
            
            delete_case1(node);
            
            Node* c = nullptr;    // child
            if (node->left) {c = node->left;}
            else if (node->right) {c = node->right;}
            
            isLeft(node) ? node->parent->left = c : node->parent->right = c;
            if(c) {c->parent = node->parent;}
            
            cout << "KEY IS FOUND, DATA: '" << node->data <<
                    "' HAS BEEN DELETED" << endl;
            delete node;
            deleted = true;
            break;
        }
        node = (node->key > key) ? (node->left) : (node->right);
    }
    
    if (!deleted) {
        cout << "THERE ARE NO DATA, TRY ANOTHER KEY " <<
                "(write letters to stop): ";
        cin >> key;
        deleteNode(key);
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
        p->key > key ? p->left = node : p->right = node;
        isLeft(node) ? p->left = node : p->right = node;
        checkTree(node);
    }
}

void RBTree::delete_case1(Node* node) {
    if (node->parent) {delete_case2(node);}
}

void RBTree::delete_case2(Node* node) {
    Node* s = sibling(node);
    if (s && s->color == RED) {
        node->parent->color = RED;
        s->color = BLACK;
        isLeft(node) ? leftRotate(s) : rightRotate(s);
    }
    delete_case3(node);
}

void RBTree::delete_case3(Node* node) {
    Node* s = sibling(node);
    if ((node->parent->color == BLACK && s) &&
        (s->color == BLACK) &&
        (!s->left || s->left->color == BLACK) &&
        (!s->right || s->right->color == BLACK)) {
        s->color = RED;
        delete_case1(node->parent);
    } else
        delete_case4(node);
}

void RBTree::delete_case4(Node* node) {
    Node* s = sibling(node);
    if ((node->parent->color == RED && s) && (s->color == BLACK) &&
        (!s->left || s->left->color == BLACK) &&
        (!s->right || s->right->color == BLACK)) {
        s->color = RED;
        node->parent->color = BLACK;
    } else
        delete_case5(node);
}

void RBTree::delete_case5(Node* node) {
    Node *s = sibling(node);
    if  (s && s->color == BLACK) {
        if (isLeft(node) &&
            (s->right && s->right->color == BLACK) &&
            (s->left && s->left->color == RED)) {
            s->color = RED;
            s->left->color = BLACK;
            rightRotate(s->left);
        } else if (isRight(node) &&
                   (s->left && s->left->color == BLACK) &&
                   (s->right && s->right->color == RED)) {
            s->color = RED;
            s->right->color = BLACK;
            leftRotate(s->right);
        }
    }
    delete_case6(node);
}

void RBTree::delete_case6(Node* node) {
    Node* s = sibling(node);
    if (s) {
        s->color = node->parent->color;
        node->parent->color = BLACK;

        if (isLeft(node)) {
            s->right->color = BLACK;
            leftRotate(s);
        } else {
            s->left->color = BLACK;
            rightRotate(s);
        }
    }
}

void RBTree::rebaseNodes(Node* &n1, Node* &n2) {
    bool isChild = (n1->left == n2  ||  n1->right == n2) ? true : false;
    bool isLeftChild = isLeft(n2) ? true : false;
    Node* ex1 = new Node(n1->key, n1->data, n1->parent, n1->color, n1->left, n1->right);
    Node* ex2 = new Node(n2->key, n2->data, n2->parent, n2->color, n2->left, n2->right);
    
    // p <-> n2
    if (n1 != root) {
        isLeft(ex1) ? ex1->parent->left = n2 : ex1->parent->right = n2;}
    else {root = n2;}
    n2->parent = ex1->parent;
    // n1 <-> c
    n1->left = ex2->left;
    n1->right = ex2->right;
    if (ex2->left) {ex2->left->parent = n1;}
    if (ex2->right) {ex2->right->parent = n1;}
    
    // case: ex2 is ex1's child
    if (isChild) {
        // n2 <-> n1
        isLeftChild ? n2->left = n1 : n2->right = n1;
        n1->parent = n2;
        // other n2's c <-> n2
        if (isLeftChild) {
            n2->right = ex1->right;
            if (ex1->right) {ex1->right->parent = n2;}
        }
        else {
            n2->left = ex1->left;
            if (ex1->left) {ex1->left->parent = n2;}
        }
    }
    else {
        // p <-> n1
        n1->parent = ex2->parent;
        isLeft(ex2) ? ex2->parent->left = n1 : ex2->parent->right = n1;
        // n2 <-> c
        n2->left = ex1->left;
        n2->right = ex1->right;
        if (ex1->left) {ex1->left->parent = n2;}
        if (ex1->right) {ex1->right->parent = n2;}
    }
    
    n1->color = ex2->color;
    n2->color = ex1->color;
    delete ex1;
    delete ex2;
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
    if (g == nullptr) {root = node;}
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
    if (g == nullptr) {root = node;}
    if (g) {isLeft(p) ? g->left = node : g->right = node;}
    
    p->right = node->left;
    if (node->left) {node->left->parent = p;}
    
    p->parent = node;
    node->left = p;
}



int main() {
    RBTree tree;
    uint choice;
    
    do {
        cout << "Press: 1/2/3 to: \n" <<
                "1. Generate DB \n" <<
                "2. Insert data \n" <<
                "3. Delete data \n";
        cout << "Your choice: "; cin >> choice; cout << endl;
        
        try {
            switch (choice) {
                case 1:
                    try {
                        uint size;
                        cout << "DB size (nodes' quantity), 1000 is maximum: "; cin >> size;
                        generateDB(tree);
                        cout << endl;
                    } catch (exception err) {
                        cout << "Wrong size!\n";
                    }
                    break;
                    
                case 2:
                    try {
                        uint key;
                        string data;
                        cout << "key to insert: "; cin >> key;
                        cout << "data: "; cin >> data;
                        tree.insert(key, data);
                        cout << endl;
                    } catch (exception err) {
                        cout << "Wrong key!\n";
                    }
                    break;
                    
                case 3:
                    try {
                        uint key;
                        cout << "key to delete: "; cin >> key;
                        tree.deleteNode(key);
                        cout << endl;
                    } catch (exception err) {
                        cout << "Wrong key!\n\n";
                    }
                    break;
                    
                default:
                    cout << "There is no function like this!\n\n";
                    break;
            }
            
        } catch (exception err) {
            cout << "There is no function like this!\n\n";
        }
    } while (true);
    
    /*
    bst.insert(8, "8");
    bst.insert(18, "18");
    bst.insert(5, "5");
    bst.insert(15, "15");
    bst.insert(17, "17");
    bst.insert(25, "25");
    bst.insert(40, "40");
    bst.insert(80, "80");
    bst.deleteNode(25);
    bst.deleteNode(17);
    bst.deleteNode(17); */
    return 0;
}

void generateDB(RBTree tree) {
    
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
    Node* s = nullptr;
    Node* p = node->parent;
    if (p) {s = isLeft(node) ? p->right : p->left;}
    return s;
}


bool RBTree::isLeft(Node* node) {
    if (node->parent->left == node) {return true;}
    return false;
}
bool RBTree::isRight(Node* node) {
    if (node->parent->right == node) {return true;}
    return false;
}
