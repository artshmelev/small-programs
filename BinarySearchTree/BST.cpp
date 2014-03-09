#include "BST.h"

#include <iostream>
using namespace std;

Node::Node()
{
    left = right = NULL;
}

Node::Node(int val)
{
    key = val;
    Node();
}

BST::BST()
{
    root = NULL;
}

BST::~BST()
{
    clear(root);
}

void BST::clear(Node* node)
{
    while (node != NULL)
    {
        clear(node->left);
        clear(node->right);
        delete node;
        node = NULL;
    }
}

void BST::inorderWalk()
{
    Node* node = root;    
    inorderWalk(node);
    cout << "\n";
}

void BST::inorderWalk(Node* node)
{    
    if (node != NULL)
    {
        inorderWalk(node->left);
        cout << node->key << " ";
        inorderWalk(node->right);
    }
}

void BST::insert(int val)
{
    Node* node = root;
    Node* parent = NULL;    
    while (node != NULL)
    {
        parent = node;        
        if (val < node->key) node = node->left;
        else node = node->right;
    }
    if (parent == NULL) root = new Node(val);
    else if (val < parent->key) parent->left = new Node(val);
    else parent->right = new Node(val);
}

Node* BST::search(int val)
{
    Node* node = root;
    while (node != NULL && node->key != val)
    {
        if (val == node->key) return node;
        else if (val < node->key) node = node->left;
        else node = node->right;
    }
    return node;
}

int BST::max()
{
    Node* node = root;
    if (root != NULL) 
    {  
        while (node->right != NULL) node = node->right;
        return node->key;
    }
    else return -1;
}

int BST::min()
{
    Node* node = root;
    if (root != NULL)
    {
        while (node->left != NULL) node = node->left;
        return node->key;
    }
    else return -1;
}

int BST::getRoot()
{
    return root->key;
}


