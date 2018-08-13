#include "Unique.h"

Unique::Unique(void) :
    id(Unique::Generator()) {};
    
Unique::Unique(const boost::uuids::uuid id) :
    id(id) {};

boost::uuids::random_generator Unique::Generator;