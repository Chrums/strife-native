#ifndef ENTITY_H
#define ENTITY_H

#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "IIterator.h"
#include "Unique.h"

namespace Strife {
    namespace Core {
        
        class Scene;
        class Component;
        
        class Entity : public Unique {
            
        private:
            
            class Components {
                
            public:
            
                Components(Entity* entity);
                ~Components() = default;
                
                Component& add(const std::type_index type);
				Component& add(const std::type_index type, const boost::uuids::uuid id);
				void remove(const std::type_index type);
				Component& get(const std::type_index type) const;
            	Component* find(const std::type_index type) const;
				
				template <class C>
				C& add() {
					const std::type_index type(typeid(C));
					Component& component = add(type);
					return static_cast<C&>(component);
				};
				
				template <class C>
				C& add(const boost::uuids::uuid id) {
					const std::type_index type(typeid(C));
					Component& component = add(type, id);
					return static_cast<C&>(component);
				};
				
				template <class C>
				void remove() {
					const std::type_index type(typeid(C));
					remove(type);
				};
				
				template <class C>
				C& get() const {
					const std::type_index type(typeid(C));
					Component& component = get(type);
					return static_cast<C&>(component);
				};
				
				template <class C>
				C* find() const {
					const std::type_index type(typeid(C));
					Component* component = find(type);
					return static_cast<C*>(component);
				}
                
            private:
            
                Entity* entity_;
                
            };
            
        public:
        
            Scene* scene;
            Components components;
        
            Entity(const Entity& entity);
			Entity(Scene& scene);
			Entity(const boost::uuids::uuid id, Scene& scene);
			~Entity() = default;
			
			bool operator==(const Entity& entity) const;
			bool operator!=(const Entity& entity) const;
            
            void destroy();
            
        };
        
    }
}

#endif