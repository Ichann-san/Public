@extends('adminlte::errors.error-page', [
    'errorCode' => '403',
    'errorTheme' => 'warning',
    'errorTitle' => 'Akses Ditolak',
    'errorMessage' => 'Anda tidak memiliki hak akses (peran/izin) untuk membuka halaman ini.',
])
