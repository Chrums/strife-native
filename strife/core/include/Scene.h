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
                Component* const get(const std::type_index type, const Entity& entity) const;

                template <class T>
                void initialize() {
                    std::type_index type = std::type_index(typeid(T));
                    this->insert({ type, new Storage<T>(&scene_) });
                    identifierToType_.insert({ T::Identifier, type });
                    typeToIdentifier_.insert({ type, T::Identifier });
                };

                // template <class T, class S>
                // void initialize(std::string identifier) {
                //     std::type_index type = std::type_index(typeid(T));
                //     this->insert({ type, new S(&scene_) });
                //     identifierToType_.insert({ identifier, type });
                //     typeToIdentifier_.insert({ type, identifier });
                // };

                template <class T>
                T* const add(const Entity& entity) {
                    std::type_index type(typeid(T));
                    Component* const component = add(type, entity);
                    return static_cast<T* const>(component);
                };

                template <class T>
                T* const add(const boost::uuids::uuid id, const Entity& entity) {
                    std::type_index type(typeid(T));
                    Component* const component = add(type, id, entity);
                    return static_cast<T* const>(component);
                };

                template <class T>
                void remove(const Entity& entity) {
                    std::type_index type(typeid(T));
                    remove(type, entity);
                };

                template <class T>
                T* const get(const Entity& entity) {
                    std::type_index type(typeid(T));
                    Component* const component = get(type, entity);
                    return static_cast<T* const>(component);
                };

            private:

                Scene& scene_;
                std::map<std::string, std::type_index> identifierToType_;
                std::map<std::type_index, std::string> typeToIdentifier_;

            };

        private:

            std::vector<ISystem*> systems_;
            Dispatcher& dispatcher_;

        public:

            const Entities entities;
            Components components;

            Scene(Dispatcher& dispatcher);
            ~Scene();

            template <class T>
            void initialize() {
                components.initialize<T>();
                System<T>* system = new System<T>(this, dispatcher_);
                system->initialize();
                systems_.push_back(system);
            }

            const Data serialize() const;
            void deserialize(const Data data);

        };

    }
}

#endif
