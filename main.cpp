#include <iostream>
#include <boost/uuid/uuid_io.hpp>

#include "Scene.h"
#include "Transform.h"

int main() {
    
    Scene s;
    s.RegisterComponent<Transform>();
    
    
    return 0;
  
}