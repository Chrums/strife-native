#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <functional>
#include "Entity.h"
#include "Event.h"
#include "Dispatcher.h"
#include "Storage.h"

namespace Strife {
    namespace Core {

        class Scene;
        
        class ISystem {

        public:
            
            template <class S>
            static void AssertBase();

            ISystem(Scene* const scene) :
                scene_(scene) {};

            virtual ~ISystem() = default;

        protected:

            Scene* const scene_;

        };
        
        template <class S>
        void ISystem::AssertBase() {
            static_assert(
                std::is_base_of<ISystem, S>::value,
                "Type not derived from ISystem"
            );
        };

        template <class C>
        class System : public ISystem {

        public:

            System(Scene* const scene, Dispatcher& dispatcher, IStorage& storage) :
                ISystem(scene),
                dispatcher_(dispatcher),
                storage_(storage) {
                C::Initialize(*this);
            };

            ~System() = default;

            template <class E>
            void on(std::function<void(C* const, Event*)> callback) {
                const std::type_index type = std::type_index(typeid(E));
                callbacks_.insert({ type, callback });
                dispatcher_.initialize<E>(); // TODO: Do this elsewhere... probably wherever the Event class is declared... (Engine::Instance()->dispatcher.initialize<E>())
                dispatcher_.on<E>(std::bind(&System<C>::dispatch, this, std::placeholders::_1, std::placeholders::_2));
            };

            void dispatch(Event* event, std::type_index type) {
                auto iteratorTypeToCallback = callbacks_.find(type);
                if (iteratorTypeToCallback != callbacks_.end()) {
                    std::function<void(C*, Event*)> callback = iteratorTypeToCallback->second;
                    if (event->entity.has_value()) {
                        try {
                            C* const component = event->entity.value().components.get<C>();
                            callback(component, event);
                        } catch (...) {
                            // TODO: Really though, this shouldn't be an exception
                            // Also, it's a bit odd that we have check all event handlers
                            // against an entity given we could know which are being handled
                        }
                    } else {
                        storage_.each(
                            [=](const Entity entity, Component* const component) {
                                callback(static_cast<C* const>(component), event);
                            }
                        );
                    }
                }
            };

        private:

            std::map<const std::type_index, std::function<void(C* const, Event*)> > callbacks_;
            Dispatcher& dispatcher_;
            IStorage& storage_;

        };

    }
}

#endif
