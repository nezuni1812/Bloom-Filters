/*Thiếu database
Cần tạo database để lưu account và sửa password trong database
Cần lấy dữ liệu từ database để check username trùng, check weak password
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <Windows.h>

using namespace std;

#include "Header.h"
#include "color.h"

// Time before switching to a new screen
int beforeSwitchScreen = 800;

// Reference: https://cp-algorithms.com/string/string-hashing.html#calculation-of-the-hash-of-a-string
// Hashing cho bit array: nhận một string -> return một hash
// Thay đổi số p để đưa ra các hash khác nhau
int polyNominalRollingHashing(string a, long n, long long p = 19, bool debug = false){
    unsigned long long hash = 0;
    for (int i = 0; i < a.size(); i++){
        long long toNum = a[i];
        hash += toNum * pow(p, i);
        hash %= n;
        if (debug)
            cout << a[i] << ":" << hash << "\n";
    }
    
    return hash % n;
}

// Kiểm tra xem có phần tử trùng trong filter Bloom không
bool checkHash(string a, int filter[],  int n){
    int pos1 = polyNominalRollingHashing(a, n, 19), pos2 = polyNominalRollingHashing(a, n, 23), pos3 = polyNominalRollingHashing(a, n, 7);
    
    return !(filter[pos1] == 0 || filter[pos2] == 0 || filter[pos3] == 0);
}

// Thêm một phần tử vào filter Bloom: đánh dấu thành bit 1 ở 3 vị trí trên bit array
void insertBloom(string a, int filter[], int n){
    int pos1 = polyNominalRollingHashing(a, n), pos2 = polyNominalRollingHashing(a, n, 23), pos3 = polyNominalRollingHashing(a, n, 7);
    
    filter[pos1] = 1;
    filter[pos2] = 1;
    filter[pos3] = 1;
}

// Lấy thông tin User từ file -> vector
void loadAllUser(string fileName, vector<Account> &names){
    ifstream in(fileName.c_str());
    
    Account acc;
    while (in >> acc.username){
        in >> acc.password;
        names.push_back(acc);
    }
    
    in.close();
}

// Lấy thông tin Weak password từ file -> vector
void loadAllWeakPassword(string fileName, vector<string> &pass){
    ifstream in(fileName.c_str());
    
    string temp;
    while (in >> temp){
        if (temp != "")
            pass.push_back(temp);
    }
    
    in.close();
}

// Khởi tạo bit array bằng vector chứa tất cả User
void initUserFilter(int filter[], int n, vector<Account> data){
    for (int i = 0; i < data.size(); i++)
        insertBloom(data[i].username, filter, n);
}

// Khởi tạo bit array bằng vector chứa tất cả Weak password
void initPassFilter(int filter[], int n, vector<string> data){
    for (int i = 0; i < data.size(); i++)
        insertBloom(data[i], filter, n);
}

// Viết thường
string toLower(string a){
    string temp = "";
    
    for (int i = 0; i < a.size(); i++)
        if ('A' <= a[i] && a[i] <= 'Z')
            temp += a[i] + ' ';
        else
            temp += a[i];
            
    return temp;
}

bool checkUsername(string user, int filter[], int n, vector<Account> accounts) {
    //Check độ dài
    if (user.length() <= 5 || user.length() >= 10) {
        cout << "Your username must be longer than 5 characters and shorter than 10 characters.\n";
        return false;
    }

    //Check xem có space '_' không
    for (int i = 0; i < user.length(); i++)
        if (user[i] == ' ') {
            cout << "Your username must not contain any spaces.\n";
            return false;
        }
        
    // Check username trùng
    if (checkHash(user, filter, n)){
        for (int i = 0; i < accounts.size(); i++)
            if (accounts[i].username == user){
                cout << "Your username is already registered.\n";
                return false;
            }
    }
    
    return true;
}

bool doContain(string whole, string inside){
    if (toLower(whole).find(toLower(inside)) != string::npos)
        return false;
        
    return true;
}

bool checkPassword (Account acc, int weakPassFilter[], int n, vector<string> weakPass) {
    //Check độ dài
    if (acc.password.length() <= 10 || acc.password.length() >= 20) {
        cout << "Your password must be longer than 10 characters and shorter than 20 characters.\n";
        return false;
    }

    if (acc.password == acc.username) {
        cout << "Your password can not be the same as your username.\n";
        return false;
    }

    //Gắn cờ cho uppercase, lowercase, số và ký tự đặc biệt/ khoảng trắng
    bool upper = false, lower = false, num = false, specialchar = false;
    for (int i = 0; i < acc.password.length(); i++) {
        if (acc.password[i] == ' ') {
            cout << "Your password must not contain any space.\n";
            return false;
        }
        else 
            if (acc.password[i] >= 'a' && acc.password[i] <= 'z')
                lower = true;
            else 
                if (acc.password[i] >= '0' && acc.password[i] <= '9')
                    num = true;
                else 
                    if (acc.password[i] >= 'A' && acc.password[i] <= 'Z') 
                        upper = true;
                    else     
                        specialchar = true;
    }

    if (!upper || !lower || !num || !specialchar) {
        cout << "Your password must contain uppercase, lowercase, numbers and special characters.\n";
        return false;
    }

    if (checkHash(acc.password, weakPassFilter, n)){
        for (int i = 0; i < weakPass.size(); i++){
            // cout << "Weak password suspected.\n";
            if (weakPass[i] == acc.password) {
                cout << "Your password is a weak one.\n";
                return false;
            }
        }
    }

    return true;
}

bool checkRegister(Account &acc, int userFilter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass) {
    if (checkUsername(acc.username, userFilter, n, accounts) && checkPassword(acc, weakPassFilter, nPass, weakPass)) {
        cout << "You have successfully registered!\n";
        acc.isLoggedIn = true;
        return true;
    }
    return false;
}

//Đẩy account đã đăng ký thành công vào file, gọi hàm này khi thao tác chức năng đăng ký
void Registration(Account &acc, int userFilter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass) {
    system("cls");
    
    cout << "Username: ";
    getline(cin, acc.username, '\n');
    cout << "Password: ";
    getline(cin, acc.password, '\n');

    ofstream ofs("Fail.txt", ios::app);
    while (!checkRegister(acc, userFilter, n, accounts, weakPassFilter, nPass, weakPass)) {
        ofs << acc.username << " " << acc.password << endl;

        cout << dye("#cf1717", "\nPlease re-enter your username and password!\n");
        cout << "Username: ";
        getline(cin, acc.username, '\n');
        cout << "Password: ";
        getline(cin, acc.password, '\n');
        
    }
    ofs.close();

    //Đẩy account vào file
    ofstream out("SignUp.txt", ios::app);
    out << acc.username << " " << acc.password << endl;
    
    out.close();
    
    cout << dye("#008022", "Ket thuc registration\n");
    
    Sleep(beforeSwitchScreen);
}

void MultipleRegistration(Account &acc, int filter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass){
    system("cls");
    
    cout << "Input the amount of registration: ";
    int amount;
    cin >> amount;
    cin.ignore();
    
    for (int i = 0; i < amount; i++)
        Registration(acc, filter, n,  accounts, weakPassFilter, nPass, weakPass);
        
    Sleep(beforeSwitchScreen);
}

void LogIn(Account &acc, int filter[], int n, vector<Account> allUsers){
    system("cls");
    
    cout << "Welcome to login screen.\n";
    cout << "Input your username: ";
    cin >> acc.username;
    cout << "Input your password: ";
    cin >> acc.password;
    
    if (!checkHash(acc.username, filter, n)){
        cout << dye("#cf1717", "Not on our database.\n");
        
        Sleep(beforeSwitchScreen);
        return;
    }
    
    for (int i = 0; i < allUsers.size(); i++)
        if (acc.username == allUsers[i].username && acc.password == allUsers[i].password){
            cout << dye("#008022", "Login successfully.\n");
            acc.password = allUsers[i].password;
            acc.isLoggedIn = true;
            
            Sleep(beforeSwitchScreen);
        }
}

void changePassword(Account &acc, int filter[], int n, int weakPassFilter[], int nPass, vector<string> weakPass){
    system("cls");
    
    if (!acc.isLoggedIn){
        cout << dye("#cf1717", "You haven't logged in yet.\n");
        Sleep(beforeSwitchScreen);
        return;
    }
    
    string password;
    cout << "Input your new password: ";
    password = acc.password;
    cin >> acc.password;
    
    while (!checkPassword(acc, weakPassFilter, nPass, weakPass)) {

        // cin.clear();
        // cin.ignore();
        cout << dye("#cf1717", "\nPlease re-enter your password!\n");
        cout << "Password: ";
        password = acc.password;
        // getline(cin, acc.password, '\n');
        cin >> acc.password;
    }
    
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
    
    file.close();
    
    cout << dye("#008022", "Password changed successfully.\n");
    
    Sleep(beforeSwitchScreen);
}
