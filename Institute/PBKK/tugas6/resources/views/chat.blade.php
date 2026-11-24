@extends('layouts.app')
@section('title', 'Workspace AI')

@section('content')
    <div class="workspace">
        <livewire:conversation-list />
        <livewire:chat-panel />
    </div>
@endsection
