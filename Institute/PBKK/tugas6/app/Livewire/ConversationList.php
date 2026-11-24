<?php

namespace App\Livewire;

use App\Models\Conversation;
use Illuminate\View\View;
use Livewire\Attributes\On;
use Livewire\Component;

class ConversationList extends Component
{
    public function boot(): void
    {
        abort_unless(auth()->check(), 401);
    }

    #[On('conversations-changed')]
    public function refreshConversations(): void
    {
    }

    public function render(): View
    {
        return view('livewire.conversation-list', [
            'conversations' => Conversation::where('user_id', auth()->id())
                ->latest('updated_at')->latest('id')->limit(50)->get(),
        ]);
    }
}
