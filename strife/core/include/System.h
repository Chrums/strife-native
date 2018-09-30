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

            virtual void intialize() const = 0;

        protected:

            Scene* const scene_;

        };

        template <class T>
        class System : public ISystem {

        public:

            System(Scene* const scene) :
                ISystem(scene) {};

            void initialize() const {

            };

            template<class E>
            void on(std::function<void(Event*)> callback) {
                const std::type_index eventType = std::type_index(typeid(E));
                callbacks_.insert({ eventType, callback });
                //Strife::Core::Engine::Instance().dispatcher.on(std::bind(&dispatchEvent, &this, std::placeholders::_1));
            }

            void dispatchEvent(Event* event, std::type_index eventType) {
                T* const component = event->entity.components.get<T>();
                auto callback = callbacks_.find(eventType);
                callback(component, event);
            }

        private:

            std::unordered_map<const std::type_index, std::function<void(T const&, Event*)> > callbacks_;

        };

    }
}

#endif
