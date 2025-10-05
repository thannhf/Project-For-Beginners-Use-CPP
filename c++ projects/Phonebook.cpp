#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

struct Contact {
    string name;
    string phone;
    string mobile;
    string fax;
    string email;
    string address;
};

Contact contacts[50];
int counter = -1;

// kiểm tra trùng tên, cho phép bỏ qua 1 contact khi update
int validateContact(string tmpName, int ignoreIndex = -1) {
    for (int i = 0; i <= counter; i++) {
        if (contacts[i].name == tmpName && i != ignoreIndex) {
            return 0; // đã tồn tại
        }
    }
    return 1;
}

void addContact() {
    string tmpName;
    cout << "Enter Name: ";
    cin >> tmpName;

    if (validateContact(tmpName) == 1) {
        counter++;
        contacts[counter].name = tmpName;
    } else {
        cout << endl << "Contact Already Exists with this Name" << endl;
        return;
    }

    cout << "Enter Phone no: ";
    cin >> contacts[counter].phone;
    cout << "Enter Mobile no: ";
    cin >> contacts[counter].mobile;
    cout << "Enter Fax no: ";
    cin >> contacts[counter].fax;
    cout << "Enter Email: ";
    cin >> contacts[counter].email;
    cin.ignore(); // bỏ ký tự \n còn sót
    cout << "Enter Address: ";
    getline(cin, contacts[counter].address);
}

void print(int tmpCounter) {
    if (tmpCounter < 0 || tmpCounter > counter) return;
    cout << "Name: " << contacts[tmpCounter].name << endl;
    cout << "Phone No: " << contacts[tmpCounter].phone << endl;
    cout << "Mobile No: " << contacts[tmpCounter].mobile << endl;
    cout << "Fax No: " << contacts[tmpCounter].fax << endl;
    cout << "Email: " << contacts[tmpCounter].email << endl;
    cout << "Address: " << contacts[tmpCounter].address << endl;
    cout << "Press any key to continue..." << endl << endl;
    getch();
}

void printAll() {
    if (counter > -1) {
        for (int i = 0; i <= counter; i++) {
            print(i);
        }
    } else {
        cout << "No contacts found!" << endl;
        getch();
    }
}

void updateContact(int tmpCounter) {
    string tmpName;
    cout << "Enter New Name: ";
    cin >> tmpName;

    if (validateContact(tmpName, tmpCounter)) {
        contacts[tmpCounter].name = tmpName;
    } else {
        cout << endl << "Contact Already Exists with this name" << endl;
        return;
    }

    cout << "Enter Phone no: ";
    cin >> contacts[tmpCounter].phone;
    cout << "Enter Mobile no: ";
    cin >> contacts[tmpCounter].mobile;
    cout << "Enter Fax no: ";
    cin >> contacts[tmpCounter].fax;
    cout << "Enter Email: ";
    cin >> contacts[tmpCounter].email;
    cin.ignore();
    cout << "Enter Address: ";
    getline(cin, contacts[tmpCounter].address);
}

void deleteContact(int tmpCounter) {
    if (tmpCounter < 0 || tmpCounter > counter) return;
    for (int i = tmpCounter; i < counter; i++) {
        contacts[i] = contacts[i + 1]; // shift
    }
    counter--;
    cout << "Contact deleted successfully." << endl;
    getch();
}

int findCounter() {
    if (counter < 0) return -1;
    string tmpName;
    cout << "Enter Name: ";
    cin >> tmpName;

    for (int i = 0; i <= counter; i++) {
        if (contacts[i].name == tmpName) {
            return i;
        }
    }
    return -1; // không tìm thấy
}

int main() {
    char op;
    do {
        system("cls");
        cout << "===== CONTACT MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. List Contacts" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Update Contact" << endl;
        cout << "5. Delete Contact" << endl;
        cout << "6. Exit" << endl << endl;
        cout << "Enter Option (1-6): ";
        cin >> op;

        switch (op) {
            case '1': {
                addContact();
                cout << "Contact added successfully..." << endl;
                cout << "Press any key to continue";
                getch();
                break;
            }
            case '2': {
                printAll();
                break;
            }
            case '3': {
                int tmpCounter = findCounter();
                if (tmpCounter > -1) {
                    print(tmpCounter);
                } else {
                    cout << "Contact not found!" << endl;
                    getch();
                }
                break;
            }
            case '4': {
                int tmpCounter = findCounter();
                if (tmpCounter > -1) {
                    updateContact(tmpCounter);
                } else {
                    cout << "Contact not found!" << endl;
                    getch();
                }
                break;
            }
            case '5': {
                int tmpCounter = findCounter();
                if (tmpCounter > -1) {
                    deleteContact(tmpCounter);
                } else {
                    cout << "Contact not found!" << endl;
                    getch();
                }
                break;
            }
            case '6': {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid option! Try again." << endl;
                getch();
            }
        }
    } while (op != '6');
    return 0;
}
