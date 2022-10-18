rm -rf ./compiled &&
mkdir ./compiled &&
mkdir ./compiled/GameOfLife/ &&
mkdir ./compiled/LowData/ &&
mkdir ./compiled/PhysicsDemo/ &&
mkdir ./compiled/Olympus/ &&
cd ./compiled/GameOfLife/ &&
cmake ../../Games/GameOfLife/CMakeLists.txt &&
make &&
cd ../../ &&
cd ./compiled/LowData/ &&
cmake ../../Games/LowData/CMakeLists.txt &&
make &&
cd ../../ &&
cd ./compiled/PhysicsDemo/ &&
cmake ../../Games/PhysicsDemo/CMakeLists.txt &&
make &&
cd ../../ &&
cd ./compiled/Olympus/ &&
cmake ../../Olympus/CMakeLists.txt &&
make