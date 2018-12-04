#ifndef IITERATOR_H
#define IITERATOR_H

namespace Strife {
    namespace Core {
        
        template <typename T>
        class IIterator {
            
        public:
        
            IIterator() = default;
            virtual ~IIterator() = default;
            
            virtual IIterator& operator++() = 0;
            virtual IIterator& operator++(int) = 0;
            virtual bool operator==(const IIterator& iterator) const = 0;
            virtual bool operator!=(const IIterator& iterator) const = 0;
            virtual T operator*() = 0;
            
        };

    }
}

#endif