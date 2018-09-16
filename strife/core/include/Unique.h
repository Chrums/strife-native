#ifndef UNIQUE_H
#define UNIQUE_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <nlohmann/json.hpp>

class Unique {
    
public:

    boost::uuids::uuid id;
    Unique();
    Unique(const boost::uuids::uuid id);
    
    virtual nlohmann::json serialize();
    virtual void deserialize(nlohmann::json data);
    
private:

    static boost::uuids::random_generator Generator;
    
};

#endif