#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct Account {
    string username;
    string password;
    bool isLoggedIn = false;
};

int h1(string a, int n);
int h2(string a, int n);
int h3(string a, int n);
int h4(string a, int n);
int h5(string a, int n);

bool checkHash(string a, int filter[],  int n);
void insertBloom(string a, int filter[], int n);
void loadAllUser(string fileName, vector<Account> &names);
void loadAllWeakPassword(string fileName, vector<string> &pass);
void initUserFilter(int filter[], int n, vector<Account> data);
void initPassFilter(int filter[], int n, vector<string> data);

bool checkUsername(string user, int filter[], int n, vector<Account> accounts);
bool checkPassword (Account acc, int weakPassFilter[], int n, vector<string> weakPass);
bool checkRegister(Account &acc, int userFilter[], int n, vector<Account> accounts, int weakPassFilter[], int nPass, vector<string> weakPass);

void Registration(Account &acc, int userFilter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass);
void AutoRegistration(Account &acc, int userFilter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass);
void MultipleRegistration(Account &acc, int filter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass);
void LogIn(Account &acc, int filter[], int n, vector<Account> allUsers);
void changePassword(Account &acc, int filter[], int n, int weakPassFilter[], int nPass, vector<string> weakPass);