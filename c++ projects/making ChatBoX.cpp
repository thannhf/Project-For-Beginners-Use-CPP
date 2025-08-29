#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main() {
    char inp;
    string name;
    int age;

    cout << "\t\tWELCOME TO CHATBOX\n";
    cout << "To continue the program type 'Y' and to end type 'N' - \n";
    cout << "--> ";
    cin >> inp;

    // Kiểm tra điều kiện Y/N
    if (inp == 'y' || inp == 'Y') {
        cout << "\nWelcome ...!\n";
    } else {
        cout << "\nThanks for coming.\n";
        return 0;
    }

    system("cls"); // Xoá màn hình

    cout << "\tHELLO USER!\n";
    cout << "What is your name? ";
    cin >> name;

    cout << "Hi " << name << "! What is your age? ";
    cin >> age;

    // Xử lý theo tuổi
    switch (age) {
        case 18:
            cout << "\nYou are young!\n";
            break;
        case 30:
            cout << "\nYou are a man!\n";
            break;
        default:
            cout << "\nNothing to say about your age.\n";
    }

    cout << "\nBye bye, " << name << "!\n";
    system("pause"); 
    system("cls");
    cout << "\t\t\t\tPROGRAM END HERE\n";

    return 0;
}