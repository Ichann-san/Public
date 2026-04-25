#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ull = unsigned long long;

// Fast Hex Converter (Uppercase) - O(1) string allocations
inline string toHex(ull num) {
    if (num == 0) return "0";
    char buf[17];
    int idx = 16;
    buf[idx] = '\0';
    const char* hexChars = "0123456789ABCDEF";
    while (num > 0) {
        buf[--idx] = hexChars[num & 15];
        num >>= 4;
    }
    return string(&buf[idx]);
}

// O(1) Absolute Index Calculation
inline ull getGlobalIndex(ull X) {
    if (X == 0) return 0;
    ull K = 1, temp = X;
    while (temp >= 16) { temp >>= 4; K++; }
    if (K == 1) return X - 1; // Base case (1-F)
    
    // Calculate using Bitwise: 16^(K-1) == 1ULL << (4 * (K - 1))
    ull pangkat_16 = 1ULL << (4 * (K - 1));
    return K * X - ((pangkat_16 - 1) / 15) - pangkat_16;
}

// FASE 1: GENERATE CANDIDATES (Kumpulin Tersangka)
vector<ull> generateCandidates(const string& S) {
    vector<ull> c;
    int n = S.length();
    const string hexChars = "0123456789ABCDEF";
    const string nonZeroHex = "123456789ABCDEF";

    // Case 1: Substring within S forms an integer
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            string sub = S.substr(i, j - i);
            if (sub[0] != '0') {
                ull Y = stoull(sub, nullptr, 16);
                int max_d = min(32, 32 / (int)sub.length() + 2);
                for (int d = 0; d < max_d; d++) {
                    if (Y > (ull)d) c.push_back(Y - d);
                }
            }
        }
    }

    // Case 2: Crossing 2 Numbers
    for (int i = 1; i < n; i++) {
        string tail = S.substr(0, i);
        string head = S.substr(i);

        // Normal splits
        if (tail[0] != '0') {
            ull X_tail = stoull(tail, nullptr, 16);
            if (toHex(X_tail + 1).find(head) == 0) c.push_back(X_tail);
            
            for (char h : nonZeroHex) {
                ull X_val = stoull(string(1, h) + tail, nullptr, 16);
                if (toHex(X_val + 1).find(head) == 0) c.push_back(X_val);
            }
        }

        if (head[0] != '0') {
            for (int k = 0; k < 6; k++) {
                string X_str = head + string(k, '0') + tail;
                if (X_str.length() > 15) continue; // Prevent stoull overflow
                ull X_val = stoull(X_str, nullptr, 16);
                if (toHex(X_val + 1).find(head) == 0) c.push_back(X_val);
            }
        }
        
        // Handle carry effect specifically for 'F'
        if (head[0] != '0' && tail.find_first_not_of('F') == string::npos) {
            ull head_val = stoull(head, nullptr, 16);
            if (head_val > 0) {
                string head_prev = (head_val - 1 == 0) ? "" : toHex(head_val - 1);
                for (int k = 0; k < 6; k++) {
                    string test_str = head_prev + string(k, 'F') + tail;
                    if (test_str.length() <= 15) {
                        c.push_back(stoull(test_str, nullptr, 16));
                    }
                }
            }
        }
    }

    // Case 3 & 4: Angka full F and Fully Embedded
    for (int k = 1; k < 8; k++) {
        ull f_val = stoull(string(k, 'F'), nullptr, 16);
        c.push_back(f_val);
        if (f_val > 1) c.push_back(f_val - 1);
    }

    if (S[0] != '0') c.push_back(stoull(S, nullptr, 16));
    
    for (char h : nonZeroHex) c.push_back(stoull(string(1, h) + S, nullptr, 16));
    for (char h : hexChars) {
        if (S[0] != '0') c.push_back(stoull(S + string(1, h), nullptr, 16));
    }

    // Use Sort & Unique instead of Set for performance
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    
    return c;
}

// ALUR UTAMA
void solve() {
    string S;
    if (!(cin >> S)) return;
    
    // Cegah limit C++ ULL
    // if (S.length() > 15) {
    //     cout << "String terlalu panjang untuk simulasi ULL C++.\n";
    //     return;
    // }

    // 1. Kumpulkan tebakan
    vector<ull> candidates = generateCandidates(S);
    vector<ull> answers;

    // 2. Buat zona uji dan cari S
    for (ull X : candidates) {
        if (X == 0) continue;
        string T;
        T.reserve(2500); // Rakit 150 angka ke depan (~2400 char approx)
        ull curr = X;
        
        for (int i = 0; i < 150; i++) {
            T += toHex(curr++);
        }
        
        size_t start = 0;
        while (true) {
            size_t idx = T.find(S, start);
            if (idx == string::npos) break;
            
            // 3. Kalkulasi index mutlak kalau ketemu
            answers.push_back(getGlobalIndex(X) + idx);
            start = idx + 1; // Geser sedikit untuk cari overlap
        }
    }

    if (answers.empty()) {
        cout << "Pola tidak ditemukan.\n";
        return;
    }

    // 4. Seleksi kemunculan non-overlapping
    sort(answers.begin(), answers.end());
    answers.erase(unique(answers.begin(), answers.end()), answers.end());

    ull first = answers[0];
    for (size_t i = 1; i < answers.size(); i++) {
        if (answers[i] >= first + S.length()) {
            cout << (answers[i] - first - S.length()) << "\n";
            return;
        }
    }

    cout << "Hanya 1 kemunculan yang ditemukan.\n";
}

int main() {
    // Fast I/O for Competitive Programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}