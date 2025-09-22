document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('registration-form');
    const namaInput = document.getElementById('nama');
    const suggestionsContainer = document.getElementById('nama-suggestions');
    const statusMessage = document.getElementById('status-message');
    const daftarNamaMahasiswa = [
        "Andi Pratama", "Budi Santoso", "Citra Lestari", "Dewi Anggraini", "Eka Wijaya",
        "Fajar Nugroho", "Gita Permata", "Hadi Kusuma", "Indah Puspita", "Joko Susilo"
    ];

    namaInput.addEventListener('input', function() {
        const inputText = this.value.toLowerCase();
        suggestionsContainer.innerHTML = '';

        if (inputText.length === 0) {
            suggestionsContainer.classList.add('hidden');
            return;
        }

        const filteredNames = daftarNamaMahasiswa.filter(name => name.toLowerCase().includes(inputText));

        if (filteredNames.length > 0) {
            suggestionsContainer.classList.remove('hidden');
            filteredNames.forEach(name => {
                const suggestionItem = document.createElement('div');
                suggestionItem.textContent = name;
                suggestionItem.className = 'p-3 cursor-pointer suggestion-item transition duration-150';
                suggestionItem.addEventListener('click', function() {
                    namaInput.value = name;
                    suggestionsContainer.innerHTML = '';
                    suggestionsContainer.classList.add('hidden');
                });
                suggestionsContainer.appendChild(suggestionItem);
            });
        } else {
            suggestionsContainer.classList.add('hidden');
        }
    });
    document.addEventListener('click', function(e) {
        if (!namaInput.contains(e.target) && !suggestionsContainer.contains(e.target)) {
            suggestionsContainer.classList.add('hidden');
        }
    });

    form.addEventListener('submit', function(event) {
        event.preventDefault();
        clearAllErrors();
        statusMessage.innerHTML = '';
        let isValid = true;
        const fieldsToValidate = ['nama', 'nim', 'matkul', 'dosen'];

        fieldsToValidate.forEach(fieldId => {
            const input = document.getElementById(fieldId);
            const errorContainer = document.getElementById(`${fieldId}-error`);
            const fieldName = input.previousElementSibling.textContent;

            if (input.value.trim() === '') {
                errorContainer.textContent = `${fieldName} tidak boleh kosong.`;
                input.classList.add('border-red-500');
                isValid = false;
            } else {
                input.classList.remove('border-red-500');
            }
        });


        if (isValid) {
            statusMessage.innerHTML = `<div class="bg-green-100 border border-green-400 text-green-700 px-4 py-3 rounded-lg" role="alert">
                <strong class="font-bold">Sukses!</strong>
                <span class="block sm:inline"> Data berhasil didaftarkan.</span>
            </div>`;
            
            form.reset();
        } else {
             statusMessage.innerHTML = `<div class="bg-red-100 border border-red-400 text-red-700 px-4 py-3 rounded-lg" role="alert">
                <strong class="font-bold">Gagal!</strong>
                <span class="block sm:inline"> Harap periksa kembali data isian Anda.</span>
            </div>`;
        }
    });

    function clearAllErrors() {
        const errorMessages = document.querySelectorAll('.error-message');
        errorMessages.forEach(msg => msg.textContent = '');
         const inputsWithErrors = document.querySelectorAll('.border-red-500');
        inputsWithErrors.forEach(input => input.classList.remove('border-red-500'));
    }
});
