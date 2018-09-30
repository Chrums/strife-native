#ifndef UNIQUE_H
#define UNIQUE_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/nil_generator.hpp>

namespace Strife {
    
    class Unique {
        
    public:
    
        static boost::uuids::nil_generator NilGenerator;
        static boost::uuids::random_generator RandomGenerator;
        
        static Unique Nil();
        static Unique Random();
        
        const boost::uuids::uuid id;
        
        Unique(const Unique& unique);
        Unique();
        Unique(const boost::uuids::uuid id);
        
        bool operator<(const Unique& unique) const;
            
    };
    
}

#endif