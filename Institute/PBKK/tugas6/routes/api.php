<?php

use App\Http\Controllers\Api\ChatController;
use App\Models\Conversation;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;

Route::post('/token', [ChatController::class, 'token'])->middleware('throttle:5,1');

Route::middleware(['auth:sanctum', 'throttle:20,1'])->group(function () {
    Route::post('/chat', [ChatController::class, 'store']);
    Route::get('/conversations/{id}/messages', function (Request $request, int $id) {
        return Conversation::where('user_id', $request->user()->id)->findOrFail($id)
            ->messages()->orderBy('id')->paginate(100);
    });
    Route::delete('/token', function (Request $request) {
        $request->user()->currentAccessToken()->delete();

        return response()->noContent();
    });
});
