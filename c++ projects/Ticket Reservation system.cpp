#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>  
using namespace std;

class TourBus {
    int bid;
    char destination[200];
    char time[50];
    int max_seats;
    int booked;
    int fare;

public:
    TourBus() {
        bid = 0;
        max_seats = 50;
        booked = 0;
        fare = 0;
        strcpy(time, "9:10am");
        strcpy(destination, "");
    }

    void input() {
        cout << "Enter bus id: ";
        cin >> bid;
        cin.ignore();
        cout << "Enter bus destination: ";
        cin.getline(destination, 200);
        cout << "Enter time of bus: ";
        cin.getline(time, 50);
        cout << "Enter fare of the bus: ";
        cin >> fare;
        cin.ignore();
    }

    void display() {
        cout << bid << "\t" << destination << "\t" << time
             << "\t" << max_seats << "\t" << booked << "\t" << fare << "\n";
    }

    void show() {
        cout << "Bus Id: " << bid << endl;
        cout << "Destination: " << destination << endl;
        cout << "Time: " << time << endl;
        cout << "Seats remaining: " << max_seats - booked << endl;
    }

    int getid() const { return bid; }
    void book() { booked++; }
    const char* getDestination() const { return destination; }
    int getBooked() const { return booked; }
    int getMax() const { return max_seats; }
    int getFare() const { return fare; }
};

class Ticket {
    char name[50];
    TourBus bus;

public:
    void generate(const char cname[], const TourBus& tb) {
        strcpy(name, cname);
        bus = tb;
    }

    void display() {
        cout << "Customer Name: " << name << endl;
        cout << "Details of Bus:" << endl;
        bus.show();
    }
};

int main() {
    int ch;
    fstream F, G;
    TourBus b;
    Ticket t;

    do {
        cout << "\n--- TOUR BUS MENU ---\n";
        cout << "1 - Add a new Tour Bus\n";
        cout << "2 - Show selected Bus\n";
        cout << "3 - Display All Buses\n";
        cout << "4 - Delete a Bus\n";
        cout << "5 - Book a ticket\n";
        cout << "6 - Display booked tickets\n";
        cout << "7 - Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        cin.ignore();

        if (ch == 1) {
            F.open("tour.dat", ios::app | ios::binary);
            b.input();
            F.write(reinterpret_cast<char*>(&b), sizeof(b));
            F.close();
            cout << "Bus added successfully.\n";
        } 
        else if (ch == 2) {
            int id, chk = 0;
            cout << "Enter bus id to display: ";
            cin >> id;
            F.open("tour.dat", ios::in | ios::binary);
            while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                if (b.getid() == id) {
                    b.show();
                    chk = 1;
                    break;
                }
            }
            if (!chk) cout << "Bus not found.\n";
            F.close();
        }
        else if (ch == 3) {
            F.open("tour.dat", ios::in | ios::binary);
            while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                b.display();
            }
            F.close();
        }
        else if (ch == 4) {
            int id, chk = 0;
            cout << "Enter bus id to delete: ";
            cin >> id;
            F.open("tour.dat", ios::in | ios::binary);
            G.open("temp.dat", ios::out | ios::binary);
            while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                if (b.getid() != id) {
                    G.write(reinterpret_cast<char*>(&b), sizeof(b));
                } else {
                    chk = 1;
                }
            }
            F.close();
            G.close();
            remove("tour.dat");
            rename("temp.dat", "tour.dat");
            if (chk) cout << "Bus deleted.\n"; else cout << "Bus not found.\n";
        }
        else if (ch == 5) {
            char dest[70], cname[50];
            int chk = 0;
            cout << "Enter destination: ";
            cin.getline(dest, 70);
            F.open("tour.dat", ios::in | ios::out | ios::binary);
            while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                if (strcmp(b.getDestination(), dest) == 0) {
                    b.show();
                    cout << "Enter customer name: ";
                    cin.getline(cname, 50);
                    b.book();
                    t.generate(cname, b);

                    G.open("tickets.dat", ios::app | ios::binary);
                    G.write(reinterpret_cast<char*>(&t), sizeof(t));
                    G.close();

                    streampos pos = F.tellg();
                    F.seekp(pos - static_cast<streamoff>(sizeof(b)));
                    F.write(reinterpret_cast<char*>(&b), sizeof(b));

                    cout << "Ticket booked!\n";
                    chk = 1;
                    break;
                }
            }
            if (!chk) cout << "No bus found.\n";
            F.close();
        }
        else if (ch == 6) {
            cout << "Booked Tickets:\n";
            G.open("tickets.dat", ios::in | ios::binary);
            while (G.read(reinterpret_cast<char*>(&t), sizeof(t))) {
                t.display();
            }
            G.close();
        }
    } while (ch != 7);

    return 0;
}