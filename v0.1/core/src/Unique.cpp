#include "Unique.h"

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Unique::Unique() :
    id(Unique::RandomGenerator()) {};
    
Unique::Unique(const uuid id) :
    id(id) {};
    
json Unique::serialize() {
    json data;
    data["id"] = boost::lexical_cast<string>(id);
    return data;
};

void Unique::deserialize(json data) {
    id = boost::lexical_cast<uuid>(data["id"].get<string>());
}

boost::uuids::random_generator Unique::RandomGenerator;
boost::uuids::nil_generator Unique::NilGenerator;