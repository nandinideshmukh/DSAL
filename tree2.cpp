//============================================================================
// Name        : assgn2.cpp
// Author      : Nandini Deshmukh
// Version     :
// Copyright   : Your copyright notice
// Description : 

// Problem statement:
/// Beginning with an empty binary tree, Construct binary tree by inserting
// the values in the order given. After constructing a binary tree perform
// following operations on it-
//  Perform inorder, preorder and post order traversal
//  Change a tree so that the roles of the left and right pointers are
// swapped at every node
//  Find the height of tree
//  Copy this tree to another [operator=]
//  Count number of leaves, number of internal nodes.
//  Erase all nodes in a binary tree.
//(Implement both recursive and non-recursive methods)


#include <iostream>
#include <stack>
using namespace std;

class treenode {
    int data;
    treenode *left, *right;

public:
    treenode(int d) {
        data = d;
        left = right = nullptr;
    }

	treenode* clone_node(const treenode* src) {
		if (src == nullptr) return nullptr;
		treenode* clonedNode = new treenode(src->data);
		clonedNode->left = clone_node(src->left);
		clonedNode->right = clone_node(src->right);
		return clonedNode;
	}
	
	treenode operator=(const treenode& other) {
		if (this == &other) 
		{
			return *this;
		}
		this->data = other.data;
		
		this->left = clone_node(other.left);
		this->right = clone_node(other.right);

		return *this;
	}

    friend class assgn;
};

class assgn {
	treenode* root;

	public:

    // Create tree
    treenode* create(treenode* root) {
        int data;
        cout << "\nEnter the node data: ";
        cin >> data;
        if (data == -1) return nullptr;

        root = new treenode(data);

        cout << "\nEnter left child of: " << data;
        root->left = create(root->left);

        cout << "\nEnter right child of: " << data;
        root->right = create(root->right);

        return root;
    }

    // Inorder Traversal (Recursive)
    void rinorder(treenode* root) {
        if (!root) return;
        rinorder(root->left);
        cout << "\nData: " << root->data;
        rinorder(root->right);
    }

    // Preorder Traversal (Recursive)
    void rpreorder(treenode* root) {
        if (!root) return;
        cout << "\nData: " << root->data;
        rpreorder(root->left);
        rpreorder(root->right);
    }

    // Postorder Traversal (Recursive)
    void rpostorder(treenode* root) {
        if (!root) return;
        rpostorder(root->left);
        rpostorder(root->right);
        cout << "\nData: " << root->data;
    }

    // Non-recursive Inorder Traversal
    void iinorder(treenode* root) {
        stack<treenode*> st;
        treenode* current = root;
        while (current != nullptr || !st.empty()) {
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
            current = st.top();
            st.pop();
            cout << current->data << endl;
            current = current->right;
        }
    }
void ipreorder(treenode *root){
  stack<treenode *> st;
  st.push(root);
	while (!st.empty())
	{
		while (root)
		{
			cout << "\nData: "<<root->data << endl;
			if (root->right)
			st.push(root->right);
			root = root->left;
		}
		root = st.top();
		st.pop();
  }
 }

    // Non-recursive Postorder Traversal
    void ipostorder(treenode* root) {
        stack<treenode*> st1, st2;
        if (root) st1.push(root);
        while (!st1.empty()) {
            treenode* node = st1.top();
            st1.pop();
            st2.push(node);
            if (node->left) st1.push(node->left);
            if (node->right) st1.push(node->right);
        }
        while (!st2.empty()) {
            treenode* node = st2.top();
            st2.pop();
            cout << "\nData: "<<node->data << endl;
        }
    }

    // Clone a tree recursively
    treenode* rclone(treenode* root) {
        if (root == nullptr) return nullptr;
        treenode* newNode = new treenode(root->data);
        newNode->left = rclone(root->left);
        newNode->right = rclone(root->right);
        return newNode;
    }

    // Calculate height of the tree recursively
    int rheight(treenode* root) {
        if (root == nullptr) return 0;
        int leftHeight = rheight(root->left);
        int rightHeight = rheight(root->right);
        return max(leftHeight, rightHeight) + 1;
    }

    // Count number of leaf nodes
    int rcount_leaves(treenode* root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 1;
        return rcount_leaves(root->left) + rcount_leaves(root->right);
    }

    // Count number of internal nodes
    int rcount_internal(treenode* root) {
        if (root == nullptr) return 0;
        if (root->left != nullptr || root->right != nullptr) return 1 + rcount_internal(root->left) + rcount_internal(root->right);
        return 0;
    }

    // Erase all nodes of the tree
    void rerase(treenode*& root) {
        if (root == nullptr) return;
        rerase(root->left);
        rerase(root->right);
        delete root;
        root = nullptr;
    }

	void rswap(treenode *root){
	if (root == nullptr)
	return;
	if (root->left || root->right)
	{
		treenode *temp = root->left;
		root->left = root->right;
		root->right = temp;
	}
	rswap(root->left);
	rswap(root->right);
	}
};

int main() {
    assgn bt;
    treenode* root = nullptr;
    int ch;
    
    do {
        cout << "Enter your choice :\n0. Create tree \n1. Inorder traversal \n2. Preorder traversal \n3. Post-order traversal \n4. Swap nodes \n5. Height of tree ";
        cout << "\n6. Copying a tree \n7. Count number of leaf nodes \n8. Count number of internal nodes \n9. Erase all nodes! \n10. Exit\n";
        cin >> ch;

        if (ch == 0) {
            root = bt.create(root);
        }

        else if (ch == 1) {
            bt.rinorder(root);
        }

        else if (ch == 2) {
            bt.rpreorder(root);
        }

        else if (ch == 3) {
            bt.rpostorder(root);
        }

        else if (ch == 4) {
         	bt.rswap(root);
		 	bt.iinorder(root);   
        }

        else if (ch == 5) {
            int height = bt.rheight(root);
            cout << "\nHeight of tree is: " << height - 1 << endl;
        }

        else if (ch == 6) {
			treenode* copied = root;
			bt.iinorder(copied);
            // treenode* copied = bt.rclone(root);
            // bt.rinorder(copied);
        }

        else if (ch == 7) {
            int leaf = bt.rcount_leaves(root);
            cout << "\nNumber of leaf nodes in the tree are: " << leaf << endl;
        }

        else if (ch == 8) {
            int internal = bt.rcount_internal(root);
            cout << "\nNumber of internal nodes in the tree are: " << internal << endl;
        }

        else if (ch == 9) {
            bt.rerase(root);
            root = nullptr;
            bt.rinorder(root); 
        }

        else if (ch == 10) {
            cout<<"\n\nExiting...\n";
			return 0;
        }

    } while (ch != 10);

    return 0;
}
