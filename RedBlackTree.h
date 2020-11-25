#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum Color { RED, BLACK, DOUBLE_BLACK };

struct Node
{
    int data;
    int color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int data)
    {
        this->data = data;
        color = RED;
        left = right = parent = nullptr;
    }
};

class RedBlackTree
{
private:
    Node* root;

    int getColor(Node* p)
    {
        if (p == nullptr)
            return BLACK;

        return p->color;
    }

    void setColor(Node*& p, int color)
    {
        if (p == nullptr)
            return;

        p->color = color;
    }

    void rotateLeft(Node*& p)
    {
        Node* child = p->right;
        p->right = child->left;

        if (p->right != nullptr)
            p->right->parent = p;

        child->parent = p->parent;

        if (p->parent == nullptr)
            root = child;
        else if (p == p->parent->left)
            p->parent->left = child;
        else
            p->parent->right = child;

        child->left = p;
        p->parent = child;
    }

    void rotateRight(Node*& p)
    {
        Node* child = p->left;
        p->left = child->right;

        if (p->left != nullptr)
            p->left->parent = p;

        child->parent = p->parent;

        if (p->parent == nullptr)
            root = child;
        else if (p == p->parent->left)
            p->parent->left = child;
        else
            p->parent->right = child;

        child->right = p;
        p->parent = child;
    }

