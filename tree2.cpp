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
#include <bits/stdc++.h>
using namespace std;

class treenode
{
	int data;
	treenode *left, *right;

public:
	treenode(int d)
	{
		data = d;
		left = right = nullptr;
	}

	friend class assgn;
};

class assgn
{
public:
	treenode *create(treenode *root)
	{
		int data;
		cout << "\nEnter the root node: ";
		cin >> data;
		root = new treenode(data);

		if (data == -1)
			return nullptr;
		cout << "\nEnter left child of: " << data;
		root->left = create(root->left);
		root->right = create(root->right);
	}

	void rinorder(treenode *root)
	{
		if (!root)
			return;
		rinorder(root->left);
		cout << "\nData: " << root->data;
		rinorder(root->right);
	}

	void rpostorder(treenode *root)
	{
		if (!root)
			return;
		rpostorder(root->left);
		rpostorder(root->right);
		cout << "\nData: " << root->data;
	}

	void rpreorder(treenode *root)
	{
		if (!root)
			return;
		cout << "\nData: " << root->data;
		rpostorder(root->left);
		rpostorder(root->right);
	}

	// Change a tree so that the roles of the left and right pointers are
	// swapped at every node
	void rswap(treenode *root)
	{
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

	// Find the height of tree
	int rheight(treenode *root)
	{
		if (!root)
			return 0;
		int l = rheight(root->left);
		int r = rheight(root->right);

		return max(l, r) + 1;
	}

	// Count number of number of internal nodes.
	int rcount_internal(treenode *root)
	{
		if (!root || (root->left == nullptr && root->right == nullptr))
			return 0;
		return 1 + rcount_internal(root->left) + rcount_internal(root->right);
	}

	// Count number of leaves
	int rcount_leaves(treenode *root)
	{
		queue<treenode *> q;
		q.push(root);
		// initializing count variable
		int count = 0;
		while (!q.empty())
		{
			treenode *temp = q.front();
			q.pop();

			if (temp->left == NULL && temp->right == NULL)
				count++;
			if (temp->left)
				q.push(temp->left);
			if (temp->right)
				q.push(temp->right);
		}
		return count;
	}

	// Erase all nodes in a binary tree.
	void rerase(treenode *root)
	{
		if (!root)
			return;
		rerase(root->left);
		rerase(root->right);
		root->left = nullptr;
		root->right = nullptr;
	}

	// Start iteratively now!
	// Preorder
	void ipreorder(treenode *root)
	{
		stack<treenode *> st;
		while (!st.empty())
		{
			while (root)
			{
				cout << root->data << endl;
				if (root->right)
					st.push(root->right);
				root = root->left;
			}
			root = st.top();
			st.pop();
		}
	}

	// Inorder
	void iinorder(treenode *root)
	{
		stack<treenode *> st;
		while (!st.empty())
		{
			while (root)
			{
				st.push(root);
				root = root->left;
			}
			cout << root->data << endl;
			root = root->right;
		}
	}

	void ipostorder(treenode *root)
	{
		treenode *temp = new treenode(-1);
		stack<treenode *> st;
		while (!st.empty())
		{
			while (root)
			{
				st.push(root);
				if (root->right)
				{
					st.push(root->right);
					st.push(temp);
				}
				root = root->left;
				while (!st.empty())
				{
					treenode *t = st.top();
					st.pop();

					if (t != temp)
						cout << t->data << endl;
					else
						break;
				}
				if (!st.empty())
					st.pop();
			}
		}
	}

	//  Change a tree so that the roles of the left and right pointers are
	// swapped at every node
	void iswap(treenode *root){
		// Implement karna hai ruko jara
	}
};

int main()
{

	return 0;
}
