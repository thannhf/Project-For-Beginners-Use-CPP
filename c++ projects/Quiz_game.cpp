#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// hàm chuyển chuỗi về lowercase để so sánh không phân biệt hoa/thường
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    string questions[10] = {
        "Which of the following is tricontinental country?",
        "Famous fast food restaurant company Burger king belongs to which country?",
        "Office of strategic service (OSS) was old name of which intelligence agency?",
        "The first person to draw the map of earth?",
        "Who laid first step on the moon?",
        "What is the name of chinese parliament?",
        "Ogaden desert is present in_________?",
        "Capital of America is____________?",
        "Wadi rum which resemblance to the surface of Mars is located in_____________?",
        "Borneo island is in which ocean?"
    };

    string options[10][4] = {
        {"chad","chile","mali","swaziland"},
        {"america","england","turkey","none of these"},
        {"mi6","cia","isi","N.O.T"},
        {"heraclitus","phythagoras","anaximander","thales"},
        {"lmp edgar","cmp stuart","neil armstrong","none of them"},
        {"national assembly","national people's congress","federal parliament","none"},
        {"europe","asia","africa","america"},
        {"washington dc","alaska","hawaii","california"},
        {"argentina","israel","jordan","egypt"},
        {"indian ocean","pacific ocean","arctic ocean","atlantic"},
    };

    string correctOptions[10] = {
        "chile","america","cia","anaximander",
        "neil armstrong","national people's congress","africa",
        "washington dc","jordan","pacific ocean"
    };

    int userOptions[10] = {0};
    int totalQs = 10;

    // Conduct quiz
    for(int i = 0; i < totalQs; i++) {
        cout << "Question # " << (i + 1) << endl;
        cout << questions[i] << endl;
        cout << "1. " << options[i][0] << endl;
        cout << "2. " << options[i][1] << endl;
        cout << "3. " << options[i][2] << endl;
        cout << "4. " << options[i][3] << endl << endl;

        cout << "Select option (1-4) or 0 to skip and press enter: ";
        cin >> userOptions[i];
        cout << endl << "--------------------------------" << endl << endl;
    }

    // Show correct answers
    cout << "==================================" << endl;
    cout << "========= Correct Options =========" << endl;
    cout << "==================================" << endl;

    for(int i = 0; i < totalQs; i++) {
        cout << "Question #" << (i+1) << endl;
        cout << questions[i] << endl;

        cout << "Your answer: ";
        if(userOptions[i] == 0) {
            cout << "Skipped";
        } else {
            cout << options[i][userOptions[i]-1];
        }
        cout << endl;

        cout << "Correct answer: " << correctOptions[i] << endl;
        cout << "-------------------" << endl;
    }

    // Result
    int correct = 0, incorrect = 0, skipped = 0;
    for(int i = 0; i < totalQs; i++) {
        if(userOptions[i] != 0) {
            if(toLower(correctOptions[i]) == toLower(options[i][userOptions[i]-1])) {
                correct++;
            } else {
                incorrect++;
            }
        } else {
            skipped++;
        }
    }

    cout << endl;
    cout << "=========== Result ============" << endl;
    cout << "Total Questions: " << totalQs << endl;
    cout << "Correct:   " << correct << endl;
    cout << "Incorrect: " << incorrect << endl;
    cout << "Skipped:   " << skipped << endl;

    return 0;
}
