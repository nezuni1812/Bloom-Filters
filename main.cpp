#include "operations.cpp"

// Weak pass src: https://github.com/richiemann/vietnam-password-lists/blob/master/top1k-vn-passwords.txt

int main() {
    const int n = 500;
    int bloomFilter[n] = {0};
    
    vector<string> userNames;
    loadAllData("SignUp.txt", userNames);
    initBloomFilter(bloomFilter, n, userNames);
    
    int mode = 0;
    Account acc;
    while (mode != -1){
        cout << "Choose a mode\n"
        "1 for Register\n"
        "2 for Changing password\n";
        cin >> mode;
        
        if (mode == -1)
            break;
        
        switch (mode){
            case 1:
                Registration(acc, bloomFilter, n);
                break;
            case 2:
                changePassword(acc, bloomFilter, n);
                break;
                
        }
    }
    
}