    void RebalanceInsert(Node*& p)
    {
        Node* parent = nullptr;
        Node* grandparent = nullptr;
        while (p != root && getColor(p) == RED && getColor(p->parent) == RED)
        {
            parent = p->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left)
            {
                Node* uncle = grandparent->right;
                if (getColor(uncle) == RED)
                {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    p = grandparent;
                }
                else
                {
                    if (p == parent->right)
                    {
                        rotateLeft(parent);
                        p = parent;
                        parent = p->parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    p = parent;
                }
            }
            else
            {
                Node* uncle = grandparent->left;
                if (getColor(uncle) == RED)
                {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    p = grandparent;
                }
                else {
                    if (p == parent->left)
                    {
                        rotateRight(parent);
                        p = parent;
                        parent = p->parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    p = parent;
                }
            }
        }
        setColor(root, BLACK);
    }

    Node* insertValue(Node* root, Node* p)
    {
        if (root == nullptr)
            return p;

        if (root->data >= p->data)
        {
            root->left = insertValue(root->left, p);
            root->left->parent = root;
        }
        else if (root->data < p->data)
        {
            root->right = insertValue(root->right, p);
            root->right->parent = root;
        }

        return root;
    }

    Node* getMinValue(Node*& p)
    {
        Node* min = p;

        while (min->left != nullptr)
            min = min->left;

        return min;
    }

    Node* getMaxValue(Node*& p)
    {
        Node* max = p;

        while (max->right != nullptr)
            max = max->right;

        return max;
    }

    void RebalanceDelete(Node*& p)
    {
        if (p == nullptr)
            return;

        if (p == root) {
            root = nullptr;
            return;
        }

        if (getColor(p) == RED || getColor(p->left) == RED || getColor(p->right) == RED) {
            Node* child = p->left != nullptr ? p->left : p->right;

            if (p == p->parent->left) {
                p->parent->left = child;
                if (child != nullptr)
                    child->parent = p->parent;
                setColor(child, BLACK);
                delete (p);
            }
            else {
                p->parent->right = child;
                if (child != nullptr)
                    child->parent = p->parent;
                setColor(child, BLACK);
                delete (p);
            }
        }
        else {
            Node* sibling = nullptr;
            Node* parent = nullptr;
            Node* temp = p;
            setColor(temp, DOUBLE_BLACK);
            while (temp != root && getColor(temp) == DOUBLE_BLACK) {
                parent = temp->parent;
                if (temp == parent->left) {
                    sibling = parent->right;
                    if (getColor(sibling) == RED) {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        rotateLeft(parent);
                    }
                    else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            setColor(sibling, RED);
                            if (getColor(parent) == RED)
                                setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            temp = parent;
                        }
                        else {
                            if (getColor(sibling->right) == BLACK) {
                                setColor(sibling->left, BLACK);
                                setColor(sibling, RED);
                                rotateRight(sibling);
                                sibling = parent->right;
                            }
                            setColor(sibling, parent->color);
                            setColor(parent, BLACK);
                            setColor(sibling->right, BLACK);
                            rotateLeft(parent);
                            break;
                        }
                    }
                }
                else {
                    sibling = parent->left;
                    if (getColor(sibling) == RED) {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        rotateRight(parent);
                    }
                    else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            setColor(sibling, RED);
                            if (getColor(parent) == RED)
                                setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            temp = parent;
                        }
                        else {
                            if (getColor(sibling->left) == BLACK) {
                                setColor(sibling->right, BLACK);
                                setColor(sibling, RED);
                                rotateLeft(sibling);
                                sibling = parent->left;
                            }
                            setColor(sibling, parent->color);
                            setColor(parent, BLACK);
                            setColor(sibling->left, BLACK);
                            rotateRight(parent);
                            break;
                        }
                    }
                }
            }
            if (p == p->parent->left)
                p->parent->left = nullptr;
            else
                p->parent->right = nullptr;
            delete(p);
            setColor(root, BLACK);
        }
    }

    Node* deleteValue(Node*& p, int val)
    {
        if (p == nullptr)
            return p;

        if (val < p->data)
            return deleteValue(p->left, val);

        if (val > p->data)
            return deleteValue(p->right, val);

        if (p->left == nullptr || p->right == nullptr)
            return p;

        Node* temp = getMaxValue(p->left);
        p->data = temp->data;
        return deleteValue(p->left, temp->data);
    }

    Node* searchValue(Node* p, int val)
    {
        if (p == nullptr || p->data == val)
            return p;
        else
            if (val > p->data)
                return searchValue(p->right, val);
            else
                return searchValue(p->left, val);
    }

    void preOrderTraversalNLR(Node*& p)
    {
        if (p == nullptr)
            return;

        if (p->parent == nullptr)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is root" << endl;
        else if (p->parent->left == p)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "left child" << endl;
        else
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "right child" << endl;

        preOrderTraversalNLR(p->left);
        preOrderTraversalNLR(p->right);
    }

    void inOrderTraversalLNR(Node*& p)
    {
        if (p == nullptr)
            return;

        inOrderTraversalLNR(p->left);
        if (p->parent == nullptr)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is root" << endl;
        else if (p->parent->left == p)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "left child" << endl;
        else
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "right child" << endl;
        inOrderTraversalLNR(p->right);
    }

    void postOrderTraversalLRN(Node*& p)
    {
        if (p == nullptr)
            return;

        postOrderTraversalLRN(p->left);
        postOrderTraversalLRN(p->right);
        if (p->parent == nullptr)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is root" << endl;
        else if (p->parent->left == p)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "left child" << endl;
        else
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "right child" << endl;
    }

    void preOrderTraversalNRL(Node*& p)
    {
        if (p == nullptr)
            return;

        if (p->parent == nullptr)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is root" << endl;
        else if (p->parent->left == p)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "left child" << endl;
        else
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "right child" << endl;
        preOrderTraversalNRL(p->right);
        preOrderTraversalNRL(p->left);
    }

    void inOrderTraversalRNL(Node*& p)
    {
        if (p == nullptr)
            return;

        inOrderTraversalRNL(p->right);
        if (p->parent == nullptr)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is root" << endl;
        else if (p->parent->left == p)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "left child" << endl;
        else
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "right child" << endl;
        inOrderTraversalRNL(p->left);
    }

    void postOrderTraversalRLN(Node*& p)
    {
        if (p == nullptr)
            return;

        postOrderTraversalRLN(p->right);
        postOrderTraversalRLN(p->left);
        if (p->parent == nullptr)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is root" << endl;
        else if (p->parent->left == p)
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "left child" << endl;
        else
            cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") is " << p->parent->data << "(" << (p->parent->color ? "BLACK" : "RED") << ")" << "'s " << "right child" << endl;
    }

    void deleteDuplicates(Node* p)
    {
        if (p == nullptr)
            return;

        bool flag = false;

        Node* found = searchValue(p->left, p->data);
        if (found != nullptr && flag == false)
        {
            this->remove(p->data);
            flag = true;
        }

        found = searchValue(p->right, p->data);
        if (found != nullptr && flag == false)
        {
            this->remove(p->data);
            flag = true;
        }

        deleteDuplicates(p->left);
        deleteDuplicates(p->right);
    }

    void copyTree(Node* src, Node*& dest)
    {
        if (src == nullptr)
            dest = nullptr;
        else
        {
            dest = new Node(src->data);
            dest->data = src->data;
            dest->color = src->color;
            dest->left = src->left;
            dest->right = src->right;
            dest->parent = src->parent;
            copyTree(src->left, dest->left);
            copyTree(src->right, dest->right);
        }
    }

    void printTree(const string& prefix, Node* p, bool isLeft, string outer, string inner, string mid, string end)
    {
        if (p != nullptr)
        {
            cout << prefix;

            if (!isLeft && p->parent == nullptr)
                cout << mid;
            else if (isLeft && !p->parent->right)
                cout << inner;
            else if (isLeft && p->parent->right)
                cout << outer;
            else if (!isLeft)
                cout << inner;

            cout << p->data << (p->color ? "(BLACK)" : "(RED)") << endl;

            printTree(prefix + (isLeft ? end : "    "), p->left, true, outer, inner, mid, end);
            printTree(prefix + (isLeft ? end : "    "), p->right, false, outer, inner, mid, end);
        }
    }

    void destroyTree(Node*& p)
    {
        if (p == nullptr)
            return;
        destroyTree(p->left);
        destroyTree(p->right);
        cout << p->data << "(" << (p->color ? "BLACK" : "RED") << ") has been destroyed!" << endl;
        delete p;
        p = nullptr;
    }

