<?php

return [
    'demo' => (bool) env('LLM_DEMO', false),
    'url' => env('LLM_URL', 'http://127.0.0.1:11434/api/chat'),
    'model' => env('LLM_MODEL', 'qwen3:14b'),
    'key' => env('LLM_API_KEY'),
    'timeout' => (int) env('LLM_TIMEOUT', 60),
];
