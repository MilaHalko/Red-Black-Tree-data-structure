#include "Tree&Node.hpp"

int main() {
    RBTree tree;
    int choice;
    
    do {
        cout << "Press: 1/2/3 to: \n" <<
                "1. Generate DB \n" <<
                "2. Insert data \n" <<
                "3. Delete data \n";
        cout << "Your choice: "; cin >> choice; cout << endl;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767,'\n');
            cout << "That input is invalid.\n\n";
        }
        else {
            int key;
            switch (choice) {
                case 1: {
                    int size;
                    cout << "DB size (nodes' quantity), 1000 is maximum: "; cin >> size;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767,'\n');
                        cout << "That input is invalid.\n\n";
                    }
                    else {
                        if (size >= 1  &&  size <= 1000) {
                            generateDB(tree);
                            cout << endl;
                        }
                        else {cout << "Written size is wrong\n\n";}
                    }
                    break;
                }
                case 2: {
                    string data;
                    cout << "key to insert: "; cin >> key;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767,'\n');
                        cout << "That input is invalid.\n\n";
                    }
                    else {
                        if (key <= 0  ||  key > 1000) {cout << "Key is out of range.\n\n";}
                        else {
                            cout << "data: "; cin.ignore();
                            getline(cin, data);
                            tree.insert(key, data);
                            cout << endl;
                        }
                    }
                    break;
                }
                case 3: {
                    cout << "key to delete: "; cin >> key;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767,'\n');
                        cout << "That input is invalid.\n\n";
                    }
                    else {
                        if (key <= 0  ||  key > 1000) {cout << "Key is out of range.\n\n";}
                        else {
                            tree.deleteNode(key);
                            cout << endl;
                        }
                    }
                    break;
                }
                default: {
                    cout << "There is no function like this!\n\n";
                    break;
                }
            }
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
