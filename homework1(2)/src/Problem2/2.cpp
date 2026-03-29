#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
struct Node {
    T data;
    Node* left;
    Node* right;

    Node(T x) : data(x), left(nullptr), right(nullptr) {}
};

template <class T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, T x) {
        if (!node) return new Node<T>(x);

        if (x < node->data)
            node->left = insert(node->left, x);
        else
            node->right = insert(node->right, x);

        return node;
    }

    int height(Node<T>* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    Node<T>* remove(Node<T>* node, T key) {
        if (!node) return nullptr;

        if (key < node->data)
            node->left = remove(node->left, key);
        else if (key > node->data)
            node->right = remove(node->right, key);
        else {      
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            Node<T>* minNode = node->right;
            while (minNode->left)
                minNode = minNode->left;
            node->data = minNode->data;
            node->right = remove(node->right, minNode->data);
        }
        return node;
    }

    void inorder(Node<T>* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(T x) {
        root = insert(root, x);
    }

    int getHeight() {
        return height(root);
    }

    void remove(T key) {
        root = remove(root, key);
    }

    void print() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    srand(time(0));
    cout << "A" << endl;

    int testCases[] = { 100, 500, 1000, 2000, 3000, 5000, 10000 };

    for (int i = 0; i < 7; i++) {
        int n = testCases[i];
        BST<int> tree;

        for (int j = 0; j < n; j++) {
            tree.insert(rand());
        }
        double h = tree.getHeight();
        double ratio = h / log2(n);
        cout << "n=" << n
            << ", height=" << h
            << ", h/log2(n)=" << ratio << endl;
    }
    cout << "B" << endl;
    BST<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    cout << "Before: ";
    tree.print();

    tree.remove(30);

    cout << "After: ";
    tree.print();

    return 0;
}