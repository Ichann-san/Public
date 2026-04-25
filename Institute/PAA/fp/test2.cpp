#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Cheat Code CP: 128-bit Integer (Batas ~3.4 x 10^38)
typedef unsigned __int128 u128;

// =========================================================
// CP HELPER: I/O 128-bit & HEX PARSER
// =========================================================
u128 parseHex(const string& s) {
    u128 res = 0;
    for (char c : s) {
        res = res * 16;
        if (c >= '0' && c <= '9') res += (c - '0');
        else if (c >= 'A' && c <= 'F') res += (c - 'A' + 10);
    }
    return res;
}

string toHex(u128 num) {
    if (num == 0) return "0";
    string res = "";
    string hexChars = "0123456789ABCDEF";
    while (num > 0) {
        res = hexChars[(int)(num % 16)] + res;
        num /= 16;
    }
    return res;
}

void print128(u128 n) {
    if (n == 0) {
        cout << 0 << "\n";
        return;
    }
    string s = "";
    while (n > 0) {
        s += (char)('0' + (int)(n % 10));
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

// =========================================================
// RUMUS SAKTI O(1) DENGAN BITWISE 128-BIT
// =========================================================
u128 getGlobalIndex(u128 X) {
    u128 K = toHex(X).length();
    if (K == 1) return X - 1; 
    
    // Pastikan angka '1' di-cast ke u128 sebelum di shift agar tidak overflow
    u128 pangkat_16 = ((u128)1) << (4 * (K - 1));
    return K * X - ((pangkat_16 - 1) / 15) - pangkat_16;
}

// =========================================================
// GENERATE CANDIDATES
// =========================================================
set<u128> generateCandidates(string S) {
    set<u128> candidates;
    int n = S.length();

    auto addSafe = [&](string str) {
        if (str.length() <= 31) candidates.insert(parseHex(str));
    };

    // Kasus 1: S memuat angka utuh
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            string sub = S.substr(i, j - i);
            if (sub[0] != '0') {
                u128 Y = parseHex(sub);
                int max_d = min(32, 32 / (int)sub.length() + 2);
                for (int d = 0; d < max_d; d++) {
                    if (Y > d) candidates.insert(Y - d);
                }
            }
        }
    }

    // Kasus 2 & 3: Menyeberang dan Carry Effect (F)
    for (int i = 1; i < n; i++) {
        string tail = S.substr(0, i);
        string head = S.substr(i);

        if (tail[0] != '0') {
            u128 X_tail = parseHex(tail);
            if (toHex(X_tail + 1).find(head) == 0) candidates.insert(X_tail);
            
            for (char h : string("123456789ABCDEF")) {
                u128 X_val = parseHex(string(1, h) + tail);
                if (toHex(X_val + 1).find(head) == 0) candidates.insert(X_val);
            }
        }

        if (head[0] != '0') {
            for (int k = 0; k < 6; k++) {
                string X_str = head + string(k, '0') + tail;
                if (X_str.length() <= 31) {
                    u128 X_val = parseHex(X_str);
                    if (toHex(X_val + 1).find(head) == 0) candidates.insert(X_val);
                }
            }
        }
        
        bool allF = true;
        for (char c : tail) if (c != 'F') allF = false;
        
        if (allF && head[0] != '0') {
            u128 head_val = parseHex(head);
            if (head_val > 0) {
                string head_prev = toHex(head_val - 1);
                if (head_val - 1 == 0) head_prev = ""; 
                for (int k = 0; k < 6; k++) addSafe(head_prev + string(k, 'F') + tail);
            }
        }
    }

    // Kasus 4: Transisi Murni & Fully Embedded
    for (int k = 1; k < 8; k++) {
        u128 f_val = parseHex(string(k, 'F'));
        candidates.insert(f_val);
        if (f_val > 1) candidates.insert(f_val - 1);
    }

    if (S[0] != '0') addSafe(S);
    for (char h : string("123456789ABCDEF")) addSafe(string(1, h) + S);
    for (char h : string("0123456789ABCDEF")) {
        if (S[0] != '0') addSafe(S + string(1, h));
    }

    return candidates;
}

// =========================================================
// MAIN ALGORITHM
// =========================================================
void solve() {
    string S;
    if (!(cin >> S)) return;

    set<u128> candidates = generateCandidates(S);
    set<u128> answers_set;

    for (u128 X : candidates) {
        string T = "";
        u128 curr = X;
        
        // Rakit 150 angka ke depan
        for (int i = 0; i < 150; i++) {
            T += toHex(curr);
            curr++;
        }
        
        size_t start = 0;
        while (true) {
            size_t idx = T.find(S, start);
            if (idx == string::npos) break;
            
            u128 global_idx = getGlobalIndex(X) + idx;
            answers_set.insert(global_idx);
            
            start = idx + 1;
        }
    }

    vector<u128> sorted_idx(answers_set.begin(), answers_set.end());
    
    if (sorted_idx.empty()) {
        cout << "Pola tidak ditemukan.\n";
        return;
    }

    u128 first = sorted_idx[0];
    u128 second = 0;
    bool found_second = false;
    
    for (size_t i = 1; i < sorted_idx.size(); i++) {
        if (sorted_idx[i] >= first + S.length()) {
            second = sorted_idx[i];
            found_second = true;
            break;
        }
    }

    if (found_second) {
        print128(second - first - S.length());
    } else {
        cout << "Hanya 1 kemunculan yang ditemukan.\n";
    }
}

int main() {
    // CP Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    return 0;
}