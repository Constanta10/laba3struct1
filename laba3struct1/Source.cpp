#include <iostream>
#include <iomanip> // ��� ������������� setw

using namespace std;

// ���� ������
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void Add_Binary_Tree(Node** root, int key) {
    Node* ptr; // ��������������� ���������
    int fl = 1;

    if (*root == nullptr) {
        ptr = new Node(key);
        *root = ptr;
    }
    else {
        ptr = *root;
        while (fl == 1) {
            if (ptr->data > key) {
                if (ptr->left == nullptr) {
                    ptr->left = new Node(key);
                    fl = 0;
                }
                else {
                    ptr = ptr->left;
                }
            }
            else if (ptr->data < key) {
                if (ptr->right == nullptr) {
                    ptr->right = new Node(key);
                    fl = 0;
                }
                else {
                    ptr = ptr->right;
                }
            }
            else { 
                fl = 2;
            }
        }
    }
}

// ������� ��� ������ ��������� �����
bool shiftSubtreeUp(Node*& root, int levelToShift, int currentLevel = 1) {
    if (root == nullptr) // ������� ������: ���� ���� ������, ���������� nullptr
        return false;

    if (currentLevel == levelToShift) {
        Node* temp = root; // ��������� ������ �������� ���������
        root = root->left; // ��������� ����� ��������� �� ������� ����
        if (temp->right != nullptr) { // ���� ���� ������ ���������, ��������� ��� � ������� ������� �����
            Node* rightmost = root;
            while (rightmost->right != nullptr) {
                rightmost = rightmost->right;
            }
            rightmost->right = temp->right;
        }
        delete temp; // ������� ������ �������� ���������
        return true; // ���������� true, ��� ����� �������� �������
    }
    else {
        // ���������� �������� ������� ��� ������ � ������� ����������� � ����������� ������
        bool leftShifted = shiftSubtreeUp(root->left, levelToShift, currentLevel + 1);
        bool rightShifted = shiftSubtreeUp(root->right, levelToShift, currentLevel + 1);
        return leftShifted || rightShifted; // ���������� true, ���� ����� �������� ���� �� ��� ������ ���������
    }
}

// ����������� ������� ��� ������ ������ � ��������� �������
void printTree(Node* root, int level = 0) {
    if (root == nullptr)
        return;

    printTree(root->right, level + 1);
    cout << setw(4 * level) << ""; // ��������� ������� � ����������� �� ������
    cout << root->data << endl;
    printTree(root->left, level + 1);
}

int main() {
    setlocale(LC_ALL, "ru");
    Node* root = nullptr;
    // ���� ������ � ���������� ��� �������� ������
    int n;
    cout << "������� ���������� ���������: ";
    cin >> n;

    cout << "������� ��������: ";
    for (int i = 0; i < n; ++i) {
        int key;
        cin >> key;
        Add_Binary_Tree(&root, key);
    }
    printTree(root);

    int targetLevel;
    cout << "������� ������� ��� ��������: ";
    cin >> targetLevel;

    cout << "������ �� �������� ������ " << targetLevel << ":\n";
    cout << endl;
    printTree(root);
    if (!shiftSubtreeUp(root, targetLevel)) {
        cerr << "������� ��� ������ �� ���������� � ������." << endl;
        exit(EXIT_FAILURE);
    }



    cout << "������ ����� �������� ������ " << targetLevel << ":\n";
    printTree(root);
    cout << endl;

    // ������������ ������
    // ...

    return 0;
}
