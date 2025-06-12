#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<int> stack;
    string s;
    int n=0;

    while (cin >> s) {
        if (s == "C") {
            if (!stack.empty()) stack.pop_back();
        } else if (s == "D") {
            if (!stack.empty()) stack.push_back(2 * stack.back());
        } else if (s == "+") {
            int n = stack.size();
            if (n >= 2) {
                stack.push_back(stack[n - 1] + stack[n - 2]);
            }
        } else {
            stack.push_back(stoi(s));
        }
    }

    for (int score : stack) {
        n += score;
    }

    cout << n << endl;
    return 0;
}
