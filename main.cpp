#include "operations.cpp"

// Weak pass src: https://github.com/richiemann/vietnam-password-lists/blob/master/top1k-vn-passwords.txt

int main() {
    const int n = 500;
    int usernameFilter[n] = {0};
    int usernameFilter[n] = {0};
    
    vector<Account> accounts;
    loadAllData("SignUp.txt", accounts);
    initBloomFilter(usernameFilter, n, accounts);
    
    int mode = 0;
    Account acc;
    while (mode != -1){
        cout << "Choose a mode\n"
        "1 for Register\n"
        "2 for Changing password\n"
        "3 for Multiple Registration\n"
        "4 for Login\n";
        cin >> mode;
        cin.ignore();
        
        if (mode == -1)
            break;
        
        switch (mode){
            case 1:
                Registration(acc, usernameFilter, n);
                break;
            case 2:
                changePassword(acc, usernameFilter, n);
                break;
            case 4:
                LogIn(acc, usernameFilter, n, accounts);
                break;
            case 3:
                MultipleRegistration(acc, usernameFilter, n, accounts);
                break;
        }
    }
    
}