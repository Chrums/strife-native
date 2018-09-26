#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <set>
#include <string>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Entity.h"
#include "Storage.h"

namespace Strife {
    
    class Scene {
        
        class Entities : private std::set<Entity> {
        
        public:
            
            Entities(Scene* const scene) :
                scene_(scene) {};
            
            nlohmann::json serialize() {
                nlohmann::json data;
                for (const Entity& entity : *this) {
                    std::string entityData = boost::lexical_cast<std::string>(entity.id);
                    data.push_back(entityData);
                }
                return data;
            };
            
            void deserialize(nlohmann::json data) {
                for (auto& entityData : data) {
                    boost::uuids::uuid entityId = boost::lexical_cast<boost::uuids::uuid>(entityData.get<std::string>());
                    add(entityId);
                }
            };
            
            const Entity* const add() {
                return &(*this->emplace(scene_).first);
            };
            
            const Entity* const add(const boost::uuids::uuid id) {
                return &(*this->emplace(id, scene_).first);
            };
            
            void remove(const Entity* const entity) {
                this->erase(*entity);
            };
            
        private:
            
            Scene* const scene_;
            
        };
        
        class Components : private std::map<std::type_index, IStorage*> {
            
        public:
        
            ~Components() {
                for (auto& it : *this) {
                    delete it.second;
                }
            };
            
            nlohmann::json serialize();
            void deserialize(nlohmann::json data);
            
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
            
            Component* const add(const std::type_index type, const Entity* const entity) {
                return this->at(type)->add(entity);
            };
            
            Component* const add(const std::type_index type, const boost::uuids::uuid id, const Entity* const entity) {
                return this->at(type)->add(id, entity);
            };
            
            void remove(const std::type_index type, const Entity* const entity) {
                this->at(type)->remove(entity);
            };
            
            Component* const get(const std::type_index type, const Entity* const entity) const {
                return this->at(type)->get(entity);
            };
            
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
        
        nlohmann::json serialize();
        void deserialize(nlohmann::json data);
        
    };
    
}

#endif