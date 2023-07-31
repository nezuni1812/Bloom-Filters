#ifndef COLOR
#define COLOR

#include <iostream>
#include <string>
#include <string>
#include <string.h>
#include <Windows.h>

using namespace std;


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

#endif