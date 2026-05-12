-- Active: 1763821327986@@127.0.0.1@5432@prak2mbd
-- 1. DDL: CREATE TABLES


CREATE TABLE PENULIS (
    penulis_id VARCHAR(5) PRIMARY KEY,
    nama_penulis VARCHAR(100) NOT NULL
);

CREATE TABLE BUKU (
    kode_buku VARCHAR(10) PRIMARY KEY,
    penulis_id VARCHAR(5),
    judul_buku VARCHAR(150) NOT NULL,
    tahun_terbit INT,
    harga NUMERIC(10, 2) NOT NULL,
    stok INT NOT NULL,
    FOREIGN KEY (penulis_id) REFERENCES PENULIS(penulis_id) ON DELETE CASCADE
);

CREATE TABLE PENJUALAN (
    no_nota VARCHAR(10) PRIMARY KEY,
    nama_pelanggan VARCHAR(100) NOT NULL,
    tanggal_penjualan DATE NOT NULL
);

CREATE TABLE DETAIL_PENJUALAN (
    detail_id VARCHAR(10) PRIMARY KEY,
    kode_buku VARCHAR(10),
    no_nota VARCHAR(10),
    jumlah_beli INT NOT NULL,
    total_harga NUMERIC(12, 2) NOT NULL,
    FOREIGN KEY (kode_buku) REFERENCES BUKU(kode_buku) ON DELETE CASCADE,
    FOREIGN KEY (no_nota) REFERENCES PENJUALAN(no_nota) ON DELETE CASCADE
);


-- 2. DML: INSERT DATA

INSERT INTO PENULIS (penulis_id, nama_penulis) VALUES
('P01', 'Andrea Hirata'),
('P02', 'Raditya Dika'),
('P03', 'Tere Liye'),
('P04', 'Dee Lestari');

INSERT INTO BUKU (kode_buku, penulis_id, judul_buku, tahun_terbit, harga, stok) VALUES
('BK-01', 'P01', 'Laskar Pelangi', 2005, 85000.00, 25),
('BK-02', 'P01', 'Sang Pemimpi', 2006, 75000.00, 12),
('BK-03', 'P02', 'Cinta Brontosaurus', 2006, 65000.00, 18),
('BK-04', 'P03', 'Bumi', 2014, 95000.00, 30),
('BK-05', 'P04', 'Perahu Kertas', 2009, 65000.00, 20);

INSERT INTO PENJUALAN (no_nota, nama_pelanggan, tanggal_penjualan) VALUES
('NOTA-001', 'Andi Pratama', '2024-04-10'),
('NOTA-002', 'Siti Rahmawati', '2024-04-15'),
('NOTA-003', 'Budi Santoso', '2024-05-02'),
('NOTA-004', 'Diana Putri', '2024-05-10');

INSERT INTO DETAIL_PENJUALAN (detail_id, kode_buku, no_nota, jumlah_beli, total_harga) VALUES
('DTL-001', 'BK-01', 'NOTA-001', 2, 170000.00),
('DTL-002', 'BK-02', 'NOTA-001', 1, 75000.00),
('DTL-003', 'BK-05', 'NOTA-001', 1, 65000.00),
('DTL-004', 'BK-03', 'NOTA-002', 1, 65000.00),
('DTL-005', 'BK-02', 'NOTA-002', 1, 75000.00),
('DTL-006', 'BK-04', 'NOTA-003', 5, 475000.00),
('DTL-007', 'BK-01', 'NOTA-003', 2, 170000.00),
('DTL-008', 'BK-04', 'NOTA-004', 5, 475000.00),
('DTL-009', 'BK-03', 'NOTA-004', 2, 130000.00);

-- No. 1
CREATE OR REPLACE VIEW INFO_STOK_BUKU AS
SELECT
    p.nama_penulis,
    b.judul_buku,
    b.tahun_terbit,
    b.stok
FROM BUKU b
JOIN PENULIS p ON b.penulis_id = p.penulis_id
WHERE b.stok > 20
ORDER BY p.nama_penulis;
-- Test : SELECT * FROM INFO_STOK_BUKU;


-- No. 2
CREATE OR REPLACE VIEW REKAP_PENDAPATAN AS
SELECT
    EXTRACT(MONTH FROM pj.tanggal_penjualan)::INT AS bulan_penjualan,
    EXTRACT(YEAR FROM pj.tanggal_penjualan)::INT AS tahun_penjualan,
    SUM(dp.total_harga) AS total_pendapatan
