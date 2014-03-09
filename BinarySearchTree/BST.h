//        Average | Worth case
// Space  O(N)    | O(N)
// Search O(logN) | O(N)
// Insert O(logN) | O(N)
// Delete O(logN) | O(N)

#ifndef BST_H
#define BST_H

class Node
{
public:
    int key;
    Node* left;
    Node* right;

    Node();
    Node(int val);
};

class BST
{
private:
    Node* root;

    void inorderWalk(Node* node);
    void clear(Node* node);
public:
    BST();
    ~BST();
    void inorderWalk();
    void insert(int val);
    Node* search(int val);
    int max();
    int min();
    int getRoot();
};

#endif

