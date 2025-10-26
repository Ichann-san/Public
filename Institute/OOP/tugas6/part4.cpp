#include <cstdio>
#include <cstring>

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

char line1[10005], line2[10005], line3[10005], result[10005];

int main() {
    initLookup();
    
    while (fgets(line1, 10005, stdin)) {
        // Remove newline from line1
        int len1 = strlen(line1);
        if (len1 > 0 && line1[len1-1] == '\n') line1[--len1] = '\0';
        
        // Check termination
        if (len1 == 1 && line1[0] == '0') break;
        
        // Read line2 and line3
        if (!fgets(line2, 10005, stdin) || !fgets(line3, 10005, stdin)) break;
        
        int len2 = strlen(line2);
        if (len2 > 0 && line2[len2-1] == '\n') line2[--len2] = '\0';
        
        int len3 = strlen(line3);
        if (len3 > 0 && line3[len3-1] == '\n') line3[--len3] = '\0';
        
        // Validate lengths
        if (len1 != len2 || len1 != len3 || (len1 & 1)) {
            puts("?");
            continue;
        }
        
        // State variables
        int resultIdx = 0;
        bool numberMode = false;
        bool capitalMode = false;
        int capitalCount = 0;
        bool prevWasLetterSign = false;
        bool error = false;
        
        // Process each cell (2 columns per cell)
        for (int i = 0; i < len1; i += 2) {
            // Read 6 dots
            int d1 = line1[i] - '0';
            int d2 = line2[i] - '0';
            int d3 = line3[i] - '0';
            int d4 = line1[i+1] - '0';
            int d5 = line2[i+1] - '0';
            int d6 = line3[i+1] - '0';
            
            // Build pattern
            int pattern = (d1 << 5) | (d2 << 4) | (d3 << 3) | (d4 << 2) | (d5 << 1) | d6;
            
            // STATE 1: Blank (000000)
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
            
            // STATE 2: Capital Sign (dot 6 = 000001)
            if (pattern == 0b000001) {
                capitalCount++;
                if (capitalCount >= 2) {
                    capitalMode = true;
                }
                prevWasLetterSign = false;
                continue;
            }
            
            // STATE 3: Letter Sign (dots 5-6 = 000011)
            if (pattern == 0b000011) {
                numberMode = false;
                prevWasLetterSign = true;
                continue;
            }
            
            // STATE 4: Number Sign (dots 3-4-5-6 = 001111)
            if (pattern == 0b001111) {
                numberMode = true;
                capitalMode = false;
                capitalCount = 0;
                prevWasLetterSign = false;
                continue;
            }
            
            // STATE 5: TH Contraction (dots 1-4-5-6 = 100111)
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
                continue;
            }
            
            // STATE 6 & 7: Regular Character or TION
            int ch = brailleToChar[pattern];
            
            // STATE 8: Invalid pattern
            if (ch == -1) {
                error = true;
                break;
            }
            
            // STATE 7: TION Contraction (letter sign + 'n')
            if (ch == 'n' && prevWasLetterSign) {
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
            
            // STATE 6: Regular Character
            if (numberMode) {
                // In number mode: a-j become 1-9,0
                if (ch >= 'a' && ch <= 'i') {
                    result[resultIdx++] = '1' + (ch - 'a');
                } else if (ch == 'j') {
                    result[resultIdx++] = '0';
                } else {
                    // k-z invalid in number mode
                    error = true;
                    break;
                }
            } else {
                // In letter mode
                if (capitalMode || capitalCount == 1) {
                    result[resultIdx++] = ch - 32; // Uppercase
                    if (capitalCount == 1) capitalCount = 0;
                } else {
                    result[resultIdx++] = ch;
                }
            }
            
            prevWasLetterSign = false;
        }
        
        // Output result
        if (error) {
            puts("?");
        } else {
            result[resultIdx] = '\0';
            puts(result);
        }
    }
    
    return 0;
}