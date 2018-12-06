#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
#include "Dispatcher.h"
#include "Entity.h"
#include "Event.h"
#include "IStorage.h"
#include "ISystem.h"
#include "Storage.h"
#include "System.h"

namespace Strife {
    namespace Core {
        
        class Scene {
            
        public:
        
            class Entities {
            	
            public:
            
            	class AddEvent : public Event {
            		
            		using Event::Event;
            		
            	public:
            	
            		static const unsigned int Priority;
            		
            	};
            	
            	class RemoveEvent : public Event {
            		
            		using Event::Event;
            		
            	public:
            	
            		static const unsigned int Priority;
            		
            	};
                
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
                IStorage::Iterator find(const std::type_index type, const Entity& entity) const;
                
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
				C& get(const Entity& entity) {
					std::type_index type(typeid(C));
					Component& component = get(type, entity);
					return static_cast<C&>(component);
				}
				
				template <class C>
				typename Storage<C>::Iterator find(const Entity& entity) {
					std::type_index type(typeid(C));
					return find(type, entity);
				}
				
            private:
            
                Scene& scene_;
                std::map<const std::type_index, IStorage* const> components_;
                
            };
            
            class Systems {
                
            public:
            
                Systems(Scene& scene);
                ~Systems();
                
                template <class C>
				System<C>& initialize(Storage<C>& storage) {
					Component::AssertBase<C>();
					std::type_index type(typeid(C));
					System<C>* const system = new System<C>(scene_, scene_.dispatcher, storage);
					systems_.insert({type, system});
					return *system;
				}
				
				template <class S>
				S& initialize() {
					ISystem::AssertBase<S>();
					std::type_index type(typeid(S));
					S* const system = new S(scene_, scene_.dispatcher);
					systems_.insert({type, system});
					return *system;
				}
                
            private:
            
                Scene& scene_;
                std::map<std::type_index, ISystem* const> systems_;
                
            };
            
        public:
        
            Dispatcher dispatcher;
            Entities entities;
			Components components;
			Systems systems;
			
			Scene();
			~Scene() = default;
			
			Scene& operator=(const Scene& scene);
			
			template <class C>
			void initialize() {
				Storage<C>& storage = components.initialize<C>();
				systems.initialize<C>(storage);
			}
            
        };
        
    }
}

#endif