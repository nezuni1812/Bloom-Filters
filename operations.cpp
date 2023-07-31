#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <Windows.h>

using namespace std;

#include "header.h"
#include "color.h"

// Time before switching to a new screen
int beforeSwitchScreen = 800;

string errorColor = "#cf1717";
string successColor = "#008022";

// Reference: https://cp-algorithms.com/string/string-hashing.html#calculation-of-the-hash-of-a-string
// Hashing cho bit array: nhận một string -> return một hash
// Thay đổi số p để đưa ra các hash khác nhau
int polyNominalRollingHashing(string a, long n, long long p){
    long long hash = 0;
    long long power = 1;
    for (int i = 0; i < a.size(); i++){
        long long toNum = a[i];
        
        hash = (hash + toNum * power) % n;
        power = (power * p) % n;
    }
    return hash % n;
}

int h1(string a, int n = 10007){
    // https://theartincode.stanis.me/008-djb2/
    long long hash = 5381;

    for (int i = 0; i < a.size(); i++){
        hash = (((hash << 5) + hash) + a[i]) % n; /* Equivalent to: (hash * 33 + a[i]) % n but it faster*/
        // cout << a[i] << ":" << hash << endl;
    }

    return hash;
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

// Kiểm tra xem có phần tử trùng trong filter Bloom không
bool checkHash(string a, int filter[],  int n){
    int pos1 = h1(a, n);
    int pos2 = h2(a, n);
    int pos3 = h3(a, n);
    int pos4 = h4(a, n);
    int pos5 = h5(a, n);
    
    return !(filter[pos1] == 0 || filter[pos2] == 0 || filter[pos3] == 0/*  || filter[pos4] == 0 || filter[pos5] == 0 */);
    
    // int pos1 = polyNominalRollingHashing(a, n, 53), pos2 = polyNominalRollingHashing(a, n, 31), pos3 = polyNominalRollingHashing(a, n, 23);
    
    // return !(filter[pos1] == 0 || filter[pos2] == 0 || filter[pos3] == 0);
}

// Thêm một phần tử vào filter Bloom: đánh dấu thành bit 1 ở 5 vị trí trên bit array
void insertBloom(string a, int filter[], int n){
    int pos1 = h1(a, n);
    int pos2 = h2(a, n);
    int pos3 = h3(a, n);
    int pos4 = h4(a, n);
    int pos5 = h5(a, n);
    
    filter[pos1] = 1;
    filter[pos2] = 1;
    filter[pos3] = 1;
    filter[pos4] = 1;
    filter[pos5] = 1;
    
    // int pos1 = polyNominalRollingHashing(a, n, 53), pos2 = polyNominalRollingHashing(a, n, 31), pos3 = polyNominalRollingHashing(a, n, 23);
    
    // filter[pos1] = 1;
    // filter[pos2] = 1;
    // filter[pos3] = 1;
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

bool checkUsername(string user, int filter[], int n, vector<Account> accounts) {
    //Check độ dài
    if (user.length() <= 5 || user.length() >= 10) {
        cout << dye(errorColor, "Your username must be longer than 5 characters and shorter than 10 characters.\n");
        return false;
    }

    //Check xem có space '_' không
    for (int i = 0; i < user.length(); i++)
        if (user[i] == ' ') {
            cout << dye(errorColor, "Your username must not contain any spaces.\n");
            return false;
        }
        
    // Check username trùng
    if (checkHash(user, filter, n)){
        for (int i = 0; i < accounts.size(); i++)
            if (accounts[i].username == user){
                cout << dye(errorColor, "Your username is already registered.\n");
                return false;
            }
    }
    
    return true;
}

bool checkPassword (Account acc, int weakPassFilter[], int n, vector<string> weakPass) {
    //Check độ dài
    if (acc.password.length() <= 10 || acc.password.length() >= 20) {
        cout << dye(errorColor, "Your password must be longer than 10 characters and shorter than 20 characters.\n");
        return false;
    }

    if (acc.password == acc.username) {
        cout << dye(errorColor, "Your password can not be the same as your username.\n");
        return false;
    }

    //Gắn cờ cho uppercase, lowercase, số và ký tự đặc biệt/ khoảng trắng
    bool upper = false, lower = false, num = false, specialchar = false;
    for (int i = 0; i < acc.password.length(); i++) {
        if (acc.password[i] == ' ') {
            cout << "Your Password must not contain any space.\n";
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
        cout << dye(errorColor, "Your password must contain uppercase, lowercase, numbers and special characters.\n");
        return false;
    }

    if (checkHash(acc.password, weakPassFilter, n)){
        for (int i = 0; i < weakPass.size(); i++){
            // cout << "Weak password suspected.\n";
            if (weakPass[i] == acc.password) {
                cout << dye(errorColor, "Your password is a weak one.\n");
                return false;
            }
        }
    }

    return true;
}

bool checkRegister(Account &acc, int userFilter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass) {
    if (checkUsername(acc.username, userFilter, n, accounts) && checkPassword(acc, weakPassFilter, nPass, weakPass)) {
        acc.isLoggedIn = true;
        return true;
    }
    return false;
}

//Đẩy account đã đăng ký thành công vào file, gọi hàm này khi thao tác chức năng đăng ký
void Registration(Account &acc, int userFilter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass) {
    system("cls");
    cout << "Welcome to Registration screen!\n";
    cout << "Username: ";
    getline(cin, acc.username, '\n');
    cout << "Password: ";
    getline(cin, acc.password, '\n');

    while (!checkRegister(acc, userFilter, n, accounts, weakPassFilter, nPass, weakPass)) {
        cout << dye(errorColor, "\nPlease re-enter your username and password!\n");
        cout << "Username: ";
        getline(cin, acc.username, '\n');
        cout << "Password: ";
        getline(cin, acc.password, '\n');
        
    }

    //Đẩy account vào file
    ofstream out("UserDatabase.txt", ios::app);
    out << acc.username << " " << acc.password << endl;
    
    out.close();
    
    loadAllUser("UserDatabase.txt", accounts);
    initUserFilter(userFilter, n, accounts);
    
    cout << dye(successColor, "You have successfully registered!\n");
    
    Sleep(beforeSwitchScreen);
}

void AutoRegistration(Account &acc, int userFilter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass) {

    ofstream ofs("Fail.txt", ios::app);
    bool isFailed = !checkRegister(acc, userFilter, n, accounts, weakPassFilter, nPass, weakPass);
    if (isFailed) {
        ofs << acc.username << " " << acc.password << endl;
    }
    ofs.close();
    
    if (isFailed)
        return;

    //Đẩy account vào file
    ofstream out("UserDatabase.txt", ios::app);
    out << acc.username << " " << acc.password << endl;
    
    out.close();
    
    loadAllUser("UserDatabase.txt", accounts);
    initUserFilter(userFilter, n, accounts);
}

void MultipleRegistration(Account &acc, int filter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass){
    system("cls");
    
    vector<Account> newUsers;
    
    loadAllUser("SignUp.txt", newUsers);
    
    for (int i = 0; i < newUsers.size(); i++){
        cout << "Username: " << newUsers[i].username << "\nPassword: " << newUsers[i].password << "\n";
        
        AutoRegistration(newUsers[i], filter, n, accounts, weakPassFilter, nPass, weakPass);
        loadAllUser("UserDatabase.txt", accounts);
        initUserFilter(filter, n, accounts);
        
        Sleep(beforeSwitchScreen);
    }
    
    cout << dye(successColor, "Multiple Registration done!\n");
        
    Sleep(beforeSwitchScreen);
}

void LogIn(Account &acc, int filter[], int n, vector<Account> allUsers){
    system("cls");
    
    cout << "Welcome to Login screen!\n";
    cout << "Username: ";
    cin >> acc.username;
    cout << "Password: ";
    cin >> acc.password;
    
    if (!checkHash(acc.username, filter, n)){
        cout << dye(errorColor, "This Username isn't on our database.\n");
        
        Sleep(beforeSwitchScreen);
        return;
    }
    
    for (int i = 0; i < allUsers.size(); i++)
        if (acc.username == allUsers[i].username && acc.password == allUsers[i].password){
            cout << dye(successColor, "Login successfully.\n");
            acc.password = allUsers[i].password;
            acc.isLoggedIn = true;
            
            Sleep(beforeSwitchScreen);
        }
}

void changePassword(Account &acc, int filter[], int n, int weakPassFilter[], int nPass, vector<string> weakPass){
    system("cls");
    
    if (!acc.isLoggedIn){
        cout << dye(errorColor, "You haven't logged in yet.\n");
        Sleep(beforeSwitchScreen);
        return;
    }
    
    string password;
    cout << "Input your new Password: ";
    password = acc.password;
    cin >> acc.password;
    
    while (!checkPassword(acc, weakPassFilter, nPass, weakPass)) {
        cout << dye(errorColor, "\nPlease re-enter your password!\n");
        cout << "Input your new Password: ";
        password = acc.password;
        cin >> acc.password;
    }
    
    string allContent = "";
    string individualLine = "";
    fstream file("UserDatabase.txt", ios::in);
    while (getline(file, individualLine)){
        if (individualLine.find(acc.username) != string::npos){
            individualLine = acc.username + " " + acc.password + "\n";
        }
            
        if (individualLine != "\n");
            allContent += individualLine + "\n";
        
    }
    file.close();
    
    file.open("UserDatabase.txt", ios::out);
    
    file << allContent;
    // cout << allContent << "\n";
    
    file.close();
    
    cout << dye(successColor, "Password changed successfully.\n");

    Sleep(beforeSwitchScreen);
}
