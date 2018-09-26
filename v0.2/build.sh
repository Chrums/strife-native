mkdir build
cd build
conan install ..
conan build ..
./bin/main
cd ..