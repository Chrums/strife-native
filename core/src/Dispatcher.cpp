#include "Dispatcher.h"

#include <limits>

using namespace Strife::Core;
using namespace std;

const Dispatcher::Priority Dispatcher::Synchronous = 0;
const Dispatcher::Priority Dispatcher::Final = numeric_limits<Dispatcher::Priority>::max();

void Dispatcher::dispatch() {
    for (auto [priority, types] : priorities_) {
        for (const type_index type : types) {
            dispatch(type);
        }
    }
}

void Dispatcher::dispatch(const type_index type) {
    std::queue<Message* const> messages = messages_[type];
    size_t length = messages.size();
    for (size_t count = 0; count < length; ++count) {
        Message* const message = messages.front();
        messages.pop();
        dispatch(message);
    }
}

void Dispatcher::dispatch(Message* const message) {
    messenger_.emit(*message);
    delete message;
}