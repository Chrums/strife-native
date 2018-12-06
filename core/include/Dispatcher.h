#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>

#include <map>
#include <queue>
#include <set>
#include <typeindex>
#include "Message.h"
#include "Messenger.h"

namespace Strife {
    namespace Core {
        
        class Dispatcher {
            
        public:
        
            using Priority = unsigned int;
            
        public:
        
            static const Priority Synchronous;
            static const Priority Final;
            
            void dispatch();
            
            template <class M>
            void on(Messenger::Callback<M> callback) {
                Message::AssertBase<M>();
                const std::type_index type = std::type_index(typeid(M));
                messenger_.on<M>(callback);
            }
            
            template <class M, typename... Args>
            void emit(Args... args) {
                Message::AssertBase<M>();
                const std::type_index type = std::type_index(typeid(M));
                const Priority priority = M::Priority;
                M* const message = new M(std::forward<Args>(args)...);
                if (priority == Dispatcher::Synchronous) {
                    dispatch(message);
                } else {
                    priorities_[priority].insert(type);
                    messages_[type].push(message);
                }
            }
            
        private:
            
            Messenger messenger_;
            std::map<const Priority, std::set<std::type_index>> priorities_;
            std::map<const std::type_index, std::queue<Message* const>> messages_;
            
            void dispatch(const std::type_index type);
            void dispatch(Message* const message);
            
        };
        
    }
}

#endif