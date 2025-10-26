#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Cell {
    int dots[6]; // dots 1-6
};

string decode() {
    string line1, line2, line3;
    getline(cin, line1);
    getline(cin, line2);
    getline(cin, line3);
    
    if (line1.length() == 1 && line1[0] == '0') return "END";
    
    // Parse cells
    int n = line1.length() / 2;
    vector<Cell> cells(n);
    
    for (int i = 0; i < n; i++) {
        cells[i].dots[0] = line1[i*2] - '0';     // dot 1
        cells[i].dots[1] = line2[i*2] - '0';     // dot 2
        cells[i].dots[2] = line3[i*2] - '0';     // dot 3
        cells[i].dots[3] = line1[i*2+1] - '0';   // dot 4
        cells[i].dots[4] = line2[i*2+1] - '0';   // dot 5
        cells[i].dots[5] = line3[i*2+1] - '0';   // dot 6
    }
    
    string result = "";
    bool numberMode = false;
    bool capitalMode = false;
    int capitalCount = 0;
    
    for (int i = 0; i < n; i++) {
        Cell c = cells[i];
        
        // Check for special signs
        // Number sign: 3-4-5-6
        if (!c.dots[0] && !c.dots[1] && c.dots[2] && c.dots[3] && c.dots[4] && c.dots[5]) {
            numberMode = true;
            capitalMode = false;
            capitalCount = 0;
            continue;
        }
        
        // Letter sign: 5-6
        if (!c.dots[0] && !c.dots[1] && !c.dots[2] && !c.dots[3] && c.dots[4] && c.dots[5]) {
            numberMode = false;
            capitalMode = false;
            capitalCount = 0;
            continue;
        }
        
        // Capital sign: 6
        if (!c.dots[0] && !c.dots[1] && !c.dots[2] && !c.dots[3] && !c.dots[4] && c.dots[5]) {
            capitalCount++;
            if (capitalCount >= 2) {
                capitalMode = true;
            }
            continue;
        }
        
        // TH contraction: 1-4-5-6
        if (c.dots[0] && !c.dots[1] && !c.dots[2] && c.dots[3] && c.dots[4] && c.dots[5]) {
            if (numberMode) return "?";
            result += "th";
            if (capitalCount == 1) capitalCount = 0;
            continue;
        }
        
        // TION contraction: 1-3-4-5
        if (c.dots[0] && !c.dots[1] && c.dots[2] && c.dots[3] && c.dots[4] && !c.dots[5]) {
            if (numberMode) return "?";
            result += "tion";
            if (capitalCount == 1) capitalCount = 0;
            continue;
        }
        
        // Space/blank
        if (!c.dots[0] && !c.dots[1] && !c.dots[2] && !c.dots[3] && !c.dots[4] && !c.dots[5]) {
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
        int index = 0;
        if (c.dots[0]) index += 1;
        if (c.dots[1]) index += 2;
        if (c.dots[2]) index += 4;
        if (c.dots[3]) index += 8;
        if (c.dots[4]) index += 16;
        
        // Map to letter
        char letter = '?';
        if (index >= 1 && index <= 26) {
            letter = 'a' + index - 1;
        }
        
        if (letter == '?') return "?";
        
        if (numberMode) {
            // Convert to digit
            if (index >= 1 && index <= 10) {
                result += '0' + (index % 10);
            } else {
                return "?";
            }
        } else {
            if (capitalMode || capitalCount == 1) {
                result += toupper(letter);
                if (capitalCount == 1) capitalCount = 0;
            } else {
                result += letter;
            }
        }
    }
    
    return result;
}

int main() {
    while (true) {
        string result = decode();
        if (result == "END") break;
        cout << result << endl;
    }
    return 0;
}