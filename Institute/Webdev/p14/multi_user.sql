CREATE TABLE `user` (
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `nama` VARCHAR(255) NOT NULL,
    `username` VARCHAR(255) NOT NULL,
    `password` VARCHAR(255) NOT NULL,
    `level` VARCHAR(255) NOT NULL,
    PRIMARY KEY (`id`)
);

-- default user

INSERT INTO `user` (`nama`, `username`, `password`, `level`) VALUES
('Administrator Utama', 'admin', 'adminpass', 'admin'),
('Pegawai Toko', 'pegawai', 'pegawaipass', 'pegawai'),
('Pengurus Gudang', 'pengurus', 'penguruspass', 'pengurus');
