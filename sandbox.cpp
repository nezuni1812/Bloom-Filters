#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

// #include "operations.cpp"

using namespace std;

void fileInAndOut(){
    fstream file("test.txt", ios::in | ios::out);
    
    string allContent;
    
    string line;
    while (getline(file, line)){
        if (line.find("dangkhoa") != string::npos)
            line.replace(line.find("123"), 3, "696");
        
        if (line != "")
            allContent += line + '\n';
        
    }
    
    
    file << allContent;
    file.close();
}

int polyNominalRollingHashing(string a, long n, long long p = 53, bool debug = false){
    long long hash = 0;
    long long power = 1;
    for (int i = 0; i < a.size(); i++){
        long long toNum = a[i];
        
        hash = (hash + toNum * power)%n;
        power = (power * p)%n;
        // hash %= n;
        if (debug)
            cout << a[i] << ":" << pow(p, i) << "\n";
    }
    
    
    // cout << "Hash with p = " << p << ": " << hash % n << "\n";
    return hash % n;
}

bool checkHash(string a, int filter[],  int n){
    int pos1 = polyNominalRollingHashing(a, n, 53, false), pos2 = polyNominalRollingHashing(a, n, 11, false), pos3 = polyNominalRollingHashing(a, n, 7, false);
    
    return !(filter[pos1] == 0 || filter[pos2] == 0 || filter[pos3] == 0);
}

void insertBloom(string a, int filter[], int n){
    int pos1 = polyNominalRollingHashing(a, n), pos2 = polyNominalRollingHashing(a, n, 11), pos3 = polyNominalRollingHashing(a, n, 7);
    
    filter[pos1] = 1;
    filter[pos2] = 1;
    filter[pos3] = 1;
}

int h2(string s)
{
    long long hash = 1;
    long long power = 19;
    for (int i = 0; i < s.size(); i++){
        hash = (hash + power * s[i]) % 500;
        cout << s[i] << ":" << hash << "\n";
        power = power * 19 % 500;
    }
     return hash % 500;
}

void testBloom(){
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
    
}


int main(){
    
    testBloom();
    
    // string word  = "";
    // while (word != "-1"){
    //     cout << "Input a word: ";
    //     cin >> word;
        
    //     // for (int i = 0; i < word.size(); i++)
    //         cout << h2(word) << endl;
    // }
    
    // fstream file("inandout.txt", ios::out | ios::in);
    
    // string temp;
    // file >> temp;
    
    // file.seekg(ios::beg);
    
    // for (int i = 0; i < 3; i++)
    //     file << temp << " world, programmed to work but not to feel\n";
        
    // file.close();
    
    // Account acc;
    // acc.username = "Thingtodo@2Meomeomeo~1kahng2";
    // acc.password = "Meomeomeo!1";
    
    // string password = "Meomeomeo:3";
    // string allContent = "";
    // string individualLine = "";
    // fstream file("SignUp.txt", ios::in);
    // while (getline(file, individualLine)){
    //     // cout << individualLine << endl;
    //     if (individualLine.find(acc.username) != string::npos){
    //         cout << individualLine.find(password) << "\n";
    //         individualLine.replace(individualLine.find(password), password.size(), acc.password);
    //         cout << "Password found\n";
    //     }
            
    //     cout << ">>" << individualLine << "<<\n";
        
    //     if (individualLine != "\n")
    //         allContent += individualLine + "\n";
        
    // }
    
    // file.close();
    
    // file.open("SignUp.txt", ios::out);
    
    // file << allContent;
    // cout << allContent << "\n";
    
    
    // ofstream out("test.txt");
    // out << allContent;
    // out.close();
    
    return 0;
}