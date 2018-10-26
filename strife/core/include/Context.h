#ifndef CONTEXT_H
#define CONTEXT_H

#include <map>
#include <optional>
#include <boost/uuid/uuid.hpp>
#include "Data.h"
#include "Entity.h"

namespace Strife {
    namespace Core {

        class Scene;

        class Context {
        				
        public:
        
        	const Data data;
        	Scene& scene;
        
        	Context(Scene& scene);
        	void destroy();
        	Entity at(const boost::uuids::uuid id);
        	std::optional<Entity> operator[](const std::string field);
        	Context bind(const Data data);
        	
        private:
        
        	Context(Scene& scene, std::map<boost::uuids::uuid, Entity>* context, const Data data);
        	
        	std::map<boost::uuids::uuid, Entity>* context_;
        	
        };

    }
}

#endif