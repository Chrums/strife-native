#include "Messenger.h"

using namespace Strife::Core;
using namespace std;

void Messenger::emit(const Message& message) {
    const type_index type = type_index(typeid(message));
    emit(type, message);
}

void Messenger::emit(const type_index type, const Message& message) {
    std::vector<Callback<Message>> callbacks = callbacks_[type];
    for (Callback<Message> callback : callbacks) {
        callback(message);
    }
}