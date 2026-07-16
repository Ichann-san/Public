ALTER TABLE pengguna
ADD COLUMN total_point NUMERIC(12,2) DEFAULT 0;

CREATE OR REPLACE FUNCTION add_point_jl_teknik()
RETURNS TRIGGER AS $$
DECLARE
    v_alamat VARCHAR(100);
    v_id_pembeli CHAR(7);
    v_bulan_pesan INT;
    v_bonus_point NUMERIC(12,2);
BEGIN
    -- alamat
    SELECT k.alamat INTO v_alamat
    FROM produk pr
    JOIN kantin k ON pr.id_kantin = k.id_kantin
    WHERE pr.id_produk = NEW.id_produk;

    IF v_alamat LIKE '%Jl. Teknik%' THEN
        SELECT id_pengguna, EXTRACT(MONTH FROM timestamp)
        INTO v_id_pembeli, v_bulan_pesan
        FROM pesanan
        WHERE id_pesanan = NEW.id_pesanan;
        v_bonus_point := v_bulan_pesan * 0.20;

        UPDATE pengguna
        SET total_point = total_point + v_bonus_point
        WHERE id_pengguna = v_id_pembeli AND peran = 'PEMBELI';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_add_point_jl_teknik
AFTER INSERT ON detail_pesanan
FOR EACH ROW
EXECUTE FUNCTION add_point_jl_teknik();

CREATE ROLE Penjual;

GRANT INSERT ON pesanan TO Penjual;
GRANT INSERT ON detail_pesanan TO Penjual;
GRANT SELECT ON produk TO Penjual;
GRANT SELECT ON kantin TO Penjual;
GRANT SELECT ON pesanan TO Penjual;
GRANT UPDATE (total_point) ON pengguna TO Penjual;
GRANT EXECUTE ON FUNCTION add_point_jl_teknik() TO Penjual;

SET ROLE Penjual;

SELECT id_pengguna, nama, total_point 
FROM pengguna 
WHERE id_pengguna = 'PGN0021';

INSERT INTO pesanan (id_pesanan, "timestamp", total_harga, status, id_pengguna)
VALUES ('PES0999', '2026-06-24 14:00:00', 15000, 'Selesai', 'PGN0021');
INSERT INTO detail_pesanan (id_pesanan, id_produk, jumlah, subtotal)
VALUES ('PES0999', 'PRD0027', 1, 15000);

RESET ROLE;