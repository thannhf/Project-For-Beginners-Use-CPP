#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

struct Room {
    int roomNo;
    string roomCode;
    char status;    
    float tariff;

    void display() const {
        cout << left << setw(10) << roomNo
             << setw(10) << roomCode
             << setw(12) << (status == 'A' ? "Available" : "Occupied")
             << setw(10) << tariff << endl;
    }
};

struct Customer {
    string name;
    string phone;
    int roomNo;
    float advance;
    float misc;

    void display() const {
        cout << left << setw(20) << name
             << setw(12) << phone
             << setw(10) << roomNo
             << setw(10) << advance
             << setw(10) << misc << endl;
    }
};

class HotelManagement {
private:
    vector<Room> rooms;
    vector<Customer> customers;

    // ===== File handling =====
    void loadRooms() {
        rooms.clear();
        ifstream in("rooms.dat", ios::binary);
        if (!in) return;
        Room r;
        while (in.read((char*)&r, sizeof(Room))) {
            rooms.push_back(r);
        }
        in.close();
    }

    void saveRooms() {
        ofstream out("rooms.dat", ios::binary | ios::trunc);
        for (auto &r : rooms)
            out.write((char*)&r, sizeof(Room));
        out.close();
    }

    void loadCustomers() {
        customers.clear();
        ifstream in("customers.dat", ios::binary);
        if (!in) return;
        Customer c;
        while (in.read((char*)&c, sizeof(Customer))) {
            customers.push_back(c);
        }
        in.close();
    }

    void saveCustomers() {
        ofstream out("customers.dat", ios::binary | ios::trunc);
        for (auto &c : customers)
            out.write((char*)&c, sizeof(Customer));
        out.close();
    }

public:
    HotelManagement() {
        loadRooms();
        loadCustomers();
    }

    ~HotelManagement() {
        saveRooms();
        saveCustomers();
    }

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    // ===== ROOM CRUD =====
    void addRoom() {
        Room r;
        cout << "Enter room number: ";
        cin >> r.roomNo;
        cout << "Enter room code: ";
        cin >> r.roomCode;
        cout << "Enter tariff: ";
        cin >> r.tariff;
        r.status = 'A';
        rooms.push_back(r);
        cout << "Room added successfully!\n";
    }

    void listRooms() {
        cout << left << setw(10) << "RoomNo"
             << setw(10) << "Code"
             << setw(12) << "Status"
             << setw(10) << "Tariff" << endl;
        for (auto &r : rooms) r.display();
    }

    void modifyRoom() {
        int rno;
        cout << "Enter room number to modify: ";
        cin >> rno;
        for (auto &r : rooms) {
            if (r.roomNo == rno) {
                cout << "Enter new code: ";
                cin >> r.roomCode;
                cout << "Enter new tariff: ";
                cin >> r.tariff;
                cout << "Enter status (A=Available, O=Occupied): ";
                cin >> r.status;
                cout << "Room updated successfully!\n";
                return;
            }
        }
        cout << "Room not found!\n";
    }

    void deleteRoom() {
        int rno;
        cout << "Enter room number to delete: ";
        cin >> rno;
        for (auto it = rooms.begin(); it != rooms.end(); ++it) {
            if (it->roomNo == rno) {
                rooms.erase(it);
                cout << "Room deleted successfully!\n";
                return;
            }
        }
        cout << "Room not found!\n";
    }

    // ===== CUSTOMER CRUD =====
    void addCustomer() {
        Customer c;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, c.name);
        cout << "Enter phone: ";
        cin >> c.phone;
        cout << "Enter room number: ";
        cin >> c.roomNo;
        cout << "Advance payment: ";
        cin >> c.advance;
        c.misc = 0.0;
        customers.push_back(c);

        for (auto &r : rooms) {
            if (r.roomNo == c.roomNo) r.status = 'O';
        }

        cout << "Customer added successfully!\n";
    }

    void listCustomers() {
        cout << left << setw(20) << "Name"
             << setw(12) << "Phone"
             << setw(10) << "RoomNo"
             << setw(10) << "Advance"
             << setw(10) << "Misc" << endl;
        for (auto &c : customers) c.display();
    }

    void modifyCustomer() {
        string name;
        cout << "Enter customer name to modify: ";
        cin.ignore();
        getline(cin, name);
        for (auto &c : customers) {
            if (c.name == name) {
                cout << "Enter new phone: ";
                cin >> c.phone;
                cout << "Enter new room number: ";
                cin >> c.roomNo;
                cout << "Enter new advance: ";
                cin >> c.advance;
                cout << "Enter misc charges: ";
                cin >> c.misc;
                cout << "Customer updated successfully!\n";
                return;
            }
        }
        cout << "Customer not found!\n";
    }

    void deleteCustomer() {
        string name;
        cout << "Enter customer name to delete: ";
        cin.ignore();
        getline(cin, name);
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (it->name == name) {
                for (auto &r : rooms) {
                    if (r.roomNo == it->roomNo) r.status = 'A';
                }
                customers.erase(it);
                cout << "Customer deleted successfully!\n";
                return;
            }
        }
        cout << "Customer not found!\n";
    }

    // ===== MAIN MENU =====
    void mainMenu() {
        int choice;
        do {
            clearScreen();
            cout << "=== HOTEL MANAGEMENT SYSTEM ===\n";
            cout << "1. Add Room\n";
            cout << "2. List Rooms\n";
            cout << "3. Modify Room\n";
            cout << "4. Delete Room\n";
            cout << "5. Add Customer\n";
            cout << "6. List Customers\n";
            cout << "7. Modify Customer\n";
            cout << "8. Delete Customer\n";
            cout << "9. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            clearScreen();
            switch (choice) {
                case 1: addRoom(); break;
                case 2: listRooms(); break;
                case 3: modifyRoom(); break;
                case 4: deleteRoom(); break;
                case 5: addCustomer(); break;
                case 6: listCustomers(); break;
                case 7: modifyCustomer(); break;
                case 8: deleteCustomer(); break;
                case 9: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
            if (choice != 9) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
        } while (choice != 9);
    }
};

int main() {
    HotelManagement hotel;
    hotel.mainMenu();
    return 0;
}