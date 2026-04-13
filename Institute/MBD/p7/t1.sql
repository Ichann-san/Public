-- Active: 1761461509284@@127.0.0.1@3306@pertemuan7
-- Active: 1761461509284@@127.0.0.1@3306@pertemuan6
CREATE DATABASE pertemuan7;

-- ddl dml
CREATE TABLE DataPasien (
    IDPasien VARCHAR(10) PRIMARY KEY,
    NoKtp VARCHAR(20),
    Nama_Pasien VARCHAR(50)
);

CREATE TABLE Dokter (
    NID VARCHAR(10) PRIMARY KEY,
    KodePoli VARCHAR(10),
    Nama VARCHAR(50)
);

CREATE TABLE Poli (
    KodePoli VARCHAR(10) PRIMARY KEY,
    NamaPoli VARCHAR(50)
);

CREATE TABLE Pemeriksaan (
    IDPeriksa VARCHAR(10) PRIMARY KEY,
    NID VARCHAR(10),
    IDPasien VARCHAR(10),
    TglPeriksa VARCHAR(20),
    Diagnosa VARCHAR(50)
);

-- data insert
INSERT INTO DataPasien VALUES
('PS00006', '3507254111940001', 'Lidra Trifidya'),
('PS00007', '3606125204940003', 'Yutika Amelia Effendi');

INSERT INTO Dokter VALUES
('D009', 'P01', 'Dr. Budikusnaedi'),
('D010', 'P02', 'Dr. Hariyanto Kusuma'),
('D011', 'P02', 'Dr. Sri Herianti'),
('D012', 'P03', 'Drg. Elvin Purwantari');

INSERT INTO Poli VALUES
('P01', 'Bedah Umum'),
('P02', 'Mulut'),
('P03', 'THT');

INSERT INTO Pemeriksaan VALUES
('C001', 'D009', 'PS00006', '01-Jan-15', 'Radang Usus Buntu'),
('C002', 'D010', 'PS00007', '02-Jan-15', 'Gigi Berlubang'),
('C003', 'D011', 'PS00007', '10-Feb-15', 'Flu'),
('C004', 'D009', 'PS00007', '02-May-15', 'Radang Usus Buntu');

-- abstract table
CREATE TABLE R (A INT, B INT);
CREATE TABLE S (B INT, C INT);
CREATE TABLE R2 (B INT, C INT);

-- table data
INSERT INTO R VALUES (1, 2), (5, 6), (1, 2);
INSERT INTO S VALUES (3, 4), (7, 8);
INSERT INTO R2 VALUES (5, 6), (7, 8), (9, 10);

SELECT IDPasien, TglPeriksa FROM Pemeriksaan
WHERE Diagnosa = 'Gigi Berlubang' OR Diagnosa = 'Flu';

SELECT dp.NoKtp, dp.Nama_Pasien FROM DataPasien dp
JOIN Pemeriksaan p ON dp.IDPasien = p.IDPasien
WHERE p.TglPeriksa LIKE '%May%';

SELECT  dp.Nama_Pasien, d.Nama AS Nama_Dokter, pl.NamaPoli, p.TglPeriksa FROM Pemeriksaan p
JOIN DataPasien dp ON p.IDPasien = dp.IDPasien
JOIN Dokter d ON p.NID = d.NID
JOIN Poli pl ON d.KodePoli = pl.KodePoli
WHERE d.Nama = 'Dr. Budikusnaedi';

SELECT DISTINCT A, B FROM R WHERE (A * B) > 5;

SELECT DISTINCT C FROM R2;

SELECT DISTINCT R.A, R.B, S.B AS S_B, S.C FROM R CROSS JOIN S;

SELECT DISTINCT R.A, R.B, R2.B AS R2_B, R2.C FROM R
JOIN R2 ON R.B < R2.C;

SELECT DISTINCT S.C FROM R
NATURAL JOIN R2
NATURAL JOIN S;