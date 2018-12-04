#ifndef ISTORAGE_H
#define ISTORAGE_H

#include <boost/uuid/uuid.hpp>
#include "IIterator.h"
#include "Component.h"
#include "Entity.h"

namespace Strife {
    namespace Core {
        
        class IStorage {
            
        public:
        
            class Iterator {
                
            public:
                
                using Type = std::pair<const Entity, Component&>;
                
            public:
            
                Iterator(IIterator<Type>* const iterator);
                ~Iterator();
                
                Iterator& operator++();
                Iterator& operator++(int);
                bool operator==(const Iterator& iterator) const;
                bool operator!=(const Iterator& iterator) const;
                Type operator*() const;
                
            protected:
                
                IIterator<Type>* const iterator_;
                
            };
            
        public:
        
            template <class S>
            static void AssertBase();
            
            IStorage(Scene& scene);
            virtual ~IStorage() = default;
            
            virtual Component& add(const Entity entity) = 0;
            virtual Component& add(const boost::uuids::uuid id, const Entity entity) = 0;
            virtual void remove(const Entity entity) = 0;
            virtual Component& get(const Entity entity) = 0;
            virtual Component* const find(const Entity entity) = 0;
            
            // virtual Iterator begin() = 0;
            // virtual Iterator end() = 0;
            
        protected:
        
            Scene& scene_;
            
        };

		template <class S>
		void IStorage::AssertBase() {
			static_assert(std::is_base_of<IStorage, S>::value, "Type not derived from IStorage");
		};
        
    }
}

#endif