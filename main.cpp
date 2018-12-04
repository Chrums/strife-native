#include <iostream>
#include "Component.h"
#include "Entity.h"
#include "Message.h"
#include "Messenger.h"
#include "Scene.h"
#include "Storage.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

class TestComponent : public Component {
    using Component::Component;
};

class TestMessage : public Message {
    using Message::Message;
};

int main(int argc, char const *argv[]) {
    Scene s;
    s.initialize<TestComponent>();
    Messenger m;
    m.on<TestMessage>(
        [](const TestMessage& tm) { 
            cout << "Hello, world!" << endl;
        }
    );
    TestMessage tm;
    m.emit(tm);
}