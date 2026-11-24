{{-- Tombol hapus: hanya dirender jika pengguna memiliki izin hapus. --}}
@can($permission)
    <form action="{{ $action }}" method="POST" class="d-inline"
        onsubmit="return confirm('Yakin ingin menghapus {{ addslashes($label) }}?');">
        @csrf
        @method('DELETE')
        <button type="submit" class="btn btn-sm btn-danger" title="Hapus">
            <i class="bi bi-trash"></i> Hapus
        </button>
    </form>
@endcan
