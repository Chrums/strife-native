#include <iostream>
#include "Component.h"
#include "Entity.h"
#include "Scene.h"
#include "Storage.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

class Test : public Component {
    using Component::Component;
};

int main(int argc, char const *argv[]) {
    Scene s;
    s.initialize<Test>();
    Entity e0 = s.entities.add();
    e0.components.add<Test>();
    Entity e1 = s.entities.add();
    e1.components.add<Test>();
    Storage<Test>& tests = static_cast<Storage<Test>&>(s.components.get<Test>());
    for (auto pair : tests) {
        cout << pair.second.id << endl;
    }
}