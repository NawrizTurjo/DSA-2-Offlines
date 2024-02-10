// Implementing Red-Black Tree in C++

#include <iostream>
#include "color.hpp"
using namespace std;

struct Node
{
    int data;
    string value;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};

typedef Node *NodePtr;

class RedBlackTree
{
private:
    NodePtr root;
    NodePtr TNULL;
    int size;

    void initializeNULLNode(NodePtr node, NodePtr parent)
    {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    // Preorder
    void preOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Inorder
    void inOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            inOrderHelper(node->left);
            string sColor = node->color ? "RED" : "BLACK";
            if (sColor == "RED")
                cout << hue::red << node->data << "=>" << node->value << endl;
            else
                cout << hue::white << node->data << "=>" << node->value << endl;
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    // NodePtr searchTreeHelper2(NodePtr node, int key)
    // {
    //     if (node == TNULL || key == node->data)
    //     {
    //         return node;
    //     }

    //     if (key < node->data)
    //     {
    //         return searchTreeHelper2(node->left, key);
    //     }
    //     return searchTreeHelper2(node->right, key);
    // }

    NodePtr searchTreeHelper(NodePtr node, int key)
    {
        while (node != TNULL && key != node->data)
        {
            if (key < node->data)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return node;
    }

    // For balancing the tree after deletion
    void deleteFix(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == 0)
                    {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == 0)
                    {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key)
    {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL)
        {
            if (node->data == key)
            {
                z = node;
            }

            if (node->data <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == TNULL)
        {
            cout << key << " not found" << endl;
            return;
        }
        size--;

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = maximum(z->left);
            y_original_color = y->color;
            x = y->left;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }

            rbTransplant(z, y);
            y->right = z->right;
            y->right->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0)
        {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == 1)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper1(NodePtr root, string indent, bool last)
    {
        if (root != TNULL)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper1(root->left, indent, false);
            printHelper1(root->right, indent, true);
        }
    }

    void printHelper(NodePtr root, string indent, bool last)
    {
        if (root != TNULL)
        {
            // string prefix = last ? "L----" : "R----";
            string sColor = root->color ? "RED" : "BLACK";
            if (sColor == "RED")
                cout << hue::red << root->data << "_" << root->value;

            else
                cout << hue::white << root->data << "_" << root->value;

            if (root->left != TNULL || root->right != TNULL)
            {
                cout << "(";
            }
            printHelper(root->left, "", false);
            if (root->left != TNULL || root->right != TNULL)
            {
                cout << ",";
            }
            printHelper(root->right, "", true);
            if (root->left != TNULL || root->right != TNULL)
            {
                cout << ")";
            }
            // }
        }
    }

public:
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        size = 0;
    }

    int getSize()
    {
        return this->size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void preorder()
    {
        preOrderHelper(this->root);
    }

    void inorder()
    {
        inOrderHelper(this->root);
    }

    void postorder()
    {
        postOrderHelper(this->root);
    }

    NodePtr searchTree(int k)
    {
        return searchTreeHelper(this->root, k);
    }

    NodePtr minimum(NodePtr node)
    {
        while (node->left != TNULL)
        {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != TNULL)
        {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x)
    {
        if (x->right != TNULL)
        {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x)
    {
        if (x->left != TNULL)
        {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x)
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(int key, string val)
    {
        Node *res = searchTreeHelper(root, key);
        if (res != TNULL)
        {
            res->value = val;
            return;
        }
        size++;
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;
        node->value = val;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        insertFix(node);
    }

    NodePtr getRoot()
    {
        return this->root;
    }

    void deleteNode(int data)
    {
        deleteNodeHelper(this->root, data);
    }

    void printTree()
    {
        if (root)
        {
            printHelper(this->root, "", true);
            cout << endl;
        }
    }

    void clear()
    {
        if (root == TNULL)
        {
            cout << "unsuccesful" << endl;
            return;
        }
        while (root != TNULL)
        {
            deleteNode(root->data);
        }
    }

    void search(int key)
    {
        NodePtr res = searchTreeHelper(root, key);
        if (res == TNULL)
        {
            cout << key << " not found" << endl;
        }
        else
        {
            cout << key << " found" << endl;
        }
    }
};

int main()
{
    RedBlackTree bst;
    bst.clear();
    bst.isEmpty() ? cout << "yes" << endl : cout << "no" << endl;
    bst.insert(10, "Thors");
    bst.printTree();
    bst.insert(34, "Canute");
    bst.printTree();
    bst.insert(43, "Olaf");
    bst.printTree();
    bst.insert(15, "Einer");
    bst.printTree();
    bst.insert(40, "Olmar");
    bst.printTree();
    bst.insert(53, "Floki");
    bst.printTree();
    cout << bst.getSize() << endl;
    bst.insert(90, "Thorfin");
    bst.printTree();
    bst.insert(12, "Snake");
    bst.printTree();
    bst.insert(78, "Askeladd");
    bst.printTree();
    bst.search(40);
    // bst.printTree();

    // bst.clear();
    // bst.printTree();

    bst.deleteNode(40);
    bst.printTree();
    bst.deleteNode(78);
    bst.printTree();
    cout << bst.getSize() << endl;
    bst.deleteNode(12);
    bst.printTree();
    bst.deleteNode(43);
    bst.printTree();
    bst.isEmpty() ? cout << "yes" << endl : cout << "no" << endl;
    bst.deleteNode(56);
    bst.printTree();

    bst.insert(15, "Ymir");
    bst.printTree();

    bst.inorder();

    bst.deleteNode(40);
    bst.printTree();

    bst.clear();
    bst.printTree();
    bst.isEmpty() ? cout << "yes" << endl : cout << "no" << endl;
}