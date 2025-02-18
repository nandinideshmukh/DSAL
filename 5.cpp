#include <iostream>
using namespace std;

struct Node {
    int key;
    string value;
    Node* next;

    Node(int k, string v) : key(k), value(v), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void insert(int key, string value) {
        Node* current = head;

        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
    }

    string find(int key) {
        Node* current = head;
        while (current) {
            if (current->key == key)
                return current->value;
            current = current->next;
        }
        return "Key not found";
    }

    void remove(int key) {
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev)
                    prev->next = current->next;
                else
                    head = current->next; // Deleting head node

                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Key not found\n";
    }

    // Display the linked list
    void display() {
        Node* current = head;
        while (current) {
            cout << "[" << current->key << " -> " << current->value << "] ";
            current = current->next;
        }
    }
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    LinkedList table[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    void insert(int key, string value) {
        int index = hashFunction(key);
        table[index].insert(key, value);
    }

    string find(int key) {
        int index = hashFunction(key);
        return table[index].find(key);
    }

    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket " << i << ": ";
            table[i].display();
            cout << endl;
        }
    }
};

int main() {
    HashTable dict;
    
    dict.insert(1, "nan");
    dict.insert(2, "san");
    dict.insert(11, "desh"); 
    dict.insert(13, "desh"); 
    
    cout << "Finding key 2: " << dict.find(2) << endl;

    cout << "Hash Table contents:\n";
    dict.display();

    cout << "Deleting key 1\n";
    dict.remove(1);

    cout << "Hash Table after deletion:\n";
    dict.display();

    return 0;
}

