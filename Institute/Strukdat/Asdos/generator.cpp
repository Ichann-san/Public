#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

const int N_MAX = 10;
const int V_MAX = 1000;
const int T_MAX = 100;
const int K_MAX = 10000;

vector<string> load_data(const string& filename) {
    vector<string> data;
    ifstream file(filename);
    string word;
    while (file >> word) data.push_back(word);
    return data;
}

int main() {
    random_device rd;
    mt19937 gen(rd());

    vector<string> regions_db = load_data("./regions.txt");
    vector<string> chars_db = load_data("./characters.txt");

    if (regions_db.empty() || chars_db.empty()) {
        cerr << "Error: File regions.txt atau characters.txt tidak ditemukan/kosong!\n";
        return 1;
    }

    // Randomize Constraint
    int n = uniform_int_distribution<>(1, min(N_MAX, (int)regions_db.size()))(gen);
    int t = uniform_int_distribution<>(1, T_MAX)(gen);

    cout << n << "\n";

    shuffle(regions_db.begin(), regions_db.end(), gen);
    shuffle(chars_db.begin(), chars_db.end(), gen);

    vector<string> all_inserted_chars;
    int char_idx = 0;

    // Generate Regions & Visions
    for (int i = 0; i < n; i++) {
        cout << regions_db[i] << "\n";
        
        int v = uniform_int_distribution<>(1, V_MAX)(gen);
        
        for (int j = 0; j < v; j++) {
            string char_name;
            // Jika database habis, akali dengan menambahkan ID di belakang nama
            if (char_idx < chars_db.size()) {
                char_name = chars_db[char_idx++];
            } else {
                char_name = chars_db[uniform_int_distribution<>(0, chars_db.size() - 1)(gen)] + "_" + to_string(char_idx++);
            }
            
            cout << char_name << " ";
            all_inserted_chars.push_back(char_name);
        }
        cout << "end\n";
    }

    // Generate Queries
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        string src, dst;
        int k = uniform_int_distribution<>(1, K_MAX)(gen);

        // 90% chance valid character, 10% chance fake character (untuk test Signal lost karena char ga ada)
        if (uniform_int_distribution<>(1, 100)(gen) > 10) {
            src = all_inserted_chars[uniform_int_distribution<>(0, all_inserted_chars.size() - 1)(gen)];
        } else {
            src = "Ghaib_Sender"; 
        }

        if (uniform_int_distribution<>(1, 100)(gen) > 10) {
            dst = all_inserted_chars[uniform_int_distribution<>(0, all_inserted_chars.size() - 1)(gen)];
        } else {
            dst = "Ghaib_Receiver";
        }

        cout << src << " " << dst << " " << k << "\n";
    }

    return 0;
}