#include "Engine.h"

using namespace Strife::Core;
using namespace std;

Engine* Engine::instance_ = nullptr;

Engine* Engine::Instance() {
  if (Engine::instance_ == nullptr) {
    Engine::instance_ = new Engine();
  }
  return Engine::instance_;
}
