#ifndef EVENTS_H
#define EVENTS_H

#include <functional>
#include <map>
#include <set>
#include <typeindex>
#include <queue>
#include "Entity.h"
#include "Event.h"

namespace Strife {
    namespace Core {
        
        typedef std::function<void(Event*)> Callback;
        
        class Dispatcher {
            
        public:
        
            template <class T>
            void initialize() {
                const std::type_index type = std::type_index(typeid(T));
                events_[type];
                std::set<std::type_index> types = priorities_[T::Priority];
                types.insert(type);
            }
            
            template <class T>
            void on(std::function<void(T*)> callback) {
                const std::type_index type = std::type_index(typeid(T));
                callbacks_.insert({ type, callback });
            };
            
            template <class T>
            void trigger(const Entity& entity) {
                const std::type_index type = std::type_index(typeid(T));
                T* const event = new T(entity);
                if (T::Priority == Event::Synchronous) {
                    dispatch<T>(event);
                    delete event;
                } else {
                    //events_[type].push(event);
                }
            };
            
            template <class T>
            void trigger(const Entity& entity, std::function<void(T&)> initializer) {
                const std::type_index type = std::type_index(typeid(T));
                T* const event = new T(entity);
                initializer(*event);
                if (T::Priority == Event::Synchronous) {
                    dispatch<T>(event);
                    delete event;
                } else {
                    //events_[type].push(event);
                }
            };
            
            template <class T>
            void dispatch() {
                
            }
            
        private:
        
            std::map<const std::type_index, std::queue<Event*>> events_;
            std::map<const unsigned int, std::set<std::type_index>> priorities_;
            std::map<const std::type_index, std::function<void(Event*)>> callbacks_;
            
        };
        
    }
}

#endif