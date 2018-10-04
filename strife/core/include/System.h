#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Component.h"
#include "Entity.h"
#include "Event.h"
#include "Dispatcher.h"
#include "ISystem.h"

namespace Strife {
    namespace Core {

        class Scene;

        template <class T>
        class System : public ISystem {

        public:

            System(Scene* const scene, Dispatcher& dispatcher) :
                ISystem(scene), dispatcher_(dispatcher) {};

            virtual void initialize() {
                T::initialize(*this);
            };

            ~System() {

            }

            template<class E>
            void on(std::function<void(T*, Event*)> callback) {
                const std::type_index eventType = std::type_index(typeid(E));
                callbacks_.insert({ eventType, callback });
                std::function<void(Event*, std::type_index)> boundCallback = [this](Event* event, std::type_index type) { dispatchEvent(event, type); };
                dispatcher_.initialize<E>();
                dispatcher_.on<E>(boundCallback);
            }

            void dispatchEvent(Event* event, std::type_index eventType) {
                auto callback = callbacks_.find(eventType);
                if (event->entity.has_value()) {
                    try {
                        T* const component = event->entity.value().components.get<T>();
                        callback->second(component, event);
                    } catch (...) {
                        // TODO: Really though, this shouldn't be an exception
                        // Also, it's a bit odd that we have check all event handlers
                        // against an entity given we could know which are being handled
                    }
                } else {
                    const std::type_index type = std::type_index(typeid(T));
                    auto components = getComponents(type);
                    for (auto component : components) {
                        callback->second((T*)component, event);
                    }
                }
            }

        private:

            std::map<const std::type_index, std::function<void(T*, Event*)> > callbacks_;
            Dispatcher& dispatcher_;

        };

    }
}

#endif
