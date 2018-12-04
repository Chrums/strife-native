#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
#include "Entity.h"
#include "IStorage.h"
#include "Storage.h"

namespace Strife {
    namespace Core {
        
        class Scene {
            
        private:
        
            class Entities {
                
            public:
            
                Entities(Scene& scene);
                ~Entities() = default;
                
                const Entity add();
                void remove(const Entity& entity);
                
            private:
            
                Scene& scene_;
                
            };
            
            class Components {
                
            public:
            
                Components(Scene& scene);
                ~Components();
                
                Component& add(const std::type_index type, const Entity& entity);
                Component& add(const std::type_index type, const boost::uuids::uuid id, const Entity& entity);
                void remove(const std::type_index type, const Entity& entity);
                void remove(const Entity& entity);
                Component& get(const std::type_index type, const Entity& entity) const;
                IStorage& get(const std::type_index type) const;
                Component* const find(const std::type_index type, const Entity& entity) const;
                
                template <class C>
				Storage<C>& initialize() {
					Component::AssertBase<C>();
					std::type_index type = std::type_index(typeid(C));
					Storage<C>* const storage = new Storage<C>(scene_);
					components_.insert({type, storage});
					return *storage;
				}
				
				template <class C, class S>
				S& initialize() {
					Component::AssertBase<C>();
					IStorage::AssertBase<S>();
					std::type_index type = std::type_index(typeid(C));
					S* const storage = new S(scene_);
					components_.insert({type, storage});
					return *storage;
				}
				
				template <class C>
				C& add(const Entity& entity) {
					std::type_index type(typeid(C));
					Component& component = add(type, entity);
					return static_cast<C&>(component);
				}
				
				template <class C>
				C& add(const boost::uuids::uuid id, const Entity& entity) {
					std::type_index type(typeid(C));
					Component& component = add(type, id, entity);
					return static_cast<C&>(component);
				}
				
				template <class C>
				void remove(const Entity& entity) {
					std::type_index type(typeid(C));
					remove(type, entity);
				}
				
				template <class C>
				C& get(const Entity& entity) const {
					std::type_index type(typeid(C));
					Component& component = get(type, entity);
					return static_cast<C&>(component);
				}
				
				template <class C>
				IStorage& get() const {
					std::type_index type(typeid(C));
					return get(type);
				} 
				
				template <class C>
				C* const find(const Entity& entity) const {
					std::type_index type(typeid(C));
					Component* component = find(type, entity);
					return static_cast<C*>(component);
				}
				
            private:
            
                Scene& scene_;
                std::map<const std::type_index, IStorage* const> components_;
                
            };
            
        public:
        	
            Entities entities;
			Components components;
			
			Scene();
			~Scene() = default;
			
			template <class C>
			void initialize() {
				Storage<C>& storage = components.initialize<C>();
			}
            
        };
        
    }
}

#endif