#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

#include "operations.cpp"

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

int main(){
    
    // fstream file("inandout.txt", ios::out | ios::in);
    
    // string temp;
    // file >> temp;
    
    // file.seekg(ios::beg);
    
    // for (int i = 0; i < 3; i++)
    //     file << temp << " world, programmed to work but not to feel\n";
        
    // file.close();
    
    Account acc;
    acc.username = "Thingtodo@2Meomeomeo~1kahng2";
    acc.password = "Meomeomeo!1";
    
    string password = "Meomeomeo:3";
    string allContent = "";
    string individualLine = "";
    fstream file("SignUp.txt", ios::in);
    while (getline(file, individualLine)){
        // cout << individualLine << endl;
        if (individualLine.find(acc.username) != string::npos){
            cout << individualLine.find(password) << "\n";
            individualLine.replace(individualLine.find(password), password.size(), acc.password);
            cout << "Password found\n";
        }
            
        cout << ">>" << individualLine << "<<\n";
        
        if (individualLine != "\n")
            allContent += individualLine + "\n";
        
    }
    
    file.close();
    
    file.open("SignUp.txt", ios::out);
    
    file << allContent;
    cout << allContent << "\n";
    
    
    // ofstream out("test.txt");
    // out << allContent;
    // out.close();
    
    return 0;
}