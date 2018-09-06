#ifndef UNIQUE_H
#define UNIQUE_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Unique {
public:
    const boost::uuids::uuid id;
    Unique();
    Unique(const boost::uuids::uuid id);
private:
    static boost::uuids::random_generator Generator;
};

#endif