FROM DETAIL_PENJUALAN dp
JOIN PENJUALAN pj ON dp.no_nota = pj.no_nota
GROUP BY
    EXTRACT(MONTH FROM pj.tanggal_penjualan),
    EXTRACT(YEAR FROM pj.tanggal_penjualan)
ORDER BY bulan_penjualan, tahun_penjualan;
-- Test : SELECT * FROM REKAP_PENDAPATAN;


-- No. 3
CREATE TABLE LOG_BUKU (
    log_id SERIAL PRIMARY KEY,
    aktivitas VARCHAR(100),
    kode_buku VARCHAR(10),
    waktu_eksekusi TIMESTAMP DEFAULT now()
);

-- Trigger
CREATE OR REPLACE FUNCTION fn_log_buku()
RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' THEN
        INSERT INTO LOG_BUKU (aktivitas, kode_buku)
        VALUES ('Menambah Data Buku', NEW.kode_buku);
        RETURN NEW;
    ELSIF TG_OP = 'UPDATE' THEN
        INSERT INTO LOG_BUKU (aktivitas, kode_buku)
        VALUES ('Mengubah Data Buku', NEW.kode_buku);
        RETURN NEW;
    ELSIF TG_OP = 'DELETE' THEN
        INSERT INTO LOG_BUKU (aktivitas, kode_buku)
        VALUES ('Menghapus Data Buku', OLD.kode_buku);
        RETURN OLD;
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

-- Trigger
CREATE TRIGGER trg_log_buku
AFTER INSERT OR UPDATE OR DELETE ON BUKU
FOR EACH ROW
EXECUTE FUNCTION fn_log_buku();
-- Test(run semua)
INSERT INTO BUKU (kode_buku, penulis_id, judul_buku, tahun_terbit, harga, stok) VALUES ('BK-99', 'P01', 'Edensor', 2007, 70000.00, 15);
UPDATE BUKU SET judul_buku = 'Edensor Edisi Revisi' WHERE kode_buku = 'BK-99';
DELETE FROM BUKU WHERE kode_buku = 'BK-99';
SELECT * FROM LOG_BUKU;

-- No. 4
CREATE OR REPLACE FUNCTION fn_kurangi_stok()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE BUKU
    SET stok = stok - NEW.jumlah_beli
    WHERE kode_buku = NEW.kode_buku;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_kurangi_stok
AFTER INSERT ON DETAIL_PENJUALAN
FOR EACH ROW
EXECUTE FUNCTION fn_kurangi_stok();
-- Test(run semua)
INSERT INTO PENJUALAN (no_nota, nama_pelanggan, tanggal_penjualan) VALUES ('NOTA-005', 'Eko Susanto', '2024-05-15');
INSERT INTO DETAIL_PENJUALAN (detail_id, kode_buku, no_nota, jumlah_beli, total_harga) VALUES ('DTL-010', 'BK-01', 'NOTA-005', 3, 255000);
INSERT INTO DETAIL_PENJUALAN (detail_id, kode_buku, no_nota, jumlah_beli, total_harga) VALUES ('DTL-011', 'BK-05', 'NOTA-005', 2, 130000);
SELECT kode_buku, judul_buku, stok FROM BUKU WHERE kode_buku IN ('BK-01', 'BK-05');

-- No. 5
CREATE OR REPLACE FUNCTION CARI_KARYA_PENULIS(p_nama_penulis VARCHAR)
RETURNS TEXT AS $$
DECLARE
    hasil TEXT := '';
    rec RECORD;
BEGIN
    FOR rec IN
        SELECT b.judul_buku
        FROM BUKU b
        JOIN PENULIS p ON b.penulis_id = p.penulis_id
        WHERE p.nama_penulis = p_nama_penulis
    LOOP
        IF hasil = '' THEN
            hasil := rec.judul_buku;
        ELSE
            hasil := hasil || ' | ' || rec.judul_buku;
        END IF;
    END LOOP;
    RETURN hasil;
END;
$$ LANGUAGE plpgsql;
-- Test(run semua)
SELECT CARI_KARYA_PENULIS('Andrea Hirata');
SELECT CARI_KARYA_PENULIS('Raditya Dika');
