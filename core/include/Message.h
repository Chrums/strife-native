#ifndef MESSAGE_H
#define MESSAGE_H

namespace Strife {
    namespace Core {
        
        class Message {
            
        public:
        
            template <class M>
            static void AssertBase();
            
            Message() = default;
            virtual ~Message() = default;
            
        };
        
        template <class M>
        void Message::AssertBase() {
            static_assert(std::is_base_of<Message, M>::value, "Type not derived from Message");
        }
        
    }
}

#endif