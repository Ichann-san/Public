#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Global lookup table - computed once
int brailleToChar[64]; // 2^6 possible patterns
bool initialized = false;

void initLookup() {
    if (initialized) return;
    
    // Initialize all to -1 (invalid)
    for (int i = 0; i < 64; i++) {
        brailleToChar[i] = -1;
    }
    
    // Braille patterns for a-z (dots as binary: 123456)
    brailleToChar[0b100000] = 'a'; brailleToChar[0b110000] = 'b'; 
    brailleToChar[0b100100] = 'c'; brailleToChar[0b100110] = 'd';
    brailleToChar[0b100010] = 'e'; brailleToChar[0b110100] = 'f'; 
    brailleToChar[0b110110] = 'g'; brailleToChar[0b110010] = 'h';
    brailleToChar[0b010100] = 'i'; brailleToChar[0b010110] = 'j'; 
    brailleToChar[0b101000] = 'k'; brailleToChar[0b111000] = 'l';
    brailleToChar[0b101100] = 'm'; brailleToChar[0b101110] = 'n'; 
    brailleToChar[0b101010] = 'o'; brailleToChar[0b111100] = 'p';
    brailleToChar[0b111110] = 'q'; brailleToChar[0b111010] = 'r'; 
    brailleToChar[0b011100] = 's'; brailleToChar[0b011110] = 't';
    brailleToChar[0b101001] = 'u'; brailleToChar[0b111001] = 'v'; 
    brailleToChar[0b010111] = 'w'; brailleToChar[0b101101] = 'x';
    brailleToChar[0b101111] = 'y'; brailleToChar[0b101011] = 'z';
    
    initialized = true;
}

inline int cellToInt(int d0, int d1, int d2, int d3, int d4, int d5) {
    return (d0 << 5) | (d1 << 4) | (d2 << 3) | (d3 << 2) | (d4 << 1) | d5;
}

string decode() {
    string line1, line2, line3;
    getline(cin, line1);
    getline(cin, line2);
    getline(cin, line3);
    
    if (line1.length() == 1 && line1[0] == '0') return "END";
    
    int len = line1.length();
    
    // Check line lengths are consistent and even
    if (line2.length() != len || line3.length() != len || len % 2 != 0) return "?";
    
    string result;
    result.reserve(len); // Pre-allocate
    
    bool numberMode = false;
    bool capitalMode = false;
    int capitalCount = 0;
    
    for (int i = 0; i < len; i += 2) {
        int d0 = line1[i] - '0';
        int d1 = line2[i] - '0';
        int d2 = line3[i] - '0';
        int d3 = line1[i+1] - '0';
        int d4 = line2[i+1] - '0';
        int d5 = line3[i+1] - '0';
        
        int pattern = cellToInt(d0, d1, d2, d3, d4, d5);
        
        // Number sign: 3-4-5-6 = 001111
        if (pattern == 0b001111) {
            numberMode = true;
            capitalMode = false;
            capitalCount = 0;
            continue;
        }
        
        // Letter sign: 5-6 = 000011
        if (pattern == 0b000011) {
            numberMode = false;
            capitalMode = false;
            capitalCount = 0;
            continue;
        }
        
        // Capital sign: 6 = 000001
        if (pattern == 0b000001) {
            capitalCount++;
            if (capitalCount >= 2) {
                capitalMode = true;
            }
            continue;
        }
        
        // TH contraction: 1-4-5-6 = 100111
        if (pattern == 0b100111) {
            if (numberMode) return "?";
            if (capitalMode || capitalCount == 1) {
                result += "TH";
            } else {
                result += "th";
            }
            if (capitalCount == 1) capitalCount = 0;
            continue;
        }
        
        // TION contraction: 1-3-4-5 = 101110
        if (pattern == 0b101110) {
            if (numberMode) return "?";
            if (capitalMode || capitalCount == 1) {
                result += "TION";
            } else {
                result += "tion";
            }
            if (capitalCount == 1) capitalCount = 0;
            continue;
        }
        
        // Space/blank = 000000
        if (pattern == 0) {
            if (numberMode) {
                result += '0';
            } else {
                result += ' ';
                capitalMode = false;
                capitalCount = 0;
            }
            continue;
        }
        
        // Regular letter/number
        int ch = brailleToChar[pattern];
        if (ch == -1) return "?";
        
        if (numberMode) {
            // Convert letter to digit (a=1, j=0)
            int digit = ch - 'a' + 1;
            if (digit >= 1 && digit <= 9) {
                result += ('0' + digit);
            } else if (ch == 'j') {
                result += '0';
            } else {
                return "?";
            }
        } else {
            if (capitalMode || capitalCount == 1) {
                result += (ch - 32); // Convert to uppercase
                if (capitalCount == 1) capitalCount = 0;
            } else {
                result += ch;
            }
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    initLookup();
    
    while (true) {
        string result = decode();
        if (result == "END") break;
        cout << result << '\n';
    }
    return 0;
}