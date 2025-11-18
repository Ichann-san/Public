#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

class Calculator {
private:
    double result;
    string currentInput;
    char lastOperator;
    bool errorState;
    bool hasDecimal;
    int digitCount;
    
    void reset() {
        result = 0.0;
        currentInput = "";
        lastOperator = '\0';
        errorState = false;
        hasDecimal = false;
        digitCount = 0;
    }
    
    double getCurrentNumber() {
        if (currentInput.empty()) return 0.0;
        return stod(currentInput);
    }
    
    void applyOperation(double operand) {
        if (errorState) return;
        
        switch(lastOperator) {
            case '+': result += operand; break;
            case '-': result -= operand; break;
            case 'x': result *= operand; break;
            case ':':
                if (abs(operand) < 1e-100) {
                    errorState = true;
                    return;
                }
                result /= operand;
                break;
            default: result = operand; break;
        }
        
        // Check for overflow or underflow
        if (abs(result) >= 1e100) {
            errorState = true;
            return;
        }
        if (abs(result) <= 1e-100 && result != 0.0) {
            result = 0.0;
        }
    }
    
    string formatOutput(double value) {
        if (errorState) return "    Error.";
        
        double absVal = abs(value);
        
        // Check if scientific notation is needed
        if (absVal >= 99999999.5 || (absVal < 1e-100 && absVal > 0) || 
            (absVal >= 0.5e-4 && round(absVal * 1e8) < 0.5)) {
            
            if (absVal < 1e-100) {
                return "        0.";
            }
            
            // Scientific notation
            int exponent = 0;
            double mantissa = absVal;
            
            if (mantissa >= 1.0) {
                while (mantissa >= 10.0) {
                    mantissa /= 10.0;
                    exponent++;
                }
            } else {
                while (mantissa < 1.0 && mantissa > 0) {
                    mantissa *= 10.0;
                    exponent--;
                }
            }
            
            if (value < 0) mantissa = -mantissa;
            
            // Round mantissa to 4 decimal places
            mantissa = round(mantissa * 10000.0) / 10000.0;
            
            ostringstream oss;
            oss << fixed << setprecision(4) << mantissa;
            string mantissaStr = oss.str();
            
            // Remove trailing zeros after decimal
            size_t dotPos = mantissaStr.find('.');
            if (dotPos != string::npos) {
                while (mantissaStr.back() == '0' && mantissaStr.length() > dotPos + 2) {
                    mantissaStr.pop_back();
                }
            }
            
            string expStr = (exponent < 0 ? "-" : " ") + (abs(exponent) < 10 ? "0" : "") + to_string(abs(exponent));
            
            string result = mantissaStr + expStr;
            return string(10 - result.length(), ' ') + result;
        }
        
        // Normal notation
        double rounded = round(value * 1e8) / 1e8;
        
        ostringstream oss;
        oss << fixed << setprecision(8) << rounded;
        string numStr = oss.str();
        
        // Ensure decimal point
        if (numStr.find('.') == string::npos) {
            numStr += ".";
        }
        
        // Remove trailing zeros but keep at least one after decimal
        size_t dotPos = numStr.find('.');
        while (numStr.back() == '0' && numStr.length() > dotPos + 2) {
            numStr.pop_back();
        }
        
        // Limit to 8 digits + decimal + sign
        size_t signPos = (numStr[0] == '-') ? 1 : 0;
        dotPos = numStr.find('.');
        
        if (dotPos - signPos > 8) {
            numStr = numStr.substr(0, signPos + 8) + ".";
        } else {
            int totalDigits = 0;
            for (char c : numStr) {
                if (isdigit(c)) totalDigits++;
            }
            if (totalDigits > 8) {
                numStr = numStr.substr(0, signPos + 8 + 1);
            }
        }
        
        return string(10 - numStr.length(), ' ') + numStr;
    }
    
public:
    Calculator() { reset(); }
    
    void processKey(const string& key) {
        if (errorState && key != "C") return;
        
        if (key == "C") {
            reset();
        } else if (key >= "0" && key <= "9") {
            if (currentInput == "0" && key == "0") return;
            if (digitCount < 8) {
                currentInput += key;
                if (key != "0" || !currentInput.empty()) digitCount++;
            }
        } else if (key == ".") {
            if (!hasDecimal) {
                if (currentInput.empty()) currentInput = "0";
                currentInput += ".";
                hasDecimal = true;
            }
        } else if (key == "+" || key == "-" || key == "x" || key == ":") {
            if (!currentInput.empty()) {
                applyOperation(getCurrentNumber());
                currentInput = "";
                hasDecimal = false;
                digitCount = 0;
            }
            lastOperator = key[0];
        } else if (key == "=") {
            if (!currentInput.empty()) {
                applyOperation(getCurrentNumber());
            }
            currentInput = "";
            hasDecimal = false;
            digitCount = 0;
            lastOperator = '\0';
        }
    }
    
    string getDisplay() {
        if (!currentInput.empty()) {
            double val = getCurrentNumber();
            return formatOutput(val);
        }
        return formatOutput(result);
    }
};

int main() {
    int t;
    cin >> t;
    cin.ignore();
    
    for (int i = 0; i < t; i++) {
        string line;
        getline(cin, line);
        
        Calculator calc;
        istringstream iss(line);
        string key;
        
        while (iss >> key) {
            key = key.substr(1, key.length() - 2); // Remove brackets
            calc.processKey(key);
        }
        
        cout << calc.getDisplay() << endl;
    }
    
    return 0;
}