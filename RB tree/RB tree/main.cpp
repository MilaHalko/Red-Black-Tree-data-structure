#include "Tree&Node.hpp"
void readFile(RBTree);

int main() {
    RBTree tree;
    int choice;
    readFile(tree);
    
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
                            tree.generateDB(size);
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
                            cout << "data: ";
                            cin.ignore();
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
    return 0;
}

void readFile(RBTree tree) {
    ifstream fin (FILE_BD);
    vector<string> oldFile;
    while (!fin.eof()) {
        oldFile.resize(0);
        string str;
        getline(fin, str);
        if (!str.empty()) {
            oldFile.push_back(str);
            
            int index = str.find(":");
            int key = stoi(str.substr(0, index));
            str = str.substr(index+1);
            tree.insert(key, str);
        }
    }
    fin.close();
}

