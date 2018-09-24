#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Entity.h"
#include "Storage.h"

namespace Strife {
    
    class Scene {
        
        class Entities : private std::set<Entity> {
        
        public:
            
            Entities(Scene* const scene);
            
            const Entity* const add();
            const Entity* const add(const boost::uuids::uuid id);
            void remove(const Entity* const entity);
            
        private:
            
            Scene* const scene_;
            
        };
        
        class Components : private std::map<std::type_index, IStorage*> {
            
        public:
            
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
            
            Component* const add(const std::type_index type, const Entity* const entity);
            Component* const add(const std::type_index type, const boost::uuids::uuid id, const Entity* const entity);
            void remove(const std::type_index type, const Entity* const entity);
            Component* const get(const std::type_index type, const Entity* const entity) const;
            
            template <class T>
            T* const add(const Entity* const entity) {
                return static_cast<Storage<T>*>(this->at(std::type_index(typeid(T))))->add(entity);
            };
            
            template <class T>
            T* const add(const boost::uuids::uuid id, const Entity* const entity) {
                return static_cast<Storage<T>*>(this->at(std::type_index(typeid(T))))->add(id, entity);
            };
            
            template <class T>
            void remove(const Entity* const entity) {
                static_cast<Storage<T>*>(this->at(std::type_index(typeid(T))))->remove(entity);
            };
            
            template <class T>
            T* const get(const Entity* const entity) {
                return static_cast<Storage<T>*>(this->at(std::type_index(typeid(T))))->get(entity);
            };
            
        private:
            
            std::map<std::string, std::type_index> identifierToType_;
            std::map<std::type_index, std::string> typeToIdentifier_;
            
        };
        
    public:
    
        Entities entities;
        Components components;
    
        Scene();
        
    };
    
}

#endif