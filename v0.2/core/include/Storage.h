#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
#include "Entity.h"
#include "IIterator.h"
#include "IStorage.h"

namespace Strife {
    namespace Core {
        
        class Scene;
        
        template <class C>
        class Storage : public IStorage {
            
        private:
        
            using Type = std::pair<const Entity, C&>;
        
            class Iterator : public IIterator<Type> {
                
            public:
            
                Iterator(typename std::unordered_map<Entity, C>::iterator iterator)
                    : iterator_(iterator) {}
                ~Iterator() = default;
                
                void operator++() {
                    iterator_++;
                }
                
                Type operator*() {
                    return { iterator_->first, iterator_->second };
                }
                
                bool operator==(const IIterator<Type>& iterator) const {
                    return iterator_ == static_cast<const Iterator&>(iterator).iterator_;
                }
                
            private:
            
                typename std::unordered_map<Entity, C>::iterator iterator_;
                
            };
            
        public:
        
            Storage(Scene& scene)
                : IStorage(scene) {}
            ~Storage() = default;
            
            C& add(const Entity entity) {
                return components_.emplace(entity, entity).first->second;
            }
            
            C& add(const boost::uuids::uuid id, const Entity entity) {
                return components_.try_emplace(entity, id, entity).first->second;
            }
            
            void remove(const Entity entity) {
                components_.erase(entity);
            }
            
            C& get(const Entity entity) const {
                return components_.at(entity);
            }
            
            IStorage::Iterator find(const Entity entity) const {
                return IStorage::Iterator(new Iterator(components_.find(entity)));
            }
            
            IStorage::Iterator begin() {
                return IStorage::Iterator(new Iterator(components_.begin()));
            }
            
            IStorage::Iterator end() {
                return IStorage::Iterator(new Iterator(components_.end()));
            }
            
        private:
        
            std::unordered_map<Entity, C> components_;
        
        };
        
    }
}

#endif