public:
    RedBlackTree()
    {
        root = nullptr;
    }

    void insert(int val)
    {
        Node* p = new Node(val);
        root = insertValue(root, p);
        RebalanceInsert(p);
    }

    void remove(int val)
    {
        if (root == nullptr)
        {
            cout << "\tRed Black Tree is empty!\n";
            return;
        }

        Node* p = deleteValue(root, val);

        if (p != nullptr)
        {
            RebalanceDelete(p);
            cout << "\tValue " << val << " has been removed!\n";
        }
        else
            cout << "\tValue " << val << " does not exist!\n";
    }

    void search(int val)
    {
        if (root == nullptr)
        {
            cout << "\tRed Black Tree is empty!\n";
            return;
        }

        Node* p = searchValue(root, val);

        if (p == nullptr || p->data != val)
            cout << "\tValue " << val << " does not exist!\n";
        else
            cout << "\tValue " << p->data << (p->color ? "(BLACK)" : "(RED)") << " has been found!\n";
    }

    void preOrderNLR()
    {
        preOrderTraversalNLR(root);
        cout << endl;
    }

    void inOrderLNR()
    {
        inOrderTraversalLNR(root);
        cout << endl;
    }

    void postOrderLRN()
    {
        postOrderTraversalLRN(root);
        cout << endl;
    }

    void preOrderNRL()
    {
        preOrderTraversalNRL(root);
        cout << endl;
    }

    void inOrderRNL()
    {
        inOrderTraversalRNL(root);
        cout << endl;
    }

    void postOrderRLN()
    {
        postOrderTraversalRLN(root);
        cout << endl;
    }

    void removeGreaterNodes(int val)
    {
        if (root == nullptr)
        {
            cout << "\tRed Black Tree is empty!\n";
            return;
        }

        if (getMaxValue(root)->data > val)
        {
            while (getMaxValue(root)->data > val)
                this->remove(getMaxValue(root)->data);

            cout << "\n\tValues greater than " << val << " have been removed!\n\n";
        }
        else
            cout << "\tNo values greater than " << val << " exist!\n\n";
    }

    void displayParent(int val)
    {
        if (root == nullptr)
        {
            cout << "\tRed Black Tree is empty!\n";
            return;
        }

        Node* p = searchValue(root, val);

        if (p == nullptr)
            cout << "\tValue not found!\n";
        else if (p->parent == nullptr)
            cout << "\t" << p->data << " is a root node! It does not have a parent node!\n";
        else
            cout << "\tParent of Node " << p->data << (p->parent->color ? "(BLACK)" : "(RED)") << " is " << p->parent->data << (p->parent->color ? "(BLACK)" : "(RED)") << endl;
    }

    void readFromFile()
    {
        ifstream fin("input.txt");

        if (!fin.is_open())
            cout << "File does not exist!\n";
        else
        {
            int num = 0;
            while (!fin.eof())
            {
                fin >> num;
                this->insert(num);
            }
        }
        fin.close();
    }

    void removeDuplicates()
    {
        if (root == nullptr)
        {
            cout << "\tRed Black Tree is empty!\n";
            return;
        }

        deleteDuplicates(root);
    }

    void copy(RedBlackTree& RBTree)
    {
        if (root == nullptr)
        {
            cout << "\tRed Black Tree is empty!\n";
            return;
        }

        copyTree(root, RBTree.root);
    }

    void print()
    {
        if (root == nullptr)
        {
            cout << "\tRed Black Tree is empty!\n";
            return;
        }

        string inner(1, char(192));
        string outer(1, char(195));
        string mid(1, char(196));
        string end(1, char(179));

        string outer1 = outer + mid + mid + mid;
        string inner1 = inner + mid + mid + mid;
        string mid1 = mid + mid + mid + mid;
        string end1 = end + "   ";

        cout << endl;
        printTree("", root, false, outer1, inner1, mid1, end1);
        cout << endl;
    }

    ~RedBlackTree()
    {
        if (root != nullptr)
        {
            destroyTree(root);
            cout << "\nRed Black Tree has been successfully destroyed!\n\n";
        }
        else
            cout << "Red Black Tree is empty!\n\n";
             
    }
};

