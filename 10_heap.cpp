#include <bits/stdc++.h>
using namespace std;

class node {
    int data;
    node *left;
    node *right;

    public:
    node(int d) {
        data = d;
        left = right = nullptr;
    }

    friend class heapsort;
};

class heapsort {
    vector<int> arr;
    vector<int> heap;
    int num;
    node *root = nullptr;

    node *insertLevelOrder(int i) {
        if (i >= num) return nullptr;
        node *temp = new node(arr[i]);
        temp->left = insertLevelOrder(2 * i + 1);
        temp->right = insertLevelOrder(2 * i + 2);
        return temp;
    }

    node *findRightMost(node *root) {
        queue<node *> q;
        q.push(root);
        node *it = nullptr;
        while (!q.empty()) {
            it = q.front();
            q.pop();
            if (it->left) q.push(it->left);
            if (it->right) q.push(it->right);
        }
        return it;
    }

    node *deleteNode(node *root, int val) {
        if (!root) return nullptr;
        if (root->data == val && !root->left && !root->right) {
            delete root;
            return nullptr;
        }
        if (root->left) root->left = deleteNode(root->left, val);
        if (root->right) root->right = deleteNode(root->right, val);
        return root;
    }

    node *heapify(node *root) {
        if (!root) return root;
        root->left = heapify(root->left);
        root->right = heapify(root->right);

        if (root->left && root->left->data > root->data) {
            swap(root->data, root->left->data);
        }
        if (root->right && root->right->data > root->data) {
            swap(root->data, root->right->data);
        }
        return root;
    }

public:
    heapsort() {
        cout << "Enter number of elements: ";
        cin >> num;
        arr.resize(num);
        cout << "Enter elements:\n";
        for (int i = 0; i < num; i++) {
            cin >> arr[i];
        }
    }

    void buildHeap() {
        root = insertLevelOrder(0);
    }

    void sort() {
        for (int i = 0; i < num; i++) {
            // step 1: root node has greater value than child nodes
            root = heapify(root);
            
            // finding the last node of tree
            node *rightmost = findRightMost(root);

            // swap data of node
            swap(root->data, rightmost->data);
            
            // store in ans;
            heap.push_back(rightmost->data);
            
            // delete node from tree
            root = deleteNode(root, rightmost->data);
        }

        cout << "\nSorted elements: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

int main() {
    heapsort h;
    h.buildHeap();
    h.sort();
    return 0;
}
