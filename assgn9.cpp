
/*

A dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords,
updating values of an entry. Provide facility to display whole data in sorted Ascending / Descending order.
Also find out how many comparisons are required for finding any entry. Use height balance tree and find
complexity for finding a keyword.

 */

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int key;
    string value;
    int height = 1;
    Node *left = nullptr;
    Node *right = nullptr;
};

class AVLTree
{
public:
    int getBalanceFactor(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
    int height(Node *N)
    {
        if (!N)
            return 0;
        return N->height;
    }
    int getBalance(Node *N)
    {
        if (!N)
            return 0;
        return height(N->left) - height(N->right);
    }
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }
    Node *insertToAVL(Node *node, int data, string key)
    {
        if (node == NULL)
        {
            node = new Node;
            node->key = data;
            node->value = key;
            return node;
        }

        if (key < node->value)
            node->left = insertToAVL(node->left, data, key);
        else if (key > node->value)
            node->right = insertToAVL(node->right, data, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->value)
            return rightRotate(node);

        if (balance < -1 && key > node->right->value)
            return leftRotate(node);

        if (balance > 1 && key > node->left->value)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    void iinorder(Node *root)
    {
        if (root == nullptr)
            return;
        iinorder(root->left);
        cout << root->key << " ";
        iinorder(root->right);
    }

    Node *minValueNode(Node *node)
    {
        Node *curr = node;
        while (curr->left != nullptr)
            curr = curr->left;

        return curr;
    }
    Node *search(Node *root, int key)
    {
        Node *curr = root;
        while (curr != nullptr)
        {
            if (key > curr->key)
                curr = curr->right;
            else if (key < curr->key)
                curr = curr->left;
            else
                return curr;
        }
        return nullptr;
    }

    Node *deleteNode(Node *root, int key)
    {
        // STEP 1: PERFORM STANDARD BST DELETE

        if (root == NULL)
            return root;

        // If the key to be deleted is smaller than the
        // root's key, then it lies in left subtree
        if (key < root->key)
            root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater than the
        // root's key, then it lies in right subtree
        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then This is
        // the node to be deleted
        else
        {
            // node with only one child or no child
            if ((root->left == NULL) || (root->right == NULL))
            {
                struct Node *temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                struct Node *temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == NULL)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
};
int main()
{
    AVLTree t;
    Node *root = nullptr;
    root = t.insertToAVL(root, 1, "hello");
    root = t.insertToAVL(root, 2, "i");
    root = t.insertToAVL(root, 3, "ij");
    root = t.insertToAVL(root, 4, "kl");
    root = t.insertToAVL(root, 5, "mn");
    root = t.insertToAVL(root, 6, "op");
    root = t.insertToAVL(root, 7, "qr");

    t.iinorder(root);
    cout << endl;
    t.preOrder(root);
    cout << endl;
    root = t.deleteNode(root, 3);
    t.iinorder(root);
    cout<<endl;
    t.preOrder(root);
    cout << endl;
    return 0;
}