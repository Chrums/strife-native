#ifndef SYSTEM_H
#define SYSTEM_H

namespace Strife {
    
    class ISystem {
        
    public:
        
        ISystem() = default;
        virtual ~ISystem() = default;
        
    };
    
    template <class T>
    class System : public ISystem {
        
    public:
        
        
        
    };
    
}

#endif