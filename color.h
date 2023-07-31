#ifndef COLOR
#define COLOR

#include <iostream>
#include <string>
#include <string>
#include <string.h>
#include <Windows.h>

using namespace std;

const string rainbow[] = {"#FF0000", "#FFA500", "#FFFF00", "#5dc591", "#84ff01", "#077712", "#00FFFF", "#ADD8E6", "#0000FF", "#4B0082", "#FFC0CB", "#EE82EE", "#FF69B4", "#FF1493", "#800000"};

#define COLOR_RESET "\033[0m"
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

string foreg = "\033[0m";
string backg = "\033[0m";

#define COLOR_RESET "\033[0m"
// #define cout cout<<foreg<<backg
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif


string dye(string color, string text = "▞▞▞▞▞█▓▒░", string resetTo = foreg){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), NULL, 16);
    int g = stoi(color.substr(2, 2), NULL, 16);
    int b = stoi(color.substr(4, 2), NULL, 16);
    
    return "\033[38;2;" + std::to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text + resetTo;
}

string dyeAll(string color){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), NULL, 16);
    int g = stoi(color.substr(2, 2), NULL, 16);
    int b = stoi(color.substr(4, 2), NULL, 16);
    
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}

string tint(string color, string text = "hello", string resetTo = backg){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), NULL, 16);
    int g = stoi(color.substr(2, 2), NULL, 16);
    int b = stoi(color.substr(4, 2), NULL, 16);
    
    return "\033[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text + resetTo;
}

string tintAll(string color, string text = "hello"){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), NULL, 16);
    int g = stoi(color.substr(2, 2), NULL, 16);
    int b = stoi(color.substr(4, 2), NULL, 16);
    
    return "\033[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}

void testColor(){
    SetConsoleOutputCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
	cout << dye("#cba6f7", "Hex color code can be written with/without # ,like dye(\"#cba6f7\", textToDye)") << endl;
	cout << dye("cba6f7", "...or dye(\"cba6f7\", anotherTextToDye)") << endl;
    
    cout << "...and it automatically resets, even written inline like " << dye("ff0000","t") << dye("00ff00", "h") << dye("0000ff", "i") << dye("ffffff","s") << ", and " << tint("437213", "background") << " too." << endl;
    
    cout << dye("#ff0000") << endl;
    cout << dye("#ffa500") << endl;
    cout << dye("#ffff00") << endl;
    cout << dye("#008000") << endl;
    cout << dye("#0000ff") << endl;
    cout << dye("#4b0082") << endl;
    cout << dye("#ee82ee") << endl;
    
    cout << "And now, the classics..." << endl;
    
    cout << tint("#ff0000") << endl;
    cout << tint("#ffa500") << endl;
    cout << tint("#ffff00") << endl;
    cout << tint("#008000") << endl;
    cout << tint("#0000ff") << endl;
    cout << tint("#4b0082") << endl;
    cout << tint("#ee82ee") << endl;
}

#endif