#include "Messenger.h"

using namespace Strife::Core;
using namespace std;

void Messenger::emit(const Message& message) {
	const std::type_index type = std::type_index(typeid(message));
	emit(type, message);
}

void Messenger::emit(const type_index type, const Message& message) {
	auto& callbacks = callbacks_[type];
	for (auto& callback : callbacks) {
		callback(message);
	}
}