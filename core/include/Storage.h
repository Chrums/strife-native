#ifndef STORAGE_H
#define STORAGE_H

#include <map>
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
            
        public:
        
            class Iterator : public IIterator<IStorage::Iterator::Type> {
                
            public:
            
                Iterator(typename std::map<Entity, C>::iterator iterator)
                    : iterator_(iterator) {}
                ~Iterator() = default;
                
                Iterator& operator++() {
                    iterator_++;
                    return *this;
                }
                
                Iterator& operator++(int) {
                    ++iterator_;
                    return *this;
                }
                
                bool operator==(const IIterator<IStorage::Iterator::Type>& iterator) const {
                    return iterator_ == static_cast<const Iterator&>(iterator).iterator_;
                }
                
                bool operator!=(const IIterator<IStorage::Iterator::Type>& iterator) const {
                    return iterator_ != static_cast<const Iterator&>(iterator).iterator_;
                }
                
                IStorage::Iterator::Type operator*() {
                    return {iterator_->first, iterator_->second};
                }
                
            private:
            
                typename std::map<Entity, C>::iterator iterator_;
                
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
            
            C& get(const Entity entity) {
                return components_.at(entity);
            }
            
            C* const find(const Entity entity) {
                auto iterator = components_.find(entity);
                return iterator != components_.end()
                    ? &iterator->second
                    : nullptr;
            }
            
            IStorage::Iterator begin() {
                return IStorage::Iterator(new Iterator(components_.begin()));
            }
            
            IStorage::Iterator end() {
                return IStorage::Iterator(new Iterator(components_.end()));
            }
            
        private:
        
            std::map<Entity, C> components_;
        
        };
        
    }
}

#endif