#include "Context.h"

using namespace Strife::Core;
using namespace std;

Context::Context(Scene& scene)
    : scene_(scene) {}

Context& Context::bind(const Data data) {
    return Context(scene_, data);
}

Context::Context(Scene& scene, const Data data)
    : scene_(scene)
    , data(data) {}