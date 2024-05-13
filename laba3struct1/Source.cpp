#include <iostream>
#include <iomanip> // Для использования setw

using namespace std;

// Узел дерева
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void Add_Binary_Tree(Node** root, int key) {
    Node* ptr; // Вспомогательный указатель
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

// Функция для сдвига поддерева вверх
bool shiftSubtreeUp(Node*& root, int levelToShift, int currentLevel = 1) {
    if (root == nullptr) // Базовый случай: если узел пустой, возвращаем nullptr
        return false;

    if (currentLevel == levelToShift) {
        Node* temp = root; // Сохраняем корень текущего поддерева
        root = root->left; // Поднимаем левое поддерево на уровень выше
        if (temp->right != nullptr) { // Если есть правое поддерево, добавляем его к правому потомку корня
            Node* rightmost = root;
            while (rightmost->right != nullptr) {
                rightmost = rightmost->right;
            }
            rightmost->right = temp->right;
        }
        delete temp; // Удаляем корень текущего поддерева
        return true; // Возвращаем true, что сдвиг выполнен успешно
    }
    else {
        // Рекурсивно вызываем функцию для левого и правого поддеревьев с увеличением уровня
        bool leftShifted = shiftSubtreeUp(root->left, levelToShift, currentLevel + 1);
        bool rightShifted = shiftSubtreeUp(root->right, levelToShift, currentLevel + 1);
        return leftShifted || rightShifted; // Возвращаем true, если сдвиг выполнен хотя бы для одного поддерева
    }
}

// Рекурсивная функция для вывода дерева в табличном формате
void printTree(Node* root, int level = 0) {
    if (root == nullptr)
        return;

    printTree(root->right, level + 1);
    cout << setw(4 * level) << ""; // Установка отступа в зависимости от уровня
    cout << root->data << endl;
    printTree(root->left, level + 1);
}

int main() {
    setlocale(LC_ALL, "ru");
    Node* root = nullptr;
    // Ввод данных с клавиатуры для создания дерева
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите элементы: ";
    for (int i = 0; i < n; ++i) {
        int key;
        cin >> key;
        Add_Binary_Tree(&root, key);
    }
    printTree(root);

    int targetLevel;
    cout << "Введите уровень для удаления: ";
    cin >> targetLevel;

    cout << "Дерево до удаления уровня " << targetLevel << ":\n";
    cout << endl;
    printTree(root);
    if (!shiftSubtreeUp(root, targetLevel)) {
        cerr << "Уровень для сдвига не существует в дереве." << endl;
        exit(EXIT_FAILURE);
    }



    cout << "Дерево после удаления уровня " << targetLevel << ":\n";
    printTree(root);
    cout << endl;

    // Освобождение памяти
    // ...

    return 0;
}
