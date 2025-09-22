// 1. Definisikan data merk untuk setiap jenis produk
const dataMerk = {
    Desktop: ["Dell", "HP", "Asus ROG", "Lenovo"],
    Laptop: ["Macbook", "Asus", "HP", "Dell", "Lenovo"],
    Smartphone: ["iPhone", "Samsung", "Xiaomi", "Google Pixel", "Oppo"]
};

// 2. Ambil elemen dropdown dari HTML
const jenisProdukDropdown = document.getElementById('jenisProduk');
const merkProdukDropdown = document.getElementById('merkProduk');

// 3. Tambahkan event listener 'change' ke dropdown pertama
jenisProdukDropdown.addEventListener('change', function() {
    // Ambil nilai (value) dari jenis produk yang dipilih
    const selectedJenis = this.value;

    // Kosongkan dropdown merk terlebih dahulu
    merkProdukDropdown.innerHTML = '<option value="">Pilih Merk</option>';

    // Periksa apakah user memilih jenis produk yang valid (bukan yang "Pilih Jenis Produk")
    if (selectedJenis) {
        // Aktifkan dropdown merk
        merkProdukDropdown.disabled = false;

        // Ambil array merk yang sesuai dari objek dataMerk
        const merks = dataMerk[selectedJenis];

        // Isi dropdown merk dengan opsi yang sesuai menggunakan loop
        merks.forEach(function(merk) {
            const option = document.createElement('option');
            option.value = merk;
            option.textContent = merk;
            merkProdukDropdown.appendChild(option);
        });

    } else {
        // Jika user kembali memilih "Pilih Jenis Produk", nonaktifkan dropdown merk
        merkProdukDropdown.disabled = true;
    }
});