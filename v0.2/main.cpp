#include <iostream>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Component.h"
#include "Entity.h"
#include "Scene.h"
#include "Storage.h"

using namespace Strife;
using namespace std;
using nlohmann::json;

int main() {
    
    Scene* s0 = new Scene();
    s0->entities.add();
    s0->entities.add();
    s0->entities.add();
    
    json data = s0->serialize();
    Scene* s1 = new Scene();
    s1->deserialize(data);
    cout << s1->serialize() << endl;
    
    return 0;
  
}