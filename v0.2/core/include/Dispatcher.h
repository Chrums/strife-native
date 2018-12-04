#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <map>
#include <queue>
#include <set>
#include <typeindex>
#include "Event.h"
#include "Messenger.h"

namespace Strife {
    namespace Core {
        
        class Dispatcher {
            
        public:
        
            static const unsigned int Synchronous;
            static const unsigned int Final;
			
			void dispatch();
			void dispatch(const std::type_index type);
			void dispatch(const std::type_index type, Event* const event);
			
			template <class E>
			void on(Messenger::Callback<E> callback) {
			    Event::AssertBase<E>();
			    const std::type_index type = std::type_index(typeid(E));
			    messenger_.on<E>(callback);
			}
			
			template <class E, typename... Args>
			void emit(Args... args) {
			    Event::AssertBase<E>();
			    const std::type_index type = std::type_index(typeid(E));
			    const unsigned int priority = E::Priority;
			    E* const event = new E(std::forward<Args>(args)...);
			    emit(type, priority, event);
			}
			
		private:
		
			void emit(const std::type_index type, const unsigned int priority, Event* const event);
            
            Messenger messenger_;
            std::map<const unsigned int, std::set<std::type_index>> priorities_;
            std::map<const std::type_index, std::queue<Event* const>> events_;
            
        };
        
    }
}

#endif