#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <functional>
#include "Dispatcher.h"
#include "Storage.h"

namespace Strife {
    namespace Core {
        
        class Scene;
        
        template <class C>
        class System {
            
        private:
        
            template <class E>
            using Callback = std::function<void(C* const, const E&)>;
            
            template <class E>
            class Binding {
                
            public:
            
                Binding(Callback<E> callback)
                    : callback_(callback) {}
                ~Binding() = default;
                
                void operator()(C* const component, const Event& event) {
                    callback_(component, static_cast<const E&>(event));
                }
                
            private:
            
                Callback<E> callback_;
                
            }
            
        public:
        
            System(Scene& scene, Dispatcher& dispatcher)
                : ISystem(scene);
                , dispatcher_(dispatcher)
                , storage_(storage) {
                C::Initialize(messenger_);
            }
            ~System() = default;
            
            template <class E>
            void on(Callback<E> callback) {
				const std::type_index type = std::type_index(typeid(E));
				Binding<E> binding(callback);
				callbacks_.insert({ type, binding });
				dispatcher_.on<E>(std::bind(&System<C>::emit<E>, this, std::placeholders::_1))
            }
            
            template <class E>
            void emit(const Event& event) {
				const std::type_index type = std::type_index(typeid(E));
				Callback<Event> callback = callbacks_[type];
				if (event.target.has_value()) {
				    
				}
            }
                
        private:
            
            Dispatcher& dispatcher_;
            Storage& storage_;
            
        };
        
    }
}

#endif