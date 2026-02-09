#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Contact {
public:
    string name, phone, email;

    void input() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "Enter Email: ";
        cin >> email;
    }

    void display() const {
        cout << left << setw(20) << name
             << setw(15) << phone
             << email << endl;
    }
};

void addContact() {
    Contact c;
    ofstream fout("contacts.txt", ios::app);

    if (!fout) {
        cout << "File error!\n";
        return;
    }

    c.input();
    fout << c.name << "|" << c.phone << "|" << c.email << endl;

    fout.close();
    cout << "\nContact Added Successfully!\n";
}

void viewContacts() {
    Contact c;
    ifstream fin("contacts.txt");

    if (!fin) {
        cout << "No contacts found!\n";
        return;
    }

    cout << "\nName                 Phone          Email\n";
    cout << "------------------------------------------------\n";

    while (getline(fin, c.name, '|')) {
        getline(fin, c.phone, '|');
        getline(fin, c.email);
        c.display();
    }

    fin.close();
}

void searchContact() {
    ifstream fin("contacts.txt");
    string search;
    bool found = false;

    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, search);

    Contact c;

    while (getline(fin, c.name, '|')) {
        getline(fin, c.phone, '|');
        getline(fin, c.email);

        if (c.name == search) {
            cout << "\nContact Found:\n";
            c.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nContact Not Found!\n";

    fin.close();
}

void deleteContact() {
    ifstream fin("contacts.txt");
    ofstream fout("temp.txt");

    string delName;
    bool found = false;

    cout << "Enter name to delete: ";
    cin.ignore();
    getline(cin, delName);

    Contact c;

    while (getline(fin, c.name, '|')) {
        getline(fin, c.phone, '|');
        getline(fin, c.email);

        if (c.name != delName) {
            fout << c.name << "|" << c.phone << "|" << c.email << endl;
        } else {
            found = true;
        }
    }

    fin.close();
    fout.close();

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found)
        cout << "\nContact Deleted Successfully!\n";
    else
        cout << "\nContact Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n====== Contact Management System ======\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addContact(); break;
        case 2: viewContacts(); break;
        case 3: searchContact(); break;
        case 4: deleteContact(); break;
        case 5: cout << "Exiting Program...\n"; break;
        default: cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
