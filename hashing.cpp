#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

int hashFunction(string name)
{
    return name.size() % 10;
}

class Data
{
public:
    string name;
    long number;
    Data(string _name = " ", long _number = 0)
    {
        name = _name;
        number = _number;
    }
    friend ostream &operator<<(ostream &out, const Data &d)
    {
        out << "Name: " << setw(10) << d.name << " Number: " << d.number << endl;
        return out;
    }
};

class HashTablewoR
{
    Data arr[10];

public:
    HashTablewoR()
    {
        fill_n(arr, 10, Data());
    }

    void insertData(string _name, long _number)
    {
        int hash = hashFunction(_name);
        int ogHash = hash;
        if (arr[hash].name == " ")
        {
            arr[hash] = Data(_name, _number);
        }
        else
        {
            while (true)
            {
                hash++;
                if (hash % 10 == ogHash)
                {
                    cout << "Table full!\n";
                    break;
                }
                if (arr[hash % 10].name == " ")
                {
                    arr[hash % 10] = Data(_name, _number);
                    break;
                }
            }
        }
    }

    void search(string _name)
    {
        int hash = hashFunction(_name);
        int ogHash = hash;
        while (true)
        {
            if (arr[hash % 10].name == _name)
            {
                cout << "Number: " << arr[hash % 10].number << endl;
                break;
            }
            hash++;
            if (hash % 10 == ogHash)
            {
                cout << "Not Found!\n";
                break;
            }
        }
    }

    void deleteEntry(string _name)
    {
        int hash = hashFunction(_name);
        int ogHash = hash;
        while (true)
        {
            if (arr[hash % 10].name == _name)
            {
                arr[hash % 10] = Data();
                cout << "Deleted.\n";
                break;
            }
            hash++;
            if (hash % 10 == ogHash)
            {
                cout << "Not Found!\n";
                break;
            }
        }
    }

    void display()
    {
        cout << "---------------------------------------------------------------------------------------\n";
        for (int i = 0; i < 10; i++)
        {
            cout << "Slot" << setw(2) << i << " " << arr[i];
        }
        cout << "---------------------------------------------------------------------------------------\n";
    }
};

class HashTablewR
{
    Data arr[10];

public:
    HashTablewR()
    {
        fill_n(arr, 10, Data());
    }

    void insertData(string _name, long _number)
    {
        int hash = hashFunction(_name);
        int ogHash = hash;
        if (arr[hash].name == " ")
        {
            arr[hash] = Data(_name, _number);
        }
        else
        {
            Data toBeCarried = Data(_name, _number);
            if (hashFunction(arr[hash].name) != hash)
            {
                toBeCarried = arr[hash];
                arr[hash] = Data(_name, _number);
            }
            while (true)
            {
                hash++;
                if (hash % 10 == ogHash)
                {
                    cout << "Table full!\n";
                    break;
                }
                if (arr[hash % 10].name == " ")
                {
                    arr[hash % 10] = toBeCarried;
                    break;
                }
            }
        }
    }

    void search(string _name)
    {
        int hash = hashFunction(_name);
        int ogHash = hash;
        while (true)
        {
            if (arr[hash % 10].name == _name)
            {
                cout << "Number: " << arr[hash % 10].number << endl;
                break;
            }
            hash++;
            if (hash % 10 == ogHash)
            {
                cout << "Not Found!\n";
                break;
            }
        }
    }

    void deleteEntry(string _name)
    {
        int hash = hashFunction(_name);
        int ogHash = hash;
        while (true)
        {
            if (arr[hash % 10].name == _name)
            {
                arr[hash % 10] = Data();
                cout << "Deleted.\n";
                break;
            }
            hash++;
            if (hash % 10 == ogHash)
            {
                cout << "Not Found!\n";
                break;
            }
        }
    }

    void display()
    {
        cout << "---------------------------------------------------------------------------------------\n";
        for (int i = 0; i < 10; i++)
        {
            cout << "Slot" << setw(2) << i << " " << arr[i];
        }
        cout << "---------------------------------------------------------------------------------------\n";
    }
};

int main()
{
    vector<Data> database = {Data("Nandini", 444444),Data("Tejas", 8237848905), Data("Daniel", 7798680188), Data("Abhinav", 8767033270), Data("Raghav", 1234567890)};
    HashTablewoR t1;
    HashTablewR t2;
    for (int i = 0; i < 4; i++)
    {
        t1.insertData(database[i].name, database[i].number);
        t2.insertData(database[i].name, database[i].number);
    }
    while (true)
    {
        cout << "\nEnter option:\n\n1. Insert\n2. Search\n3. Delete\n4. Display\n\n";
        int op;
        cin >> op;
        cout << endl;
        switch (op)
        {
        case 1:
        {
            string name;
            long number;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter number: ";
            cin >> number;
            t1.insertData(name, number);
            t2.insertData(name, number);
            break;
        }
        case 2:
        {
            string name;
            cout << "Enter name: ";
            cin >> name;
            t1.search(name);
            t2.search(name);
            break;
        }
        case 3:
        {
            string name;
            cout << "Enter name: ";
            cin >> name;
            t1.deleteEntry(name);
            t2.deleteEntry(name);
            break;
        }
        case 4:
        {
            t1.display();
            t2.display();
            break;
        }
        default:
        {
            return 0;
        }
        }
    }
    return 0;
}
