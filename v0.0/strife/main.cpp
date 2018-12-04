#include <iostream>
#include <optional>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
#include "Data.h"
#include "Entity.h"
#include "Scene.h"
#include "System.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

class OtherComponent : public Component {
    
    using Component::Component;
    
public:

	static const string Identifier;
	
	static void Initialize(System<OtherComponent>& system) {}
    
	const Data serialize() const {
	    return Data();
	}
	
    void deserialize(Data data) {}
    
};

const string OtherComponent::Identifier = "Other";

class HierarchyComponent : public Component {
    
    using Component::Component;
    
public:

	static const string Identifier;
    
    optional<Entity> parent;
    //vector<Entity> children;
    
	const Data serialize() const {
	    Data data;
	    data["parent"] = parent;
	    //data["children"] = children;
	    return data;
	}
	
    void deserialize(Data data) {
        parent = data["parent"].get<optional<Entity>>();
        //children = data["children"].get<vector<Entity>>();
    }
    
};

const string HierarchyComponent::Identifier = "Hierarchy";

int main() {
	
	Scene* s = new Scene();
	s->components.initialize<HierarchyComponent>();
	s->components.initialize<OtherComponent>();
	s->deserialize("{\"components\":{\"Hierarchy\":{\"60a7adcb-8f76-438c-b95b-150f00507f41\":{\"parent\":\"e3140528-624b-4529-991a-423b03ed69a2\",\"children\":[]},\"e3140528-624b-4529-991a-423b03ed69a2\":{\"parent\":null,\"children\":[\"60a7adcb-8f76-438c-b95b-150f00507f41\",\"e3140528-624b-4529-991a-423b03ed69a3\"]}}}}"_json);
	cout << s->serialize() << endl;
	
	return 0;
	
}
