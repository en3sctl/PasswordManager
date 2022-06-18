#include<iostream>
#include<string>
#include "Manager.h"
using namespace std;

/**
 * @brief The main driver code
 *
 * @return int
 */
int main() {
    cout << "----------------Welcome to Password Manager----------------" << "\n";
    cout << "Enter the secret key: ";
    string secretKey;
    getline(cin, secretKey);
    cout << "Enter the filename: ";
    string filename;
    cin >> filename;
    Manager pm(10, filename, secretKey);
    int choice;
    pm.readPasswords();
    pm.decryptPasswords();
    cout << "Last Attempt was at: " << pm.getLastAttempt() << "\n";
    while (true) {
        cout << "\nMenu:\n1. Search a password\n2.Sort Passwords\n3.Add a password\n4.Edit a password\n5.Remove a password\n6.Add a category\n7.Remove a category\n8.Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:pm.searchPassword(); break;
        case 2:pm.sortPasswords(); break;
        case 3:pm.addPassword(); break;
        case 4:pm.editPassword(); break;
        case 5:pm.removePassword(); break;
        case 6:pm.addCategory(); break;
        case 7:pm.removeCategory(); break;
        case 9:pm.showPasswords(); break;
        case 8:pm.writePasswords(); exit(0);
        default:cout << "Invalid Choice!\n"; break;
        }
    }
    pm.writePasswords();
    return 0;
}
