// JavaScript untuk logika pencarian
document.getElementById('form-kodepos').addEventListener('submit', function(event) {
    // Mencegah form dari refresh halaman
    event.preventDefault(); 

    // Ambil nilai dari setiap input
    const provinsi = document.getElementById('provinsi').value;
    const kabupaten = document.getElementById('kabupaten-kota').value;
    const kecamatan = document.getElementById('kecamatan').value;

    // Elemen untuk menampilkan hasil dan loading
    const outputDiv = document.getElementById('output');
    const loadingDiv = document.getElementById('loading');
    
    // Kosongkan hasil sebelumnya dan tampilkan loading
    outputDiv.innerHTML = '';
    loadingDiv.style.display = 'block';

    // Buat query pencarian dari input yang diisi
    const query = `${kecamatan} ${kabupaten} ${provinsi}`.trim();
    
    // Panggil API menggunakan fetch
    fetch(`https://kodepos.vercel.app/search?q=${encodeURIComponent(query)}`)
        .then(response => response.json())
        .then(data => {
            loadingDiv.style.display = 'none'; // Sembunyikan loading
            
            if (data.success && data.data.length > 0) {
                // Jika data ditemukan, tampilkan
                data.data.forEach(item => {
                    const hasilItem = `
                        <div class="hasil-item">
                            <strong>${item.postalcode}</strong><br>
                            ${item.urban}, ${item.subdistrict}, <br>
                            ${item.city}, ${item.province}
                        </div>
                    `;
                    outputDiv.innerHTML += hasilItem;
                });
            } else {
                // Jika tidak ditemukan
                outputDiv.innerHTML = '<p>Kode pos tidak ditemukan.</p>';
            }
        })
        .catch(error => {
            // Jika terjadi error saat fetch
            loadingDiv.style.display = 'none';
            console.error('Error:', error);
            outputDiv.innerHTML = '<p>Terjadi kesalahan saat mengambil data.</p>';
        });
});