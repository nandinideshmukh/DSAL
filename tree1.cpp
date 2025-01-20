#include <iostream>
#include <bits/stdc++.h>

using namespace std;


/*

BST operations: 

1.Insert
2. Nodes in longest path from root
3. Swap pointers of root node(left right)
4. Minimum data value found in the tree
5. Search a value in tree
6. Delete a node 

*/
class treenode{
    int data;
    treenode *left , *right;

    public:
    treenode(int d){
        data = d;
        left = right = nullptr;
    }
    friend class bst;
};

class bst{
    public:
    
    treenode* insert(treenode* root, int key) {

    if (root == NULL) 
        return new treenode(key);    
    
    if (root->data == key) 
        return root;
    
    if (root->data < key) 
        root->right = insert(root->right, key);
    
    else 
        root->left = insert(root->left, key);
    
    return root;
    }

    void inorder(treenode* root) {
        if (!root) return;

        inorder(root->left);
        cout << "\nData: " << root->data;
        inorder(root->right);
    }

    int rheight(treenode* root) {
        if (root == nullptr) return 0;
        int leftHeight = rheight(root->left);
        int rightHeight = rheight(root->right);

        return max(leftHeight, rightHeight) + 1;
    }

    void rswap(treenode *root){

        if(!root) return;

        if(root->left || root->right){
            treenode * t = root->left;
            root->left = root->right;
            root->right = t;
        }
        rswap(root->left);
        rswap(root->right);
    }

    int minValue(treenode* root) {
  
    if (root == nullptr) {
        cout<<"\nNo node present in the tree! \n";
        return -1;
    }

    treenode* curr = root;

    while (curr->left != nullptr) {
        curr = curr->left;
    }

    return curr->data;
    }

    treenode* rsearch(treenode* root, int key) {

    if (root == NULL || root->data == key)
        return root;

    if (root->data < key)
        return rsearch(root->right, key);

    return rsearch(root->left, key);
    }

    treenode* getSuccessor(treenode* root){
    treenode *curr = root->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
    }

    // This function deletes a given key x from
    // the give BST and returns modified root of
    // the BST (if it is modified)
    treenode* delNode(treenode* root, int x){

    // Base case
    if (root == nullptr)
        return root;

    // If key to be searched is in a subtree
    if (root->data > x)
        root->left = delNode(root->left, x);
    else if (root->data < x)
        root->right = delNode(root->right, x);

    // If root matches with the given key
    else {

        // Cases when root has 0 children
        // or only right child
        if (root->left == nullptr) {
            treenode* temp = root->right;
            delete root;
            return temp;
        }

        // When root has only left child
        if (root->right == nullptr) {
            treenode* temp = root->left;
            delete root;
            return temp;
        }

        treenode* succ = getSuccessor(root);
        root->data = succ->data;
        root->right = delNode(root->right, succ->data);
    }
    return root;
    }

};

int main() {
    bst bt;
    treenode* root = nullptr;

    root = bt.insert(root, 50);
    root = bt.insert(root, 30);
    root = bt.insert(root, 20);
    root = bt.insert(root, 40);
    root = bt.insert(root, 70);
    root = bt.insert(root, 60);
    root = bt.insert(root, 80);

    cout << "\nInorder Traversal: ";
    bt.inorder(root);

    cout << "\n\nNodes in the maximum path length of tree: " << bt.rheight(root);

    cout << "\n\nMinimum Value: " << bt.minValue(root);

    cout << "\n\nSwapping left and right children...";
    bt.rswap(root);
    cout << "\n\nInorder Traversal After Swap: ";
    bt.inorder(root);

    bt.rswap(root);
    cout << "\n\nDeleting 20...";
    treenode* deleted = bt.delNode(root, 20);
    cout << "\n\nIn-order Traversal After Deletion: ";
    bt.inorder(root);
    cout<<endl;

    return 0;
}


