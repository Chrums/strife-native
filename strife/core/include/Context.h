#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <memory>
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
        	Entity at(const boost::uuids::uuid id);
        	Context bind(const Data data);
        	
        	template<typename T>
        	T get(const std::string field) {
        	    return data[field].get<T>();
        	}
        	
        private:
        
        	Context(Scene& scene, std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context, const Data data);
        	
        	std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context_;
        	
        };
        	
    	template<>
        inline std::optional<Entity> Context::get(const std::string field) {
            const Data identifier = data[field];
            if (!identifier.is_null()) {
                const boost::uuids::uuid id = identifier.get<boost::uuids::uuid>();
            	return at(id);
            } else {
                return std::nullopt;
            }
        }

    }
}

#endif