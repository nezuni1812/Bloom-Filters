#include <iostream>
#include <vector>

using namespace std;

struct Account {
    string username;
    string password;
    bool isLoggedIn = false;
};

int polyNominalRollingHashing(string a, long n, long long p, bool debug);
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
void MultipleRegistration(Account &acc, int filter[], int n, vector<Account> &accounts, int weakPassFilter[], int nPass, vector<string> weakPass);
void LogIn(Account &acc, int filter[], int n, vector<Account> allUsers);
void changePassword(Account &acc, int filter[], int n, int weakPassFilter[], int nPass, vector<string> weakPass);