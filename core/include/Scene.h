#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
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
                void remove(const Entity entity);
                
            private:
            
                Scene& scene_;
                
            };
            
            class Components {
            
                friend class Entity;
                
            public:
            
                Components(Scene& scene);
                ~Components();
                
                void remove(const Entity entity);
                
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
                C& add(const Entity entity) {
                    std::type_index type(typeid(C));
                    Component& component = add(type, entity);
                    return static_cast<C&>(component);
                }
                
                template <class C>
                C& add(const boost::uuids::uuid id, const Entity entity) {
                    std::type_index type(typeid(C));
                    Component& component = add(type, id, entity);
                    return static_cast<C&>(component);
                }
                
                template <class C>
                void remove(const Entity entity) {
                    std::type_index type(typeid(C));
                    remove(type, entity);
                }
                
                template <class C>
                C& get(const Entity entity) const {
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
                C* const find(const Entity entity) const {
                    std::type_index type(typeid(C));
                    Component* component = find(type, entity);
                    return static_cast<C*>(component);
                }
                
            private:
            
                Scene& scene_;
                std::map<const std::type_index, IStorage* const> components_;
                
                Component& add(const std::type_index type, const Entity entity);
                Component& add(const std::type_index type, const boost::uuids::uuid id, const Entity entity);
                void remove(const std::type_index type, const Entity entity);
                Component& get(const std::type_index type, const Entity entity) const;
                IStorage& get(const std::type_index type) const;
                Component* const find(const std::type_index type, const Entity entity) const;
                
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
                    S* const system = new S(scene_);
                    systems_.insert({type, system});
                    return *system;
                }
                
            private:
            
                Scene& scene_;
                std::map<std::type_index, ISystem* const> systems_;
                
            };
            
        public:
            
            Entities entities;
            Components components;
            Systems systems;
            
            Dispatcher dispatcher;
            
            Scene();
            ~Scene() = default;
            
            template <class C>
            void initialize() {
                Storage<C>& storage = components.initialize<C>();
                systems.initialize<C>(storage);
            }
            
        };
        
    }
}

#endif