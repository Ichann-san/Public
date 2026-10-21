@props(['tone' => 'info'])

<div {{ $attributes->class(['status-banner', 'status-success' => $tone === 'success']) }} role="status">
    <span class="status-icon" aria-hidden="true">{{ $tone === 'success' ? '✓' : '✦' }}</span>
    <div>{{ $slot }}</div>
</div>
