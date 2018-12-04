#include "Dispatcher.h"

#include <limits>

using namespace Strife::Core;
using namespace std;

const unsigned int Dispatcher::Synchronous = 0;
const unsigned int Dispatcher::Final = numeric_limits<unsigned int>::max();

void Dispatcher::dispatch() {
    for (auto [priority, types] : priorities_) {
        for (const type_index type : types) {
            dispatch(type);
        }
    }
}

void Dispatcher::dispatch(const type_index type) {
    std::queue<Event* const> events = events_[type];
    size_t length = events.size();
    for (size_t count = 0; count < length; ++count) {
        Event* const event = events.front();
        events.pop();
        dispatch(type, event);
    }
}

void Dispatcher::dispatch(const type_index type, Event* const event) {
    messenger_.emit(type, *event);
    delete event;
}

void Dispatcher::emit(const type_index type, const unsigned int priority, Event* const event) {
    if (priority == Dispatcher::Synchronous) {
        dispatch(type, event);
    } else {
        priorities_[priority].insert(type);
        events_[type].push(event);
    }
}