#ifndef EVENTS_H
#define EVENTS_H

#include <functional>
#include <map>
#include <set>
#include <typeindex>
#include <queue>
#include <vector>
#include "Entity.h"
#include "Event.h"

namespace Strife {
    namespace Core {

        typedef std::function<void(Event*, std::type_index)> Callback;

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
            void on(Callback callback) {
                const std::type_index type = std::type_index(typeid(T));
                auto callbacks = callbacks_.find(type);
                if (callbacks == callbacks_.end()) {
                    std::vector<Callback> callbackVector;
                    callbackVector.push_back(callback);
                    callbacks_.insert({ type, callbackVector });
                } else {
                    callbacks->second.push_back(callback);
                }
            };

            template <class T>
            void trigger(const Entity& entity) {
                const std::type_index type = std::type_index(typeid(T));
                T* const event = new T(entity);
                if (T::Priority == Event::Synchronous) {
                    dispatch(type, event);
                } else {
                    auto events = events_.find(type);
                    if (events == events_.end()) {
                        std::queue<Event*> eventQueue;
                        eventQueue.push(event);
                        events_.insert({type, eventQueue});
                    } else {
                        events->second.push(event);
                    }
                }
            };

            template <class T>
            void trigger(const Entity& entity, std::function<void(T&, std::type_index)> initializer) {
                const std::type_index type = std::type_index(typeid(T));
                T* const event = new T(entity);
                initializer(*event, type);
                if (T::Priority == Event::Synchronous) {
                    dispatch(type, event);
                } else {
                    auto events = events_.find(type);
                    if (events == events_.end()) {
                        std::queue<Event*> eventQueue;
                        eventQueue.push(event);
                        events_.insert({type, eventQueue});
                    } else {
                        events->second.push(event);
                    }
                }
            };

            void dispatch(const std::type_index type, Event* event) {
                auto callbacks = callbacks_.find(type);
                if (callbacks != callbacks_.end()) {
                    for (auto callback : callbacks->second) {
                        callback(event, type);
                    }
                }
                delete event;
            }

            void dispatch(const std::type_index type) {
                auto events = events_.find(type);
                if (events == events_.end()) {
                    return;
                }
                size_t num_events = events->second.size();
                for (size_t i = 0; i < num_events; i++) {
                    Event* event = events->second.front();
                    events->second.pop();
                    dispatch(type, event);
                }
            }

        private:

            std::map<const std::type_index, std::queue<Event*>> events_;
            std::map<const unsigned int, std::set<std::type_index>> priorities_;
            std::map<const std::type_index, std::vector<Callback> > callbacks_;

        };

    }
}

#endif
