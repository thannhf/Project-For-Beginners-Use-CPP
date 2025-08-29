#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <limits>
using namespace std;

void menu();

class one {
public:
    virtual void get() = 0;
    virtual void show() = 0;
};

class info : public one {
public:
    char name[50], time[50];
    int num, age;
    void get() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter The Patient Name = ";
        cin.getline(name, 50);

        cout << "\nEnter the Appointment Time = ";
        cin.getline(time, 50);

        cout << "\nEnter Age = ";
        cin >> age;
        cout << "\nEnter Appointment No = ";
        cin >> num;
    }
    void show() {
        cout << "\nName = " << name;
        cout << "\nAge = " << age;
        cout << "\nNo = " << num;
        cout << "\nTime = " << time << "\n";
    }
};

class rana : public info {
public:
    info a1;
    void get() {
        system("cls");
        ofstream out("rana.txt", ios::app | ios::binary);
        a1.get();
        out.write((char*)&a1, sizeof(info));
        out.close();
        cout << "Your Entry Has been saved";
        getch();
        menu();
    }
    void show() {
        ifstream in("rana.txt", ios::binary);
        if (!in) {
            cout << "\n\nNo Data In the File.";
        } else {
            while (in.read((char*)&a1, sizeof(a1))) {
                a1.show();
            }
            in.close();
        }
        getch();
        menu();
    }
};

class attash : public info {
public:
    info a1;
    void get() {
        system("cls");
        ofstream out("attash.txt", ios::app | ios::binary);
        a1.get();
        out.write((char*)&a1, sizeof(info));
        out.close();
        cout << "Your Entry has been saved";
        getch();
        menu();
    }
    void show() {
        ifstream in("attash.txt", ios::binary);
        if (!in) {
            cout << "No Data In the file";
        } else {
            while (in.read((char*)&a1, sizeof(a1))) {
                a1.show();
            }
            in.close();
        }
        getch();
        menu();
    }
};

class bahadur : public info {
public:
    info a1;
    void get() {
        system("cls");
        ofstream out("bahadur.txt", ios::app | ios::binary);
        a1.get();
        out.write((char*)&a1, sizeof(info));
        out.close();
        cout << "your entry has been saved ";
        getch();
        menu();
    }
    void show() {
        ifstream in("bahadur.txt", ios::binary);
        if (!in) {
            cout << "No data in the file";
        } else {
            while (in.read((char*)&a1, sizeof(a1))) {
                a1.show();
            }
            in.close();
        }
        getch();
        menu();
    }
};

class staff : public one {
public:
    char all[999];
    char name[50], age[20], sal[30], pos[20];

    void get() {
        ofstream out("staff.txt", ios::app);
        {
            system("cls");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nEnter Name= ";
            cin.getline(name, 50);

            cout << "\nEnter Age= ";
            cin.getline(age, 20);

            cout << "\nEnter Salary= ";
            cin.getline(sal, 30);

            cout << "\nEnter working position= ";
            cin.getline(pos, 20);
        }
        out << "\nName = " << name << "\nAge = " << age << "\nSalary = " << sal << "\nWorking Position = " << pos << "\n";
        out.close();
        cout << "\n\nYour Information has been saved: \n\t\t\tPress any key to continue: ";
        getch();
        menu();
    }

    void show() {
        ifstream in("staff.txt");
        if (!in) {
            cout << "File open error";
        }
        while (in.getline(all, 999)) {
            cout << all << endl;
        }
        in.close();
        cout << "\n\n\t\t\tPress any key to continue: ";
        getch();
        menu();
    }
};

