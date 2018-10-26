#include "Data.h"

#include <iostream>
#include "Scene.h"

using namespace Strife::Core;
using namespace std;
using nlohmann::json;

Data::Data()
    : json()
    , scene_(nullptr)
    , context_(nullptr) {}
    
 Data::Data(const Data& data)
    : json(data)
    , scene_(data.scene_)
    , context_(data.context_) {}
    
Context::Context(Scene* const scene)
    : json()
    , scene_(scene)
    , context_(make_shared<map<uuid, Entity>>()) {}
    
Data::Data(const json& j)
    : json(j)
    , scene_(nullptr)
    , context_(nullptr) {}
    
// Data& Data::operator=(const json& j) {
//     return json::operator=(j);
// }

// Data& Data::bind(Context* const context) {
//     context_ = context;
// }