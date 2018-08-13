#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include "Scene.h"
#include "Entity.h"

int main() {
  Scene s;
  
  
  Entity e0 = s.AddEntity();
  Entity e00 = s.AddEntity(e0);
  Entity e01 = s.AddEntity(e0);
  
  Entity e1 = s.AddEntity();
  Entity e10 = s.AddEntity(e1);
  Entity e11 = s.AddEntity(e1);
  
  s.MoveEntity(e0, e1);
  s.RemoveEntity(e1);
  
  std::vector<std::optional<std::reference_wrapper<Entity>>> e0c = e0.GetChildren();
  std::for_each(e0c.begin(), e0c.end(), [](std::optional<std::reference_wrapper<Entity>> child) {
    if (child) std::cout << child->get().id << std::endl;
  });
  
  return 0;
}