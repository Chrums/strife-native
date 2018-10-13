#include "Dispatcher.h"

using namespace Strife::Core;
using namespace std;

const unsigned int Dispatcher::Synchronous = 0;

void Dispatcher::emit(const type_index type, const unsigned int priority, Event* const event) {
	if (priority == Dispatcher::Synchronous) {
		dispatch(type, event);
	} else {
		events_[type].push(event);
	}
}

void Dispatcher::dispatch() {
	for (auto& [ priority, types ] : priorities_) {
		for (auto& type : types) {
			dispatch(type);
		}
	}
}

void Dispatcher::dispatch(const type_index type) {
	auto& events = events_[type];
	size_t length = events.size();
	for (size_t i = 0; i < length; i++) {
		Event* const event = events.front();
		events.pop();
		dispatch(type, event);
	}
}

void Dispatcher::dispatch(const type_index type, Event* const event) {
	messenger.emit(type, *event);
	delete event;
}