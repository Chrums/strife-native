mkdir build
cd build
#cmake ..
conan install ..
#make
conan build ..
./bin/main
cd ..

#mkdir build
#cd build
#emcmake cmake -DBoost_INCLUDE_DIR=$HOME/boost_1_68_0 ..
#emmake make
#node main.js
#cd ..