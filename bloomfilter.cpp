#include "header.h"

int h1(string a, int n = 10007){
    // https://theartincode.stanis.me/008-djb2/
    long long hash = 5381;

    for (int i = 0; i < a.size(); i++){
        hash = (((hash << 5) + hash) + a[i]) % n; /* Equivalent to: (hash * 33 + a[i]) % n but it faster*/
    }

    return hash;
}

int h2(string a, int n = 10007){
    // Reference: https://cp-algorithms.com/string/string-hashing.html#calculation-of-the-hash-of-a-string
    long long hash = 0;
    long long power = 1;
    long long p = 311;
    for (int i = 0; i < a.size(); i++){
        long long toNum = a[i];
        
        hash = (hash + toNum * power) % n;
        power = (power * p) % n;
    }
    
    
    return hash % n;
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
    int base = 59;
    
    for (int i = 0; i < a.size(); i++){
        hash = (hash + (a[i]*base)) % n;
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
    
    return !(filter[pos1] == 0 || filter[pos2] == 0 || filter[pos3] == 0 || filter[pos4] == 0 || filter[pos5] == 0);
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
}

// Lấy thông tin User từ file -> vector
void loadAllUser(string fileName, vector<Account> &names){
    ifstream in(fileName.c_str());
    
    names.clear();
    
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
