#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>
#include <functional>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Component.h"
#include "Entity.h"
#include "Engine.h"
#include "Event.h"

namespace Strife {
    namespace Core {

        class Scene;

        class ISystem {

        public:

            ISystem(Scene* const scene) :
                scene_(scene) {};

            virtual ~ISystem() = default;

            virtual void initialize() const = 0;

        protected:

            Scene* const scene_;

        };

        template <class T>
        class System : public ISystem {

        public:

            System(Scene* const scene) :
                ISystem(scene) {};

            virtual void initialize() const {

            };

            ~System() {

            }

            template<class E>
            void on(std::function<void(T*, Event*)> callback) {
                const std::type_index eventType = std::type_index(typeid(E));
                callbacks_.insert({ eventType, callback });
                std::function<void(Event*, std::type_index)> boundCallback = [this](Event* event, std::type_index type) { dispatchEvent(event, type); };
                Engine::Instance()->dispatcher.on<E>(boundCallback);
            }

            void dispatchEvent(Event* event, std::type_index eventType) {
                T* const component = event->entity.components.get<T>();
                auto callback = callbacks_.find(eventType);
                callback->second(component, event);
            }

        private:

            std::map<const std::type_index, std::function<void(T*, Event*)> > callbacks_;

        };

    }
}

#endif
