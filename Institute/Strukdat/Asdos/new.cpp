#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

using namespace std;

int main() {
    ifstream db_file("teyvat_db.txt");
    ofstream out_file("tc_final.in");

    if (!db_file.is_open()) {
        cout << "Bikin dulu file teyvat_db.txt isinya 10 region tadi ya!\n";
        return 1;
    }

    // 1. Copy isi database ke file output dan simpan daftar karakter
    vector<string> all_chars;
    string word;
    int region_count;
    db_file >> region_count;
    out_file << region_count << "\n";

    for (int i = 0; i < region_count; i++) {
        string region_name;
        db_file >> region_name;
        out_file << region_name << "\n";
        
        while (db_file >> word && word != "end") {
            out_file << word << " ";
            all_chars.push_back(word);
        }
        out_file << "end\n";
    }

    // 2. Masukkan 1000 Query
    int total_queries = 1000;
    out_file << total_queries << "\n";

    // Masukkan 20 Hardcoded Edge Cases dulu
    vector<string> edge_cases = {
        "Lauma Linnea 5", "Albedo Donna 5", "Paimon Asmoday 5", "Aether Lumine 10",
        "Traveler Paimon 20", "Venti Zhongli 30", "Venti Zhongli 20", "Deshret Remus 25",
        "Dvalin Durin 20", "Tsaritsa Dainsleif 10", "Rukkhadevata Phanes 20", "Aino Snegurochka 5",
        "Tartaglia Teucer 5", "Lauma Lauma 10", "Alice Rhinedottir 10", "Chasca Ororon 10",
        "Makoto Ei 10", "Skirk Tartaglia 5", "Skirk Tartaglia 15", "Paimon Paimon 0"
    };

    for (const string& ec : edge_cases) {
        out_file << ec << "\n";
    }

    // 3. Generate 980 sisanya secara acak
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> char_dist(0, all_chars.size() - 1);
    uniform_int_distribution<> k_dist(1, 10000); // K diacak sampai 10.000
    uniform_int_distribution<> ghaib_dist(1, 100);

    for (int i = 0; i < (total_queries - 20); i++) {
        string src, dst;
        int k = k_dist(gen);

        // 5% kemungkinan muncul karakter ghaib
        if (ghaib_dist(gen) <= 5) src = "Traveler";
        else src = all_chars[char_dist(gen)];

        if (ghaib_dist(gen) <= 5) dst = "AbyssMage";
        else dst = all_chars[char_dist(gen)];

        out_file << src << " " << dst << " " << k << "\n";
    }

    cout << "Selesai! File tc_final.in berhasil dibuat dengan 1000 queries.\n";
    cout << "Sekarang tinggal run: ./solver < tc_final.in > tc_final.ans\n";

    return 0;
}