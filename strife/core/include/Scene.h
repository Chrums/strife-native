#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <set>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Common.h"
#include "Component.h"
#include "Entity.h"
#include "Storage.h"

namespace Strife {

    class Scene {
        
        class Entities : private std::set<Entity> {
            
        public:
        
            Entities(Scene* const scene);
            
            const nlohmann::json serialize() const;
            void deserialize(const nlohmann::json data);
            
            const Entity* const add();
            const Entity* const add(const boost::uuids::uuid id);
            void remove(const Entity* const entity);
        
        private:
        
            Scene* const scene_;
            
        };
        
        class Components : private std::map<std::type_index, IStorage* const> {
            
        public:
            
            ~Components();
            
            const nlohmann::json serialize() const;
            void deserialize(const nlohmann::json data);
            
            Component* const add(const std::type_index type, const Entity* const entity);
            Component* const add(const std::type_index type, const boost::uuids::uuid id, const Entity* const entity);
            void remove(const std::type_index type, const Entity* const entity);
            Component* const get(const std::type_index type, const Entity* const entity) const;
            
            template <class T>
            void initialize(std::string identifier) {
                std::type_index type = std::type_index(typeid(T));
                this->insert({ type, new Storage<T>() });
                identifierToType_.insert({ identifier, type });
                typeToIdentifier_.insert({ type, identifier });
            };
            
            template <class T, class S>
            void initialize(std::string identifier) {
                std::type_index type = std::type_index(typeid(T));
                this->insert({ type, new S() });
                identifierToType_.insert({ identifier, type });
                typeToIdentifier_.insert({ type, identifier });
            };
            
            template <class T>
            T* const add(const Entity* const entity) {
                std::type_index type(typeid(T));
                Component* const component = add(type, entity);
                return static_cast<T* const>(component);
            };
            
            template <class T>
            T* const add(const boost::uuids::uuid id, const Entity* const entity) {
                std::type_index type(typeid(T));
                Component* const component = add(type, id, entity);
                return static_cast<T* const>(component);
            };
            
            template <class T>
            void remove(const Entity* const entity) {
                std::type_index type(typeid(T));
                remove(type, entity);
            };
            
            template <class T>
            T* const get(const Entity* const entity) {
                std::type_index type(typeid(T));
                Component* const component = get(type, entity);
                return static_cast<T* const>(component);
            };
            
        private:
            
            std::map<std::string, std::type_index> identifierToType_;
            std::map<std::type_index, std::string> typeToIdentifier_;
            
        };
        
    public:
        
        Entities entities;
        Components components;
        
        Scene();
        
        const nlohmann::json serialize() const;
        void deserialize(const nlohmann::json data);
        
    };

}

#endif