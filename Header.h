#include <iostream>
#include <vector>

using namespace std;

struct Account {
    string username;
    string password;
    bool isLoggedIn = false;
};

// // Reference: https://cp-algorithms.com/string/string-hashing.html#calculation-of-the-hash-of-a-string
// // Hashing cho bit array: nhận một string -> return một hash
// // Thay đổi số p để đưa ra các hash khác nhau
// int polyNominalRollingHashing(string a, long n, long long p = 19, bool debug = false);

// // Kiểm tra xem có phần tử trùng trong filter Bloom không
// bool checkHash(string a, int filter[],  int n);

// // Thêm một phần tử vào filter Bloom: đánh dấu thành bit 1 ở 3 vị trí trên bit array
// void insertBloom(string a, int filter[], int n);

// // Lấy thông tin User từ file -> vector
// void loadAllUser(string fileName, vector<Account> &names);

// // Lấy thông tin Weak password từ file -> vector
// void loadAllWeakPassword(string fileName, vector<string> &pass);

// // Khởi tạo bit array bằng vector chứa tất cả User
// void initUserFilter(int filter[], int n, vector<Account> data);

// // Khởi tạo bit array bằng vector chứa tất cả Weak password
// void initPassFilter(int filter[], int n, vector<string> data);

// // Viết thường
// string toLower(string a);

// bool checkUsername(string user, int filter[], int n, vector<Account> accounts);

// bool doContain(string whole, string inside);

// bool checkPassword (Account acc, int weakPassFilter[], int n, vector<string> weakPass);

// bool checkRegister(Account &acc, int userFilter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass);

// //Đẩy account đã đăng ký thành công vào file, gọi hàm này khi thao tác chức năng đăng ký
// void Registration(Account &acc, int userFilter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass);

// void MultipleRegistration(Account &acc, int filter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass);

// void LogIn(Account &acc, int filter[], int n, vector<Account> allUsers);

// void changePassword(Account &acc, int filter[], int n, int weakPassFilter[], int nPass, vector<string> weakPass);

