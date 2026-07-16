ALTER TABLE pesanan
    ADD COLUMN discount NUMERIC(12,2) NOT NULL DEFAULT 0,
    ADD COLUMN total_akhir NUMERIC(12,2) NOT NULL DEFAULT 0;


CREATE OR REPLACE FUNCTION fn_hitung_discount_total()
RETURNS TRIGGER AS $$
DECLARE
    v_peran VARCHAR;
    v_total_jumlah INTEGER;
BEGIN
    SELECT peran INTO v_peran
    FROM pengguna
    WHERE id_pengguna = current_setting('app.current_user_id');

    IF v_peran IS DISTINCT FROM 'penjual' THEN
        RAISE EXCEPTION 'Akses ditolak: hanya penjual yang boleh mengubah detail_pesanan';
    END IF;

    SELECT SUM(jumlah) INTO v_total_jumlah
    FROM detail_pesanan
    WHERE id_pesanan = NEW.id_pesanan;

    UPDATE pesanan
    SET discount = 20 * v_total_jumlah,
        total_akhir = total_harga - (20 * v_total_jumlah)
    WHERE id_pesanan = NEW.id_pesanan;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- 3. Trigger
CREATE TRIGGER trg_hitung_discount_total
AFTER INSERT OR UPDATE ON detail_pesanan
FOR EACH ROW
EXECUTE FUNCTION fn_hitung_discount_total();

SET app.current_user_id = 'PGN0006';
INSERT INTO detail_pesanan (id_pesanan, id_produk, jumlah, subtotal) VALUES
    ('PES0001', 'PRD0001', 3, 45000.00);
SELECT id_pesanan, total_harga, discount, total_akhir FROM pesanan WHERE id_pesanan = 'PES0001';

-- cek no telp genap
SELECT id_pengguna, no_telp, \
    CASE WHEN CAST(RIGHT(no_telp, 1) AS INTEGER) % 2 = 0 THEN 'true'ELSE 'false'
    END AS status_no_telp
FROM pengguna;

SELECT dp.id_produk from detail_pesanan 

SELECT 
    dp.id_pesanan,
    dp.id_produk,
    dp.jumlah,
    p.discount,
    p.total_akhir,
    p.total_harga
FROM detail_pesanan dp
JOIN pesanan p ON dp.id_pesanan = p.id_pesanan
ORDER BY dp.id_pesanan;

SELECT 
    pg.id_pengguna,
    pg.no_telp,
    dp.id_produk,
    dp.jumlah,
    CASE WHEN CAST(RIGHT(pg.no_telp, 1) AS INTEGER) % 2 = 0 THEN 'true' ELSE 'false'
    END AS status_no_telp
FROM pengguna pg
JOIN pesanan p ON pg.id_pengguna = p.id_pengguna
JOIN detail_pesanan dp ON p.id_pesanan = dp.id_pesanan
WHERE dp.id_produk = 'PRD0001';