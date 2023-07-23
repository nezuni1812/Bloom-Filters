//Nhập username và password xong kiểm tra
#include "header.h"

bool checkUsername(string user) {
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
        
    //Chưa code phần check xem có username trùng hay không

    
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

    //Chưa code weak password
    return true;
}

bool checkRegister(Account acc) {
    if (checkUsername(acc.username) && checkPassword(acc)) {
        cout << "You have successfully registered!\n";
        return true;
    }
    return false;
}

//Đẩy account đã đăng ký thành công vào file, gọi hàm này khi thao tác chức năng đăng ký
void Registration() {
    Account acc;
    cout << "Username: ";
    getline(cin, acc.username, '\n');
    cout << "Password: ";
    getline(cin, acc.password, '\n');

    ofstream ofs("Fail.txt", ios::app);
    while (!checkRegister(acc)) {
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
