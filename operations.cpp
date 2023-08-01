#include "color.h"
#include "bloomfilter.cpp"

using namespace std;

// Time before switching to a new screen
int beforeSwitchScreen = 800;

string errorColor = "#cf1717";
string successColor = "#008022";

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
    
    accounts.push_back(acc);
    for (int i = 0; i < accounts.size(); i++) {
        cout << accounts[i].username << endl;
    }
    insertBloom(acc.username, userFilter, n);
    
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
    
    accounts.push_back(acc);
    insertBloom(acc.username, userFilter, n);
}

//Gọi hàm này khi thao tác chức năng đa đăng ký
void MultipleRegistration(Account &acc, int filter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass){
    system("cls");
    
    vector<Account> newUsers;
    
    loadAllUser("SignUp.txt", newUsers);
    
    for (int i = 0; i < newUsers.size(); i++){
        cout << "Username: " << newUsers[i].username << "\nPassword: " << newUsers[i].password << "\n";
        
        AutoRegistration(newUsers[i], filter, n, accounts, weakPassFilter, nPass, weakPass);

        // Thêm khoảng cách giữa các tài khoản
        cout << "\n";
        
        Sleep(beforeSwitchScreen);
    }
    
    cout << dye(successColor, "Multiple Registration done!\n");
        
    Sleep(beforeSwitchScreen);
}

//Gọi hàm này khi thao tác chức năng đăng nhập
void LogIn(Account &acc, int filter[], int n, vector<Account> allUsers){
    system("cls");

    if (acc.isLoggedIn) {
        cout << dye(errorColor, "You have logged in alreadey!\n");
        return;
    }
    
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
    
    cout << "a" << endl;
    for (int i = 0; i < allUsers.size(); i++)
        if (acc.username == allUsers[i].username && acc.password == allUsers[i].password){
            cout << "b" << endl;
            cout << dye(successColor, "Login successfully.\n");
            acc.password = allUsers[i].password;
            acc.isLoggedIn = true;
            
            Sleep(beforeSwitchScreen);
        }
}

//Gọi hàm này khi thao tác chức năng thay đổi mật khẩu
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
            individualLine = acc.username + " " + acc.password;
        }
            
        if (individualLine != "\n");
            allContent += individualLine + "\n";
        
    }
    file.close();
    
    file.open("UserDatabase.txt", ios::out);
    file << allContent;
    file.close();
    
    cout << dye(successColor, "Password changed successfully.\n");

    Sleep(beforeSwitchScreen);
}
