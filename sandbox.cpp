#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

// #include "operations.cpp"

using namespace std;

int h1(string a, int n = 10007){
    // https://theartincode.stanis.me/008-djb2/
    long long hash = 5381;

    for (int i = 0; i < a.size(); i++){
        hash = (((hash << 5) + hash) + a[i]) % n; /* Equivalent to: (hash * 33 + a[i]) % n but it faster*/
        cout << a[i] << ":" << hash << endl;
    }

    return hash;
}

int hold(string a, int n){
    long long hash = 1;
    int p = 311;
    long long power = 19;
    for (int i = 0; i < a.size(); i++){
        hash = (hash + power * a[i]) % n;
        cout << a[i] << ":" << hash << "\n";
        power = power * 19 % n;
    }
    
    return hash % n;
}

int h2(string a, int n = 10007){
    // https://viblo.asia/p/giai-thuat-so-khop-chuoi-rolling-hash-Ljy5V3kMKra#_2-so-sanh-hai-chuoi-ki-tu-bang-ma-hash-3
    long long hash = 0;
    int base = 311;

    for (int i = 0; i < a.size(); ++i)
        hash = (hash * base + (int)a[i]) % n;

    return hash;
}

int h3(string a, int n = 10007){
    // http://www.cse.yorku.ca/~oz/hash.html
    long long hash = 0;

    for (int i = 0; i < a.size(); i++)
        hash = (a[i] + (hash << 6) + (hash << 16) - hash) % n; /*  Actual hash function: hash(i) = hash(i - 1) * 65599 + str[i]; */

    return hash % n;
}

int h4(string a, int n = 10007){
    long long hash = 53;
    
    for (int i = 0; i < a.size(); i++){
        hash = (hash * 37 + a[i]) % n;
    }
    
    return hash % n;
}

int h5(string a, int n = 10007){
    long long hash = 71;
    int p = 1;
    int base = 59;
    
    for (int i = 0; i < a.size(); i++){
        hash = (hash + (a[i]*base)) % n;
        base *= p;
    }
    
    return hash % n;
}



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

int polyNominalRollingHashing(string a, long n, long long p = 311, bool debug = true){
    long long hash = 0;
    long long power = 1;
    for (int i = 0; i < a.size(); i++){
        long long toNum = a[i];
        
        hash = (hash + toNum * power)%n;
        power = (power * p)%n;
        // hash %= n;
        if (debug)
            cout << a[i] << ":" << power << "\n";
    }
    
    
    // cout << "Hash with p = " << p << ": " << hash % n << "\n";
    return hash % n;
}

bool checkHash(string a, int filter[],  int n){
    int pos1 = polyNominalRollingHashing(a, n, 53, false), pos2 = polyNominalRollingHashing(a, n, 31, false), pos3 = polyNominalRollingHashing(a, n, 23, false);
    
    return !(filter[pos1] == 0 || filter[pos2] == 0 || filter[pos3] == 0);
}

void insertBloom(string a, int filter[], int n){
    int pos1 = polyNominalRollingHashing(a, n, 53), pos2 = polyNominalRollingHashing(a, n, 31), pos3 = polyNominalRollingHashing(a, n, 23);
    
    filter[pos1] = 1;
    filter[pos2] = 1;
    filter[pos3] = 1;
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
    
    // testBloom();
    
    string word  = "";
    while (word != "-1"){
        cout << "Input a word: ";
        cin >> word;
        
        // for (int i = 0; i < word.size(); i++)
            cout << polyNominalRollingHashing(word, 10007) << endl;
    }
    
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