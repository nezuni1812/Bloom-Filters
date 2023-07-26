/*Thiếu database
Cần tạo database để lưu account và sửa password trong database
Cần lấy dữ liệu từ database để check username trùng, check weak password
*/

#include "header.h"

// Reference: https://cp-algorithms.com/string/string-hashing.html#calculation-of-the-hash-of-a-string
int polyNominalRollingHashing(string a, long n, long long p = 19, bool debug = false){
    unsigned long long hash = 0;
    for (int i = 0; i < a.size(); i++){
        long long toNum = a[i];
        hash += toNum * pow(p, i);
        hash %= n;
        if (debug)
            cout << a << ":" << hash << "\n";
    }
    
    return hash % n;
}

bool checkHash(string a, int filter[],  int n){
    int pos1 = polyNominalRollingHashing(a, n, 19), pos2 = polyNominalRollingHashing(a, n, 23), pos3 = polyNominalRollingHashing(a, n, 7);
    
    return !(filter[pos1] == 0 || filter[pos2] == 0 || filter[pos3] == 0);
}

void insertBloom(string a, int filter[], int n){
    int pos1 = polyNominalRollingHashing(a, n), pos2 = polyNominalRollingHashing(a, n, 23), pos3 = polyNominalRollingHashing(a, n, 7);
    
    filter[pos1] = 1;
    filter[pos2] = 1;
    filter[pos3] = 1;
}

void loadAllData(string fileName, vector<Account> &names){
    ifstream in(fileName.c_str());
    
    Account acc;
    while (in >> acc.username){
        in >> acc.password;
        names.push_back(acc);
    }
    
    in.close();
}

void initBloomFilter(int filter[], int n, vector<Account> data){
    for (int i = 0; i < data.size(); i++)
        insertBloom(data[i].username, filter, n);
}

string toLower(string a){
    string temp = "";
    
    for (int i = 0; i < a.size(); i++)
        if ('A' <= a[i] && a[i] <= 'Z')
            temp += a[i] + ' ';
        else
            temp += a[i];
            
    return temp;
}

bool checkUsername(string user, int filter[], int n) {
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
        cout << "Your username is already registered.\n";
        return false;
    }
    
    return true;
}

bool doContain(string whole, string inside){
    if (toLower(whole).find(toLower(inside)) != string::npos)
        return false;
        
    return true;
}

bool checkPassword (Account acc) {
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

    

    return true;
}

bool checkRegister(Account &acc, int filter[], int n) {
    if (checkUsername(acc.username, filter, n) && checkPassword(acc)) {
        cout << "You have successfully registered!\n";
        acc.isLoggedIn = true;
        return true;
    }
    return false;
}

//Đẩy account đã đăng ký thành công vào file, gọi hàm này khi thao tác chức năng đăng ký
void Registration(Account &acc, int filter[], int n) {
    cout << "Username: ";
    getline(cin, acc.username, '\n');
    cout << "Password: ";
    getline(cin, acc.password, '\n');

    ofstream ofs("Fail.txt", ios::app);
    while (!checkRegister(acc, filter, n)) {
        ofs << acc.username << " " << acc.password << endl;

        cout << "\nPlease re-enter your username and password!\n";
        cout << "Username: ";
        getline(cin, acc.username, '\n');
        cout << "Password: ";
        getline(cin, acc.password, '\n');
    }
    ofs.close();

    //Đẩy account vào file
    ofstream out("SignUp.txt", ios::app);
    out << acc.username << " " << acc.password << endl;
    // cin.ignore();
    out.close();
    
    cout << "Ket thuc registration\n";
}

void MultipleRegistration(Account &acc, int filter[], int n, vector<Account> allUsers){
    cout << "Input the amount of registration: ";
    int amount;
    cin >> amount;
    
    for (int i = 0; i < amount; i++)
        Registration(acc, filter, n);
        
    
}

void LogIn(Account &acc, int filter[], int n, vector<Account> allUsers){
    cout << "Welcome to login screen.\n";
    cout << "Name: " << acc.username << endl;
    cout << "Pass: " << acc.password << endl;
    cout << "isLoggedIn: " << acc.isLoggedIn << endl;
    cout << "Input your username: ";
    cin >> acc.username;
    cout << "Input your password: ";
    cin >> acc.password;
    
    if (!checkHash(acc.username, filter, n)){
        cout << "Not on our database.\n";
        return;
    }
    
    for (int i = 0; i < allUsers.size(); i++)
        if (acc.username == allUsers[i].username && acc.password == allUsers[i].password){
            cout << "Login successfully.\n";
            acc.password = allUsers[i].password;
            acc.isLoggedIn = true;
        }
}

void changePassword(Account &acc, int filter[], int n){
    if (!acc.isLoggedIn){
        cout << "You haven't logged in yet.\n";
        return;
    }
    
    string password;
    cout << "Input your new password: ";
    password = acc.password;
    cin >> acc.password;
    
    while (!checkPassword(acc)) {

        cin.ignore();
        cout << "\nPlease re-enter your password!\n";
        cout << "Password: ";
        password = acc.password;
        getline(cin, acc.password, '\n');
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
    
    cout << "Password changed successfully.\n";
}
