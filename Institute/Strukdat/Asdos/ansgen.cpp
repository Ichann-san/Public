#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    cout << "=== Memulai Auto-Generate File .ans ===" << "\n\n";

    for (int i = 1; i <= 5; i++) {
        string in_file = to_string(i) + ".in";
        string ans_file = to_string(i) + ".ans";

        // PERHATIAN: Sesuaikan nama executable solver-mu!
        // Jika di Windows: "solver.exe"
        // Jika di Linux/Mac/WSL: "./solver"
        string command = "final.exe < " + in_file + " > " + ans_file;

        cout << "Mengeksekusi: " << command << " ... ";

        // system() akan menjalankan command string di atas seolah-olah kita mengetiknya di terminal
        int result = system(command.c_str());

        if (result == 0) {
            cout << "Berhasil!" << "\n";
        } else {
            cout << "GAGAL! (Pastikan file " << in_file << " dan solver.exe ada di folder ini)" << "\n";
        }
    }

    cout << "\n=== Semua file .ans selesai di-generate! ===" << "\n";
    return 0;
}