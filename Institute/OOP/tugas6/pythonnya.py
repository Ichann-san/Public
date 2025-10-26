#include <cstdio>
#include <cstring>

// Global lookup table
int brailleToChar[64];

void initLookup() {
    memset(brailleToChar, -1, sizeof(brailleToChar));
    
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
}

char line1[10005], line2[10005], line3[10005];
char result[10005];

int main() {
    initLookup();
    
    while (fgets(line1, 10005, stdin)) {
        int len1 = strlen(line1);
        if (len1 > 0 && line1[len1-1] == '\n') line1[--len1] = '\0';
        
        if (len1 == 1 && line1[0] == '0') break;
        
        if (!fgets(line2, 10005, stdin) || !fgets(line3, 10005, stdin)) break;
        
        int len2 = strlen(line2);
        if (len2 > 0 && line2[len2-1] == '\n') line2[--len2] = '\0';
        
        int len3 = strlen(line3);
        if (len3 > 0 && line3[len3-1] == '\n') line3[--len3] = '\0';
        
        if (len1 != len2 || len1 != len3 || (len1 & 1)) {
            puts("?");
            continue;
        }
        
        int resultIdx = 0;
        bool numberMode = false;
        bool capitalMode = false;
        int capitalCount = 0;
        bool error = false;
        bool prevWasLetterSign = false;
        
        for (int i = 0; i < len1 && !error; i += 2) {
            int d0 = line1[i] - '0';
            int d1 = line2[i] - '0';
            int d2 = line3[i] - '0';
            int d3 = line1[i+1] - '0';
            int d4 = line2[i+1] - '0';
            int d5 = line3[i+1] - '0';
            
            int pattern = (d0 << 5) | (d1 << 4) | (d2 << 3) | (d3 << 2) | (d4 << 1) | d5;
            
            // Number sign: 3-4-5-6
            if (pattern == 0b001111) {
                numberMode = true;
                capitalMode = false;
                capitalCount = 0;
                prevWasLetterSign = false;
                continue;
            }
            
            // Letter sign: 5-6
            if (pattern == 0b000011) {
                numberMode = false;
                capitalMode = false;
                capitalCount = 0;
                prevWasLetterSign = true;
                continue;
            }
            
            // Capital sign: 6
            if (pattern == 0b000001) {
                capitalCount++;
                if (capitalCount >= 2) {
                    capitalMode = true;
                }
                prevWasLetterSign = false;
                continue;
            }
            
            // TION contraction: 1-3-4-5 (must be preceded by letter sign)
            if (pattern == 0b101110 && prevWasLetterSign) {
                if (capitalMode || capitalCount == 1) {
                    result[resultIdx++] = 'T';
                    result[resultIdx++] = 'I';
                    result[resultIdx++] = 'O';
                    result[resultIdx++] = 'N';
                } else {
                    result[resultIdx++] = 't';
                    result[resultIdx++] = 'i';
                    result[resultIdx++] = 'o';
                    result[resultIdx++] = 'n';
                }
                if (capitalCount == 1) capitalCount = 0;
                prevWasLetterSign = false;
                continue;
            }
            
            // TH contraction: 1-4-5-6
            if (pattern == 0b100111) {
                if (capitalMode || capitalCount == 1) {
                    result[resultIdx++] = 'T';
                    result[resultIdx++] = 'H';
                } else {
                    result[resultIdx++] = 't';
                    result[resultIdx++] = 'h';
                }
                if (capitalCount == 1) capitalCount = 0;
                prevWasLetterSign = false;
                // TH can be followed by numbers without switching modes
                continue;
            }
            
            // Space/blank
            if (pattern == 0) {
                if (numberMode) {
                    result[resultIdx++] = '0';
                } else {
                    result[resultIdx++] = ' ';
                    capitalMode = false;
                    capitalCount = 0;
                }
                prevWasLetterSign = false;
                continue;
            }
            
            // Regular letter/number
            int ch = brailleToChar[pattern];
            if (ch == -1) {
                error = true;
                break;
            }
            
            if (numberMode) {
                int digit = ch - 'a' + 1;
                if (digit >= 1 && digit <= 9) {
                    result[resultIdx++] = '0' + digit;
                } else if (ch == 'j') {
                    result[resultIdx++] = '0';
                } else {
                    error = true;
                    break;
                }
            } else {
                if (capitalMode || capitalCount == 1) {
                    result[resultIdx++] = ch - 32;
                    if (capitalCount == 1) capitalCount = 0;
                } else {
                    result[resultIdx++] = ch;
                }
            }
            prevWasLetterSign = false;
        }
        
        if (error) {
            puts("?");
        } else {
            result[resultIdx] = '\0';
            puts(result);
        }
    }
    
    return 0;
}