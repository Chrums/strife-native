#include "Engine.h"

using namespace Strife::Core;
using namespace std;

Engine& Engine::Instance() {
  if (instance_ == nullptr) {
    instance_ = new Engine();
  }
  return *instance_;
}


Engine::~Engine() {
  delete instance_;
}
