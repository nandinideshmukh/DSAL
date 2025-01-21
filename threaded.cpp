/*

Create an inordered threaded binary search tree. Perform inorder,
preorder traversals without recursion and deletion of a node. Analyze
time and space complexity of the algorithm.

*/

// Insertion in Threaded Binary Search Tree. 
#include<bits/stdc++.h> 
using namespace std; 

class Node 
{   
	struct Node *left, *right; 
	int info; 

	bool lthread; 
	
	bool rthread; 

    friend class threaded;
}; 

class threaded{
    public:
    Node *insert(Node* root,int key){
        Node *ptr = root; 
	Node *par = NULL; // Parent of key to be inserted 
	while (ptr != NULL) 
	{ 
		// If key already exists, return 
		if (key == (ptr->info)) 
		{ 
			printf("Duplicate Key !\n"); 
			return root; 
		} 

		par = ptr; // Update parent pointer 

		// Moving on left subtree. 
		if (key < ptr->info) 
		{ 
			if (ptr -> lthread == false) 
				ptr = ptr -> left; 
			else
				break; 
		} 

		// Moving on right subtree. 
		else
		{ 
			if (ptr->rthread == false) 
				ptr = ptr -> right; 
			else
				break; 
		} 
    }
	Node *tmp = new Node; 
	tmp -> info = key; 
	tmp -> lthread = true; 
	tmp -> rthread = true; 

	if (par == NULL) 
	{ 
		root = tmp; 
		tmp -> left = NULL; 
		tmp -> right = NULL; 
	} 
	else if (key < (par -> info)) 
	{ 
		tmp -> left = par -> left; 
		tmp -> right = par; 
		par -> lthread = false; 
		par -> left = tmp; 
	} 
	else
	{ 
		tmp -> left = par; 
		tmp -> right = par -> right; 
		par -> rthread = false; 
		par -> right = tmp; 
	} 

	return root;
    }

    Node *inorderSuccessor(Node *ptr) 
    { 
	if (ptr -> rthread == true) 
		return ptr->right; 

	ptr = ptr -> right; 
	while (ptr -> lthread == false) 
		ptr = ptr -> left; 

	return ptr; 
    }

    Node *inPred(Node *ptr){
        if (ptr -> lthread == true) 
		return ptr->left; 

	ptr = ptr -> left; 
	while (ptr -> rthread == false) 
		ptr = ptr -> right; 

	return ptr; 
    } 

    void inorder( Node *root) 
    { 
	if (root == NULL) 
		printf("Tree is empty"); 

	Node *ptr = root; 
	while (ptr -> lthread == false) 
		ptr = ptr -> left; 

	while (ptr != NULL) 
	{ 
		printf("%d ",ptr -> info); 
		ptr = inorderSuccessor(ptr); 
	} 
    }

void preorder(Node* root)
{
    if(root==NULL)
    {
    printf("Tree is empty");
    return;
    }
    Node* ptr = root;
    while(ptr!=NULL)
    {
    cout<<ptr->info<<" ";
    if(ptr->lthread==false)
    ptr=ptr->left;
    else if(ptr->rthread==false)
    ptr=ptr->right;
    else
    {
    while(ptr!=NULL && ptr->rthread==true)
    ptr=ptr->right;
    if(ptr!=NULL)
    ptr=ptr->right;
    }
}
}
    Node* caseA( Node* root,  Node* par, Node* ptr)
    {
    // If Node to be deleted is root
    if (par == NULL)
        root = NULL;
 
    // If Node to be deleted is left
    // of its parent
    else if (ptr == par->left) {
        par->lthread = true;
        par->left = ptr->left;
    }
    else {
        par->rthread = true;
        par->right = ptr->right;
    }
 
    // Free memory and return new root
    free(ptr);
    return root;
    }

    Node* caseB( Node* root,  Node* par, Node* ptr)
{
     Node* child;
 
    // Initialize child Node to be deleted has
    // left child.
    if (ptr->lthread == false)
        child = ptr->left;
 
    // Node to be deleted has right child.
    else
        child = ptr->right;
 
    // Node to be deleted is root Node.
    if (par == NULL)
        root = child;
 
    // Node is left child of its parent.
    else if (ptr == par->left)
        par->left = child;
    else
        par->right = child;
 
    // Find successor and predecessor
    Node* s = inorderSuccessor(ptr);
    Node* p = inPred(ptr);
 
    // If ptr has left subtree.
    if (ptr->lthread == false)
        p->right = s;
 
    // If ptr has right subtree.
    else {
        if (ptr->rthread == false)
            s->left = p;
    }
 
    free(ptr);
    return root;
}
    // Here 'par' is pointer to parent Node and 'ptr' is
// pointer to current Node.
Node* caseC( Node* root,  Node* par, Node* ptr)
{
	// Find inorder successor and its parent.
	 Node* parsucc = ptr;
	 Node* succ = ptr->right;

	// Find leftmost child of successor
	while (succ->left != NULL) {
		parsucc = succ;
		succ = succ->left;
	}

	ptr->info = succ->info;

	if (succ->lthread == true && succ->rthread == true)
		root = caseA(root, parsucc, succ);
	else
		root = caseB(root, parsucc, succ);

	return root;
    }

    Node* delThreadedBST( Node* root, int key)
    {
    // Initialize parent as NULL and ptrent
    // Node as root.
     Node *par = NULL, *ptr = root;
 
    // Set true if key is found
    int found = 0;
 
    // Search key in BST : find Node and its
    // parent.
    while (ptr != NULL) {
        if (key == ptr->info) {
            found = 1;
            break;
        }
        par = ptr;
        if (key < ptr->info) {
            if (ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }
        else {
            if (ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }
 
    if (found == 0)
        printf("\nkey not present in tree\n");
 
    // Two Children
    else if (ptr->lthread == false && ptr->rthread == false)
        root = caseC(root, par, ptr);
 
    // Only Left Child
    else if (ptr->lthread == false)
        root = caseB(root, par, ptr);
 
    // Only Right Child
    else if (ptr->rthread == false)
        root = caseB(root, par, ptr);
 
    // No child
    else
        root = caseA(root, par, ptr);
 
    return root;
}

};

int main(){
    threaded td;
    Node *root = NULL; 
  
    root = td.insert(root, 20); 
    root = td.insert(root, 10); 
    root = td.insert(root, 30); 
    root = td.insert(root, 5); 
    root = td.insert(root, 16); 
    root = td.insert(root, 14); 
    root = td.insert(root, 17); 
    root = td.insert(root, 13); 

    td.preorder(root);
    cout<<endl;
    root = td.delThreadedBST(root, 10);
    // inorder(root);
    td.inorder(root);

    return 0;
}




