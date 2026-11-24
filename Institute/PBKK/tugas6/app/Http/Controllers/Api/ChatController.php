<?php

namespace App\Http\Controllers\Api;

use App\Http\Controllers\Controller;
use App\Models\Conversation;
use App\Models\User;
use App\Services\ChatService;
use Illuminate\Http\JsonResponse;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Hash;
use Illuminate\Support\Str;
use Illuminate\Validation\ValidationException;

class ChatController extends Controller
{
    public function token(Request $request): JsonResponse
    {
        $data = $request->validate([
            'email' => 'required|email',
            'password' => 'required|string',
        ]);
        $user = User::where('email', $data['email'])->first();
        if (! $user || ! Hash::check($data['password'], $user->password)) {
            throw ValidationException::withMessages(['email' => 'Email atau password salah.']);
        }

        return response()->json([
            'token' => $user->createToken('chat-api', ['chat'], now()->addDay())->plainTextToken,
        ]);
    }

    public function store(Request $request, ChatService $chat): JsonResponse
    {
        $data = $request->validate([
            'prompt' => 'required|string|min:3|max:1000',
            'conversation_id' => 'nullable|integer|min:1',
        ]);
        $conversation = isset($data['conversation_id'])
            ? Conversation::where('user_id', $request->user()->id)->findOrFail($data['conversation_id'])
            : Conversation::create(['user_id' => $request->user()->id, 'title' => Str::limit($data['prompt'], 70)]);

        $message = $chat->reply($request->user(), $conversation->id, $data['prompt']);

        return response()->json(['conversation_id' => $conversation->id, 'message' => $message], 201);
    }
}
