#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <map>
#include <set>
#include <vector>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Data.h"
#include "Entity.h"
#include "Storage.h"
#include "System.h"

namespace Strife {
    namespace Core {

        class Component;

        class Scene {

            class Entities {

            public:

                Entities(Scene& scene);

                const Entity add() const;
                void remove(const Entity& entity) const;
                const Entity get(const boost::uuids::uuid id) const;

            private:

                Scene& scene_;

            };

            class Components : private std::map<std::type_index, IStorage* const> {

            public:

                Components(Scene& scene);
                ~Components();

                const Data serialize() const;
                void deserialize(const Data data);

                Component* const add(const std::type_index type, const Entity& entity);
                Component* const add(const std::type_index type, const boost::uuids::uuid id, const Entity& entity);
                void remove(const std::type_index type, const Entity& entity);
                void remove(const Entity& entity);
                IStorage* const get(const std::type_index type) const;
                Component* const get(const std::type_index type, const Entity& entity) const;

                template <class C>
                Storage<C>& initialize() {
                    //Component::AssertBase<C>();
                    std::type_index type = std::type_index(typeid(C));
                    Storage<C>* const storage = new Storage<C>(&scene_);
                    this->insert({ type, storage });
                    identifierToType_.insert({ C::Identifier, type });
                    typeToIdentifier_.insert({ type, C::Identifier });
                    return *storage;
                };

                template <class C, class S>
                S& initialize() {
                    //Component::AssertBase<C>();
                    IStorage::AssertBase<S>();
                    std::type_index type = std::type_index(typeid(C));
                    S* const storage = new S(&scene_);
                    this->insert({ type, storage });
                    identifierToType_.insert({ C::Identifier, type });
                    typeToIdentifier_.insert({ type, C::Identifier });
                    return *storage;
                };

                template <class C>
                C* const add(const Entity& entity) {
                    std::type_index type(typeid(C));
                    Component* const component = add(type, entity);
                    return static_cast<C* const>(component);
                };

                template <class C>
                C* const add(const boost::uuids::uuid id, const Entity& entity) {
                    std::type_index type(typeid(C));
                    Component* const component = add(type, id, entity);
                    return static_cast<C* const>(component);
                };

                template <class C>
                void remove(const Entity& entity) {
                    std::type_index type(typeid(C));
                    remove(type, entity);
                };
                
                template <class C>
                IStorage* const get() const {
                    std::type_index type(typeid(C));
                    return this->at(type);
                };

                template <class C>
                C* const get(const Entity& entity) {
                    std::type_index type(typeid(C));
                    Component* const component = get(type, entity);
                    return static_cast<C* const>(component);
                };

            private:

                Scene& scene_;
                std::map<std::string, std::type_index> identifierToType_;
                std::map<std::type_index, std::string> typeToIdentifier_;

            };
            
            class Systems : private std::map<std::type_index, ISystem* const> {
                
            public:
            
                Systems(Scene& scene);
                ~Systems();
                
                template <class C>
                System<C>& initialize(Dispatcher& dispatcher, Storage<C>& storage) {
                    //Component::AssertBase<C>(); Component is forward declared... should Component hold a pointer to a Scene so that this can be asserted?
                    std::type_index type(typeid(C));
                    System<C>* const system = new System<C>(&scene_, dispatcher, storage);
                    this->insert({ type, system });
                    return *system;
                }
                
                template <class S>
                S& initialize() {
                    ISystem::AssertBase<S>();
                    std::type_index type(typeid(S));
                    S* const system = new S(scene_);
                    this->insert({ type, system });
                    return *system;
                }
                
            private:
            
                Scene& scene_;
                
            };

        public:

            const Entities entities;
            Components components;
            Systems systems;

            Scene(Dispatcher& dispatcher);
            ~Scene();

            template <class C>
            void initialize() {
                Storage<C>& storage = components.initialize<C>();
                System<C>& system = systems.initialize<C>(dispatcher_, storage);
            }

            // DEPRECATED
            template <class T>
            void initializeSystem() {
                static_assert(std::is_base_of<ISystem, T>::value, "T not derived from ISystem");
                T* system = new T(this, dispatcher_);
                systems_.push_back(system);
            }

            const Data serialize() const;
            void deserialize(const Data data);

        private:
    
            std::vector<ISystem*> systems_;
            Dispatcher& dispatcher_;

        };

    }
}

#endif