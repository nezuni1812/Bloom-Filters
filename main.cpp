#include <Windows.h>

// #include "Header.h"
#include "operations.cpp"

// Weak pass src:
// https://github.com/richiemann/vietnam-password-lists/blob/master/top1k-vn-passwords.txt

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    const int n = 500;
    // Bộ lọc tên User
    int usernameFilter[n] = {0};

    // Bộ lọc Mật khẩu yếu
    int weakPassFilter[n] = {0};

    // Vector Account
    vector<Account> accounts;

    // Vector Mật khẩu yếu
    vector<string> weakPass;

    loadAllUser("SignUp.txt", accounts);
    initUserFilter(usernameFilter, n, accounts);
    loadAllWeakPassword("Weak-Pass.txt", weakPass);
    initPassFilter(weakPassFilter, n, weakPass);

    int mode = 0;
    Account acc;
    while (mode != -1) {
        system("cls");
        
        cout << "Choose a mode\n"
                "1 for Register\n"
                "2 for Changing password\n"
                "3 for Multiple Registration\n"
                "4 for Login\n";
        cin >> mode;
        cin.ignore();

        if (mode == -1)
            break;

        switch (mode) {
            case 1:
                Registration(acc, usernameFilter, n, accounts, weakPassFilter, n, weakPass);
                break;
            case 2:
                changePassword(acc, usernameFilter, n, weakPassFilter, n, weakPass);
                break;
            case 4:
                LogIn(acc, usernameFilter, n, accounts);
                break;
            case 3:
                // acc, usernameFilter, n,  accounts, weakPassFilter, n, weakPass
                MultipleRegistration(acc, usernameFilter, n, accounts, weakPassFilter, n, weakPass);
                break;
        }
    }
}