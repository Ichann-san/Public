{{-- Field input untuk halaman autentikasi AdminLTE. --}}
<div class="input-group mb-3">
    <input type="{{ $type ?? 'text' }}" name="{{ $name }}" id="{{ $name }}"
        class="form-control @error($name) is-invalid @enderror"
        value="{{ ($type ?? 'text') === 'password' ? '' : old($name, $value ?? '') }}"
        placeholder="{{ $placeholder }}" {{ ($autofocus ?? false) ? 'autofocus' : '' }}
        @isset($autocomplete) autocomplete="{{ $autocomplete }}" @endisset>
    <div class="input-group-text"><span class="bi {{ $icon }}"></span></div>
    @error($name)
        <span class="invalid-feedback" role="alert"><strong>{{ $message }}</strong></span>
    @enderror
</div>
