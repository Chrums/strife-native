#include "Body.h"

#include "Math.h"

#include <iostream>

using namespace std;
using nlohmann::json;

Body::Body(const Body& body) :
    Component(body.entity) {};

Body::Body(Entity* entity) :
    Component(entity) {};