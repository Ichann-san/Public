@props(['label'])

<div {{ $attributes->class(['info-card']) }}>
    <span class="info-label">{{ $label }}</span>
    <div class="info-value">{{ $slot }}</div>
</div>
