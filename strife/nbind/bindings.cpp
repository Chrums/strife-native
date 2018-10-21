#include <iostream>
#include <nbind/nbind.h>

void sayHello(std::string name) {
  std::cout << "Hello, " << name << "!\n";
}

NBIND_GLOBAL() {
  function(sayHello);
}
