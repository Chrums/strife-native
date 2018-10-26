#include <iostream>
#include <optional>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
#include "Context.h"
#include "Data.h"
#include "Entity.h"
#include "Scene.h"
#include "System.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

namespace Strife {
	namespace Core {
	
        void to_json(Data& data, const optional<Entity>& optional) {
			if (optional) {
				data = optional.value().id;
			} else {
				data = nullptr;
			}
	    }
	    
	    void from_json(const Data& data, optional<Entity>& optional) {
	        optional = std::nullopt;
	    }
	    
	    void to_json(Data& data, const Entity& entity) {
			data = entity.id;
	    }
	    
	    void from_json(const Data& data, Entity& entity) {
	    	
	    }
	
	}
}

class OtherComponent : public Component {
    
    using Component::Component;
    
public:

	static const string Identifier;
	
	static void Initialize(System<OtherComponent>& system) {}
    
	const Data serialize() const {
	    return Data();
	}
	
    void deserialize(Context context) {}
    
};

const string OtherComponent::Identifier = "Other";

class TestComponent : public Component {
    
    using Component::Component;
    
public:

	static const string Identifier;
	
	//static void Initialize(System<TestComponent>& system) {}
    
    optional<Entity> reference;
    string value;
    
	const Data serialize() const {
	    Data data;
	    //data["reference"] = reference;
	    data["value"] = value;
	    return data;
	}
	
    void deserialize(Context context) {
        reference = context["reference"];
        value = context.data["value"].get<string>();
    }
    
};

const string TestComponent::Identifier = "Test";

int main() {
	
	Scene* s = new Scene();
	s->components.initialize<TestComponent>();
	s->components.initialize<OtherComponent>();
	s->deserialize("{\"components\":{\"Test\":{\"60a7adcb-8f76-438c-b95b-150f00507f41\":{\"reference\":\"e3140528-624b-4529-991a-423b03ed69a2\",\"value\":\"0\"},\"e3140528-624b-4529-991a-423b03ed69a2\":{\"reference\":\"60a7adcb-8f76-438c-b95b-150f00507f41\",\"value\":\"1\"}}}}"_json);
	cout << s->serialize() << endl;
	
	return 0;
	
}
