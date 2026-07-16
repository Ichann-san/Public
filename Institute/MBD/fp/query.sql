ALTER TABLE pesanan ADD COLUMN discount NUMERIC(12, 2) DEFAULT 0;
ALTER TABLE pesanan ADD COLUMN total_akhir NUMERIC(12, 2) DEFAULT 0;

CREATE OR REPLACE FUNCTION hitung_discount_total()
RETURNS TRIGGER AS
$$
DECLARE
    total_jumlah INTEGER;
BEGIN
    -- Hitung total jumlah produk dalam pesanan
    SELECT COALESCE(SUM(jumlah), 0)
    INTO total
    FROM detail_pesanan
    WHERE id_pesanan = NEW.id_pesanan;

    -- Update tabel pesanan
    UPDATE pesanan
    SET
        discount = total * 20,
        total_akhir = total_harga - (total * 20)
    WHERE id_pesanan = NEW.id_pesanan;

    RETURN NEW;
END;
$$
LANGUAGE plpgsql;