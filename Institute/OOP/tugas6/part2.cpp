#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Cell {
    int dots[6];
    
    bool operator==(const vector<int>& pattern) const {
        for (int i = 0; i < 6; i++) {
            if (dots[i] != pattern[i]) return false;
        }
        return true;
    }
};

// Create lookup table for Braille letters a-z
map<string, char> createLetterMap() {
    map<string, char> m;
    // Braille patterns for a-z (based on standard Braille)
    m["100000"] = 'a'; m["110000"] = 'b'; m["100100"] = 'c'; m["100110"] = 'd';
    m["100010"] = 'e'; m["110100"] = 'f'; m["110110"] = 'g'; m["110010"] = 'h';
    m["010100"] = 'i'; m["010110"] = 'j'; m["101000"] = 'k'; m["111000"] = 'l';
    m["101100"] = 'm'; m["101110"] = 'n'; m["101010"] = 'o'; m["111100"] = 'p';
    m["111110"] = 'q'; m["111010"] = 'r'; m["011100"] = 's'; m["011110"] = 't';
    m["101001"] = 'u'; m["111001"] = 'v'; m["010111"] = 'w'; m["101101"] = 'x';
    m["101111"] = 'y'; m["101011"] = 'z';
    return m;
}

string cellToString(const Cell& c) {
    string s = "";
    for (int i = 0; i < 6; i++) {
        s += (c.dots[i] ? '1' : '0');
    }
    return s;
}

string decode() {
    string line1, line2, line3;
    getline(cin, line1);
    getline(cin, line2);
    getline(cin, line3);
    
    if (line1.length() == 1 && line1[0] == '0') return "END";
    
    // Check line lengths are consistent and even
    if (line1.length() != line2.length() || line1.length() != line3.length()) return "?";
    if (line1.length() % 2 != 0) return "?";
    
    // Parse cells
    int n = line1.length() / 2;
    vector<Cell> cells(n);
    
    for (int i = 0; i < n; i++) {
        cells[i].dots[0] = line1[i*2] - '0';
        cells[i].dots[1] = line2[i*2] - '0';
        cells[i].dots[2] = line3[i*2] - '0';
        cells[i].dots[3] = line1[i*2+1] - '0';
        cells[i].dots[4] = line2[i*2+1] - '0';
        cells[i].dots[5] = line3[i*2+1] - '0';
    }
    
    map<string, char> letterMap = createLetterMap();
    string result = "";
    bool numberMode = false;
    bool capitalMode = false;
    int capitalCount = 0;
    
    for (int i = 0; i < n; i++) {
        Cell c = cells[i];
        string pattern = cellToString(c);
        
        // Number sign: 3-4-5-6
        if (pattern == "001111") {
            numberMode = true;
            capitalMode = false;
            capitalCount = 0;
            continue;
        }
        
        // Letter sign: 5-6
        if (pattern == "000011") {
            numberMode = false;
            capitalMode = false;
            capitalCount = 0;
            continue;
        }
        
        // Capital sign: 6
        if (pattern == "000001") {
            capitalCount++;
            if (capitalCount >= 2) {
                capitalMode = true;
            }
            continue;
        }
        
        // TH contraction: 1-4-5-6
        if (pattern == "100111") {
            if (numberMode) return "?";
            if (capitalMode || capitalCount == 1) {
                result += "TH";
            } else {
                result += "th";
            }
            if (capitalCount == 1) capitalCount = 0;
            continue;
        }
        
        // TION contraction: 1-3-4-5
        if (pattern == "101110") {
            if (numberMode) return "?";
            if (capitalMode || capitalCount == 1) {
                result += "TION";
            } else {
                result += "tion";
            }
            if (capitalCount == 1) capitalCount = 0;
            continue;
        }
        
        // Space/blank
        if (pattern == "000000") {
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
        if (letterMap.find(pattern) != letterMap.end()) {
            char letter = letterMap[pattern];
            
            if (numberMode) {
                // Convert letter to digit (a=1, j=0)
                int digit = letter - 'a' + 1;
                if (digit >= 1 && digit <= 9) {
                    result += ('0' + digit);
                } else if (letter == 'j') {
                    result += '0';
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
        } else {
            return "?";
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