#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// reading byte by byte from file , therefore binary mode is used!
class database {
    int rollno;
    string name;
    char divi;
    string address;
    static int count;

public:
    database() {
        this->name = "";
        this->divi = '0';
        this->rollno = 0;
        this->address = "";
    }

    void input() {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter roll number: ";
        cin >> rollno;

        cout << "Enter division: ";
        cin >> divi;

        cin.ignore();
        cout << "Enter address: ";
        getline(cin, address);

        count++;
    }

    void output() {
        cout << "\nName of student: " << name
             << "\nRoll number: " << rollno
             << "\nDivision: " << divi
             << "\nAddress: " << address << endl;
    }

    friend class record;
};

int database::count = 0;

class record {
    string filename;
    database db;
    fstream f;

public:
    record() {
        cout << "Enter filename: ";
        cin >> filename;
        f.open(filename, ios::out | ios::binary);
        if (f)
            cout << "File created/opened successfully.\n";
        else
            cout << "Error opening file.\n";
        f.close();
    }

    void add() {
        f.open(filename, ios::app | ios::binary);
        db.input();
        f.write((char*)&db, sizeof(db));
        f.close();
    }

    void display() {
        f.open(filename, ios::in | ios::binary);

        if (!f) {
            cout << "File not found.\n";
            return;
        }

        bool found = false;
        while (f.read((char*)&db, sizeof(db))) {
            db.output();
            found = true;
        }

        if (!found)
            cout << "No records to display.\n";

        f.close();
    }

    void deletedb() {
        int rn = 0;
        cout << "\nEnter roll number of student you want to delete: ";
        cin >> rn;

        f.open(filename, ios::in | ios::binary);

        fstream store("temp.txt", ios::out | ios::binary);

        bool found = false;

        while (f.read((char*)&db, sizeof(db))) {
            if (db.rollno != rn) {
                store.write((char*)&db, sizeof(db));
            } else {
                found = true;
            }
        }

        f.close();
        store.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (found)
            cout << "Record deleted successfully.\n";
        else
            cout << "Record not found.\n";
    }
};

int main() {
    record r;
    int choice;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: r.add(); break;
            case 2: r.display(); break;
            case 3: r.deletedb(); break;
            case 4: cout<<"Exiting...";exit(0);
            default: cout << "Invalid choice\n";
        }
    }

    return 0;
}
