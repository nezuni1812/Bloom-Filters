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

void loadAllData(string fileName, vector<string> &names){
    ifstream in(fileName.c_str());
    
    int idx = 0;
    string temp;
    while (in >> temp){
        names.push_back(temp);
        getline(in, temp);
        idx++;
    }
    
    in.close();
}

void initBloomFilter(int filter[], int n, vector<string> data){
    for (int i = 0; i < data.size(); i++)
        insertBloom(data[i], filter, n);
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

    if (!upper || !lower || !num || !specialchar || doContain(acc.password, acc.username)) {
        cout << "Your password must contain uppercase, lowercase, numbers and special characters and must not contain your username.\n";
        return false;
    }

    //Chưa code weak password
    return true;
}

bool checkRegister(Account acc, int filter[], int n) {
    if (checkUsername(acc.username, filter, n) && checkPassword(acc)) {
        cout << "You have successfully registered!\n";
        acc.isLoggedIn = true;
        return true;
    }
    return false;
}

//Đẩy account đã đăng ký thành công vào file, gọi hàm này khi thao tác chức năng đăng ký
void Registration(int filter[], int n) {
    Account acc;
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
    out.close();
}

void changePassword(Account acc){
    if (!acc.isLoggedIn){
        cout << "You haven't logged in yet.\n";
        return;
    }
    
    
}
