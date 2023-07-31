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

    int mode = -1;
    Account acc;
    system("cls");
    while (mode != 0) {
        
        cout << "Choose a mode:\n"
                "1 for Register\n"
                "2 for Multiple Registration\n"
                "3 for Login\n"
                "4 for Changing password\n"
                "0 for Exit Program\n";
        cin >> mode;
        cin.ignore();

        switch (mode) {
            case 1:
                Registration(acc, usernameFilter, n, accounts, weakPassFilter, n, weakPass);
                break;
            case 2:
                MultipleRegistration(acc, usernameFilter, n, accounts, weakPassFilter, n, weakPass);
                break;
            case 3:
                LogIn(acc, usernameFilter, n, accounts);
                break;
            case 4:
                changePassword(acc, usernameFilter, n, weakPassFilter, n, weakPass);
                break;
            case 0:
                cout << "You have exited the program!\n";
                break;
            default: 
                system("cls");      
                cout << "Invalid Choice! Please choose a number from 0 to 5 only.\n";
                break;
        }
    }
}