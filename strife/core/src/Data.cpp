#include "Data.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Data::Context::Context(Scene& scene)
    : scene_(scene) {}

Data::Data()
    : json()
    , context_(nullptr) {}

Data::Data(const Data& data)
    : json(data)
    , context_(data.context_) {}
    
Data::Data(const json& j)
    : json(j)
    , context_(nullptr) {}
    
Data& Data::operator=(const json& j) {
    json::operator=(j);
}

Data& Data::bind(Context* const context) {
    context_ = context;
}

Data& Data::bind(Data& data) {
    context_ = data.context_;
}