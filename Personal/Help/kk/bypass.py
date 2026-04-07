import csv
import pandas as pd
import matplotlib.pyplot as plt

# 1. Baca data yang sudah rapi
with open('data.csv', 'r') as f:
    reader = csv.DictReader(f)
    rows = list(reader)

print(f"Total data points: {len(rows)}")
print(f"Columns: {list(rows[0].keys())}")
print()

# 2. Parse numeric values
data = []
for row in rows:
    entry = {
        'Index': int(row['Index']),
        'Time_s': float(row['Time_s']),
        'Current_A': float(row['Current_A']),
        'Voltage_V': float(row['Voltage_V']),
        'Relay': int(row['Relay']),
        'Voltage_source': int(row['Voltage_source']),
        'Magnetic_flux_Vs': float(row['Magnetic_flux_Vs']),
    }
    # Hitung h dan b
    # h = (Current * Index) + 0.065
    # b = Current / 0.0016
    entry['h'] = (entry['Current_A'] * entry['Index']) + 0.065
    entry['b'] = entry['Current_A'] / 0.0016
    data.append(entry)

# 3. Tampilkan preview
print("Preview (first 20 rows):")
print(f"{'Idx':>4} {'Time':>10} {'Current':>10} {'Voltage':>10} {'Flux':>16} {'h':>12} {'b':>12}")
print("-" * 80)
for d in data[:20]:
    print(f"{d['Index']:>4} "
          f"{d['Time_s']:>10.4f} "
          f"{d['Current_A']:>10.4f} "
          f"{d['Voltage_V']:>10.4f} "
          f"{d['Magnetic_flux_Vs']:>16.8f} "
          f"{d['h']:>12.4f} "
          f"{d['b']:>12.4f}")

print()

# 4. Statistik ringkas
times = [d['Time_s'] for d in data]
currents = [d['Current_A'] for d in data]
voltages = [d['Voltage_V'] for d in data]
fluxes = [d['Magnetic_flux_Vs'] for d in data]
h_vals = [d['h'] for d in data]
b_vals = [d['b'] for d in data]

print("Statistik ringkas:")
print(f"  Time range:    {min(times):.3f} - {max(times):.3f} s")
print(f"  Current range: {min(currents):.4f} - {max(currents):.4f} A")
print(f"  Voltage range: {min(voltages):.4f} - {max(voltages):.4f} V")
print(f"  Flux range:    {min(fluxes):.6f} - {max(fluxes):.6f} Vs")
print(f"  h range:       {min(h_vals):.4f} - {max(h_vals):.4f}")
print(f"  b range:       {min(b_vals):.4f} - {max(b_vals):.4f}")

# 5. Simpan hasil ke CSV baru
output_fields = ['Index', 'Time_s', 'Current_A', 'Voltage_V', 'Relay',
                 'Voltage_source', 'Magnetic_flux_Vs', 'h', 'b']

with open('result.csv', 'w', newline='') as f:
    writer = csv.DictWriter(f, fieldnames=output_fields)
    writer.writeheader()
    writer.writerows(data)

print(f"\nHasil disimpan ke: result.csv ({len(data)} rows)")

df = pd.read_csv('result.csv')
fig, axs = plt.subplots(2, 2, figsize=(12, 10))

# Magnetization curve
axs[0, 0].scatter(df['h'], df['b'], color='blue', s=10, alpha=0.6)
axs[0, 0].set_title('Hubungan H dan B')
axs[0, 0].set_xlabel('H')
axs[0, 0].set_ylabel('B')
axs[0, 0].grid(True, linestyle='--', alpha=0.7)

# Current to time
axs[0, 1].plot(df['Time_s'], df['Current_A'], color='red')
axs[0, 1].set_title('Arus (Current) vs Waktu')
axs[0, 1].set_xlabel('Time (s)')
axs[0, 1].set_ylabel('Current (A)')
axs[0, 1].grid(True, linestyle='--', alpha=0.7)

# Voltage to time
axs[1, 0].plot(df['Time_s'], df['Voltage_V'], color='green')
axs[1, 0].set_title('Tegangan (Voltage) vs Waktu')
axs[1, 0].set_xlabel('Time (s)')
axs[1, 0].set_ylabel('Voltage (V)')
axs[1, 0].grid(True, linestyle='--', alpha=0.7)

# Flux to time
axs[1, 1].plot(df['Time_s'], df['Magnetic_flux_Vs'], color='purple')
axs[1, 1].set_title('Fluks Magnetik vs Waktu')
axs[1, 1].set_xlabel('Time (s)')
axs[1, 1].set_ylabel('Magnetic Flux (Vs)')
axs[1, 1].grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.show()