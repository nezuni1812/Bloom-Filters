#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;



int main(){
    /* 
    File:
    SignUp.txt
    Fail.txt
    Weak-Pass.txt 
    */
    
    // ifstream file("wordlist.txt", ios::in, ios::out);
    string word;
    
    int n = 500;
    int bloomFilter[500] = {0};
    
    while (word != "-1"){
        cout << "Input a word: ";
        cin >> word;
        
        if (!checkHash(word, bloomFilter, n)){
            cout << word << " def hasn't existed before\n";
            insertBloom(word, bloomFilter, n);
        }
        else
            cout << word << " probably existed\n";
    }
    
    return 0;
}