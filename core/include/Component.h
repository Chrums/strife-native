#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.h"
#include "Unique.h"

namespace Strife {
    namespace Core {
        
        class Component : public Unique {
        
        public:
        
			template <class C>
			static void AssertBase();
			
			const Entity entity;
			
			Component(const Entity entity);
			Component(const boost::uuids::uuid id, const Entity entity);
			virtual ~Component() = default;
            
        };

		template <class C>
		void Component::AssertBase() {
            static_assert(std::is_base_of<Component, C>::value, "Type not derived from Component");
		}
        
    }
}

#endif