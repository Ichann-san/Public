// mass_balance.cpp
// Solve linear system from the student's assumption:
// product fractions (O2,N2,CO2,SO2) given relative to TOTAL = 700 gmol/hr.
// Variables order: v = [G, F, A1, A2, x, y]
// Equations: S, C, N, O, H2O, total (x+y=700)
// Gaussian elimination with partial pivoting

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const double TOTAL = 700.0;

    // Given / assumptions (from the problem and the student's math)
    // Fuel gas composition
    double fg_CH4 = 0.90;
    double fg_C2H2 = 0.05;
    double fg_O2_in = 0.02;

    // Derived for fuel gas per 1 gmol G
    double G_C = fg_CH4*1.0 + fg_C2H2*2.0;            // C atoms -> CO2 mol
    double G_H_atoms = fg_CH4*4.0 + fg_C2H2*2.0;
    double G_H2O = G_H_atoms / 2.0;                   // H2O mol per gmol G
    double G_stoich_O2 = G_C + G_H_atoms / 4.0;       // O2 needed per gmol G
    double G_O2_in = fg_O2_in;

    // Fuel oil composition (as in student's note: treat as mol-fractions here)
    double F_C = 0.60;
    double F_H_atoms = 0.35;
    double F_S = 0.03;
    double F_H2O = F_H_atoms / 2.0;
    double F_stoich_O2 = F_C + F_H_atoms/4.0 + F_S;   // stoichiometric O2 per gmol F

    // Air compositions
    double a1_O2 = 0.21, a1_N2 = 0.79;
    double a2_O2 = 0.20, a2_N2 = 0.72, a2_CO2 = 0.08;

    // Outlet product fractions (student's given numbers, relative to TOTAL)
    double g_O2 = 0.08, g_N2 = 0.72, g_CO2 = 0.12, g_SO2 = 0.08;

    // Build augmented matrix for 6 equations and 6 unknowns (6x7 matrix)
    // order of unknowns: [G, F, A1, A2, x, y]
    const int N = 6;
    vector<vector<double>> M(N, vector<double>(N+1, 0.0));

    // Row 0: Sulfur balance -> 0.03*F = 0.08 * TOTAL
    M[0][1] = F_S;               // coefficient for F
    M[0][6-1] = 0.0; // placeholder (we use last column below)
    M[0][N] = g_SO2 * TOTAL;     // RHS

    // Row 1: Carbon balance -> 1*G + 0.6*F + 0.08*A2 = 0.12*TOTAL
    M[1][0] = G_C;
    M[1][1] = F_C;
    M[1][3] = a2_CO2;
    M[1][N] = g_CO2 * TOTAL;

    // Row 2: Nitrogen -> 0.79*A1 + 0.72*A2 = 0.72*TOTAL
    M[2][2] = a1_N2;
    M[2][3] = a2_N2;
    M[2][N] = g_N2 * TOTAL;

    // Row 3: Oxygen -> 0.21*A1 + 0.20*A2 + 0.02*G - 0.08*TOTAL = 1.925*G + 0.7175*F
    // Rearranged: 0.21*A1 + 0.20*A2 + (0.02 - 1.925)*G - 0.7175*F = 0.08*TOTAL
    M[3][2] = a1_O2;
    M[3][3] = a2_O2;
    M[3][0] = G_O2_in - G_stoich_O2;   // (0.02 - 1.925)
    M[3][1] = -F_stoich_O2;
    M[3][N] = g_O2 * TOTAL;

    // Row 4: Water -> y = 1.85*G + 0.175*F  -> -1.85*G -0.175*F + y = 0
    M[4][0] = -G_H2O;
    M[4][1] = -F_H2O;
    M[4][5] = 1.0;
    M[4][N] = 0.0;

    // Row 5: Total -> x + y = TOTAL
    M[5][4] = 1.0;
    M[5][5] = 1.0;
    M[5][N] = TOTAL;

    // Now convert to augmented matrix form for elimination (N x (N+1))
    // (we already placed RHS in M[i][N])

    // Gaussian elimination with partial pivoting
    for (int col = 0; col < N; ++col) {
        // find pivot
        int pivot = col;
        double maxabs = fabs(M[col][col]);
        for (int r = col+1; r < N; ++r) {
            if (fabs(M[r][col]) > maxabs) {
                maxabs = fabs(M[r][col]);
                pivot = r;
            }
        }
        if (maxabs < 1e-12) {
            cerr << "Pivot too small or matrix singular near column " << col << "\n";
            // continue, but solution likely invalid
        }
        if (pivot != col) swap(M[pivot], M[col]);
        double aii = M[col][col];
        if (fabs(aii) < 1e-14) continue;
        for (int c = col; c <= N; ++c) M[col][c] /= aii;
        for (int r = 0; r < N; ++r) {
            if (r == col) continue;
            double factor = M[r][col];
            if (fabs(factor) < 1e-16) continue;
            for (int c = col; c <= N; ++c) {
                M[r][c] -= factor * M[col][c];
            }
        }
    }

    vector<double> v(N, 0.0);
    for (int i = 0; i < N; ++i) v[i] = M[i][N];

    cout.setf(std::ios::fixed); cout<<setprecision(6);
    cout << "Solved variables (order: G, F, A1, A2, x (dry), y (H2O)):\n";
    cout << "G  (fuel gas, gmol/hr) : " << v[0] << "\n";
    cout << "F  (fuel oil, gmol/hr) : " << v[1] << "\n";
    cout << "A1 (air unit1, gmol/hr) : " << v[2] << "\n";
    cout << "A2 (air unit2, gmol/hr) : " << v[3] << "\n";
    cout << "x  (dry flue gas, gmol/hr): " << v[4] << "\n";
    cout << "y  (vapor H2O, gmol/hr)  : " << v[5] << "\n\n";

    // Check negatives
    bool any_neg = false;
    for (int i = 0; i < N; ++i) if (v[i] < -1e-9) any_neg = true;
    if (any_neg) {
        cout << "WARNING: beberapa laju aliran bernilai negatif (fisika tidak mungkin).\n";
        cout << "Ini menunjukkan data/assumption tidak konsisten bila semua neraca dipaksa terpenuhi.\n";
    } else {
        cout << "Semua laju >= 0 (feasible)\n";
    }

    // Compute residuals for each equation: r = A*v - b
    cout << "\nResiduals per equation (A*v - b):\n";
    // Rebuild coefficient matrix for residual calc (non-augmented)
    vector<vector<double>> C(N, vector<double>(N, 0.0));
    vector<double> B(N, 0.0);
    C[0][1] = F_S; B[0] = g_SO2 * TOTAL;
    C[1][0] = G_C; C[1][1] = F_C; C[1][3] = a2_CO2; B[1] = g_CO2*TOTAL;
    C[2][2] = a1_N2; C[2][3] = a2_N2; B[2] = g_N2*TOTAL;
    C[3][2] = 0.21; C[3][3] = 0.20; C[3][0] = G_O2_in - G_stoich_O2; C[3][1] = -F_stoich_O2; B[3] = g_O2*TOTAL;
    C[4][0] = -G_H2O; C[4][1] = -F_H2O; C[4][5] = 1.0; B[4] = 0.0;
    C[5][4] = 1.0; C[5][5] = 1.0; B[5] = TOTAL;

    double norm_res = 0.0;
    for (int i = 0; i < N; ++i) {
        double lhs = 0.0;
        for (int j = 0; j < N; ++j) lhs += C[i][j] * v[j];
        double r = lhs - B[i];
        cout << "Eq " << (i+1) << " residual = " << r << "\n";
        norm_res += r*r;
    }
    cout << "||res||_2 = " << sqrt(norm_res) << "\n\n";

    cout << "Catatan: sesuai hitungan kertas, neraca S memberi F = 56 / 0.03 = 1866.6667 gmol/hr.\n";
    cout << "Kode ini menerapkan SEMUA neraca (S,C,N,O,H2O,total). Karena itu beberapa aliran mungkin negatif.\n";
    cout << "Jika kamu ingin: (a) paksa kedua bahan bakar >0 (constrained solve), atau (b) ubah asumsi (mis. oil massa->mol),\n";
    cout << "aku bisa tambahkan solver constrained / convert mass->mol dan ulangi perhitungan.\n";

    return 0;
}