class information {
public:
    void drinfo() {
        system("cls");
        cout << "\n==============================================================================\n";
        cout << "\n\n\t\t(Three Doctor Available) \n\n \t\t[Information And Timing Are Given Below]\n";
        cout << "-----------------------------------------------------------------------------\n";
        cout << "\t\tDr Available:\n";
        cout << "\t\tDr. Rana (skin specialist)\n\n";
        cout << "\t\t\t [[Timing]]:\n\n";
        cout << "\tMonday To Friday\t\t9AM TO 5PM\n";
        cout << "\tSaturday         \t\t9AM TO 1PM\n";
        cout << "\tSunday          \t\t Off\n";
        cout << "\n------------------------------------------------------------------------------\n";
        cout << "\t\tDr. Bahadur (child specialist)\n\n";
        cout << "\t\t\t [[Timing]]:\n\n";
        cout << "\tMonday To Friday\t\t2PM TO 10PM\n";
        cout << "\tSaturday         \t\t8AM TO 1PM\n";
        cout << "\tSunday          \t\t12PM TO 9PM\n";
        cout << "\n------------------------------------------------------------------------------\n";
        cout << "\t\tDr. Attash (DVM)\n\n";
        cout << "\t\t\t [[Timing]]:\n\n";
        cout << "\tMonday To Friday\t\t8AM TO 5PM\n";
        cout << "\tSaturday         \t\t10AM TO 1PM\n";
        cout << "\tSunday          \t\t Off\n";
        cout << "\n------------------------------------------------------------------------------\n";
        cout << "\nPress Any Key To Continue: ";
        getch();
        menu();
    }
};

void call_dr() {
    system("cls");
    int choice;
    cout << "\n\n\n\t\tPress 1 for Dr Rana Ayaz \n\n\t\t Press 2 for Dr Attash \n\n\t\t Press 3 for Dr Bahadur ";
    cin >> choice;

    one* ptr;
    rana s3;
    attash s4;
    bahadur s5;
    if (choice == 1) {
        ptr = &s3; ptr->get();
    } else if (choice == 2) {
        ptr = &s4; ptr->get();
    } else if (choice == 3) {
        ptr = &s5; ptr->get();
    } else {
        cout << "Sorry invalid choice: ";
    }
}

void pinfoshow() {
    system("cls");
    int choice;
    cout << "\n\n\t1- Press 1 for Dr Rana Ayaz \n\n\t2- Press 2 for Dr Attash \n\n\t3- Press 3 for Dr Bahadur\n";
    cout << "Please Enter Your Choice: ";
    cin >> choice;
    one* ptr;
    rana s3;
    attash s4;
    bahadur s5;
    if (choice == 1) {
        ptr = &s3; ptr->show();
    } else if (choice == 2) {
        ptr = &s4; ptr->show();
    } else if (choice == 3) {
        ptr = &s5; ptr->show();
    } else {
        cout << "Sorry invalid choice: ";
        getch();
        menu();
    }
}

void menu() {
    system("cls");

    cout << "\n Hospital Management system";
    cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\n\n\n\n\n\n\n";
    cout << "\t\t    |   ++++++++++  MAIN MENU   +++++++++  |  \n";
    cout << "\t\t    |    [[[  Hospital Management system  ]]]  |\n";
    cout << "\t\t    |======================================|   \n";
    cout << "\n--------------------------------------------------------------------------------\n";

    cout << "\n\n\t1-\t\tPress 1 For Available Doctor Information\n\n";
    cout << "\t2-\t\tPress 2 for Doctor Appointment\n\n";
    cout << "\t3-\t\tPress 3 for Saving Staff information\n\n";
    cout << "\t4-\t\tPress 4 for Checking Patient Appointment Menu:\n\n";
    cout << "\t5-\t\tPress 5 for Checking Staff Information Menu:\n\n";

    cout << "\n================================================================================\n";
    cout << "\n\n\t\tPlease Enter Your Choice: ";

    information a1;
    one* ptr;
    staff a2;
    int a;
    cin >> a;
    if (a == 1) {
        a1.drinfo();
    } else if (a == 2) {
        call_dr();
    } else if (a == 3) {
        ptr = &a2; ptr->get();
    } else if (a == 4) {
        pinfoshow();
    } else if (a == 5) {
        ptr = &a2; ptr->show();
    } else {
        cout << "Sorry invalid choice: ";
    }
}

int main() {
    menu();
}