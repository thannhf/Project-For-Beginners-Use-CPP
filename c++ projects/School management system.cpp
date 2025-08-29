#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

struct Student {
    string fname, lname, Registration, classes;
} studentData;

struct Teacher {
    string fst_name, lst_name, qualification, exp, pay, subj, lec, addrs, cel_no, blod_grp, serves;
} tech[50];

void addStudent() {
    ofstream f1("student.txt", ios::app);
    char cont = 'y';
    while (cont == 'y' || cont == 'Y') {
        cout << "Enter first name: ";
        cin >> studentData.fname;
        cout << "Enter last name: ";
        cin >> studentData.lname;
        cout << "Enter Registration number: ";
        cin >> studentData.Registration;
        cout << "Enter Class: ";
        cin >> studentData.classes;

        f1 << studentData.fname << endl
           << studentData.lname << endl
           << studentData.Registration << endl
           << studentData.classes << endl;

        cout << "Do you want to enter another student? (y/n): ";
        cin >> cont;
    }
    f1.close();
}

void findStudent() {
    ifstream f2("student.txt");
    string find;
    cout << "Enter first name to search: ";
    cin >> find;

    bool found = false;
    while (getline(f2, studentData.fname)) {
        getline(f2, studentData.lname);
        getline(f2, studentData.Registration);
        getline(f2, studentData.classes);

        if (studentData.fname == find) {
            cout << "\nFirst Name: " << studentData.fname
                 << "\nLast Name: " << studentData.lname
                 << "\nRegistration: " << studentData.Registration
                 << "\nClass: " << studentData.classes << "\n\n";
            found = true;
        }
    }
    if (!found) cout << "No record found.\n";
    f2.close();
    cout << "Press any key to continue...";
    getch();
}

void addTeacher() {
    ofstream t1("teacher.txt", ios::app);
    char cont = 'y';
    int i = 0;
    while ((cont == 'y' || cont == 'Y') && i < 50) {
        cout << "Enter First Name: ";
        cin >> tech[i].fst_name;
        cout << "Enter Last Name: ";
        cin >> tech[i].lst_name;
        cout << "Enter Qualification: ";
        cin >> tech[i].qualification;
        cout << "Enter Experience(years): ";
        cin >> tech[i].exp;
        cout << "Enter Years in this school: ";
        cin >> tech[i].serves;
        cout << "Enter Subject: ";
        cin >> tech[i].subj;
        cout << "Enter Lectures per week: ";
        cin >> tech[i].lec;
        cout << "Enter Pay: ";
        cin >> tech[i].pay;
        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, tech[i].addrs);
        cout << "Enter Phone Number: ";
        cin >> tech[i].cel_no;
        cout << "Enter Blood Group: ";
        cin >> tech[i].blod_grp;

        t1 << tech[i].fst_name << endl
           << tech[i].lst_name << endl
           << tech[i].qualification << endl
           << tech[i].exp << endl
           << tech[i].serves << endl
           << tech[i].subj << endl
           << tech[i].lec << endl
           << tech[i].pay << endl
           << tech[i].addrs << endl
           << tech[i].cel_no << endl
           << tech[i].blod_grp << endl;

        cout << "Do you want to enter another teacher? (y/n): ";
        cin >> cont;
        i++;
    }
    t1.close();
}

void findTeacher() {
    ifstream t2("teacher.txt");
    string find;
    cout << "Enter teacher's first name to search: ";
    cin >> find;

    bool found = false;
    Teacher t;
    while (getline(t2, t.fst_name)) {
        getline(t2, t.lst_name);
        getline(t2, t.qualification);
        getline(t2, t.exp);
        getline(t2, t.serves);
        getline(t2, t.subj);
        getline(t2, t.lec);
        getline(t2, t.pay);
        getline(t2, t.addrs);
        getline(t2, t.cel_no);
        getline(t2, t.blod_grp);

        if (t.fst_name == find) {
            cout << "\nFirst Name: " << t.fst_name
                 << "\nLast Name: " << t.lst_name
                 << "\nQualification: " << t.qualification
                 << "\nExperience: " << t.exp
                 << "\nYears in School: " << t.serves
                 << "\nSubject: " << t.subj
                 << "\nLectures/Week: " << t.lec
                 << "\nPay: " << t.pay
                 << "\nAddress: " << t.addrs
                 << "\nPhone: " << t.cel_no
                 << "\nBlood Group: " << t.blod_grp << "\n\n";
            found = true;
        }
    }
    if (!found) cout << "No record found.\n";
    t2.close();
    cout << "Press any key to continue...";
    getch();
}

int main() {
    char choice;
    while (true) {
        system("cls");
        cout << "\n\n\t\tSCHOOL MANAGEMENT PROGRAM\n\n";
        cout << "1. Students Information\n";
        cout << "2. Teachers Information\n";
        cout << "3. Exit Program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        system("cls");
        if (choice == '1') {
            cout << "1. Add Student\n2. Find Student\n3. Back\n";
            cin >> choice;
            if (choice == '1') addStudent();
            else if (choice == '2') findStudent();
        } else if (choice == '2') {
            cout << "1. Add Teacher\n2. Find Teacher\n3. Back\n";
            cin >> choice;
            if (choice == '1') addTeacher();
            else if (choice == '2') findTeacher();
        } else if (choice == '3') {
            break;
        }
    }
    return 0;
}