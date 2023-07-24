#include "operations.cpp"

// Weak pass src: https://github.com/richiemann/vietnam-password-lists/blob/master/top1k-vn-passwords.txt

int main() {
    const int n = 500;
    int bloomFilter[n] = {0};
    
    vector<string> userNames;
    loadAllData("SignUp.txt", userNames);
    initBloomFilter(bloomFilter, n, userNames);
    
    Registration(bloomFilter, n);
}