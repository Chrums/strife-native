#ifndef UNIQUE_H
#define UNIQUE_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/nil_generator.hpp>

#include <nlohmann/json.hpp>

class Unique {
    
public:

    boost::uuids::uuid id;
    Unique();
    Unique(const boost::uuids::uuid id);
    
    virtual nlohmann::json serialize();
    virtual void deserialize(nlohmann::json data);
    
    static boost::uuids::random_generator RandomGenerator;
    static boost::uuids::nil_generator NilGenerator;
    
};

#endif