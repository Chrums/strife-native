#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <functional>
#include "Dispatcher.h"
#include "Entity.h"
#include "Event.h"
#include "ISystem.h"
#include "Storage.h"

namespace Strife {
	namespace Core {

		class Scene;

		template <class C>
		class System : public ISystem {
			
			template <class E>
			using Callback = std::function<void(C* const, const E&)>;
			
			template <class E>
			class Binding {
			public:
				
				Binding(Callback<E> callback)
					: callback_(callback) {}
					
				void operator()(C* const component, const Event& event) {
					callback_(component, static_cast<const E&>(event));
				}
				
			private:
			
				Callback<E> callback_;
				
			};

		public:
		
			System(Scene& scene, Dispatcher& dispatcher, IStorage& storage)
			    : ISystem(scene)
			    , dispatcher_(dispatcher)
			    , storage_(storage) {
				C::Initialize(*this);
			};

			~System() = default;

			template <class E>
			void on(Callback<E> callback) {
				const std::type_index type = std::type_index(typeid(E));
				Binding<E> binding(callback);
				callbacks_.insert({type, binding});
				dispatcher_.initialize<E>();  // TODO: Do this elsewhere... probably wherever the Event class is declared... (Engine::Instance()->dispatcher.initialize<E>())
				dispatcher_.on<E>(std::bind(&System<C>::dispatch<E>, this, std::placeholders::_1));
			};

			template <class E>
			void dispatch(const Event& event) {
				const std::type_index type = std::type_index(typeid(E));
				auto& callback = callbacks_[type];
				if (event.entity.has_value()) {
					try {
						C* const component = event.entity.value().components.get<C>();
						callback(component, event);
					} catch (...) {
						// TODO: Really though, this shouldn't be an exception
						// Also, it's a bit odd that we have check all event handlers
						// against an entity given we could know which are being handled
					}
				} else {
					for (auto [ entity, component ] : storage_) {
						callback(static_cast<C* const>(component), event);
					}
				}
			};

		private:
			std::map<const std::type_index, Callback<Event>> callbacks_;
			Dispatcher& dispatcher_;
			IStorage& storage_;
        };

	}  // namespace Core
}  // namespace Strife

#endif
