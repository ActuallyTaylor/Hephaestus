#!/bin/bash
CWD=$(pwd)
echo "Writing in: $CWD"

rm -rf $CWD/compiled
mkdir $CWD/compiled
mkdir $CWD/compiled/GameOfLife/
mkdir $CWD/compiled/LowData/
mkdir $CWD/compiled/PhysicsDemo/
mkdir $CWD/compiled/Olympus/

cd $CWD
cd ./compiled/GameOfLife/
echo "CMAKE Game of Life $CWD"
cmake $CWD/Games/GameOfLife/CMakeLists.txt
echo "Compiling Game Of Life $CWD"
make

cd $CWD
cd ./compiled/LowData/
echo "CMAKE Low Data $CWD"
cmake $CWD/Games/LowData/CMakeLists.txt
echo "Compiling Low Data $CWD"
make

cd $CWD
cd ./compiled/PhysicsDemo/
echo "CMAKE Physics Demo $CWD"
cmake $CWD/Games/PhysicsDemo/CMakeLists.txt
echo "Compiling Physics Demo $CWD"
make

cd $CWD
cd ./compiled/Olympus/
echo "CMAKE Olympus $CWD"
cmake $CWD/Olympus/CMakeLists.txt
echo "Compiling Olympus $CWD"
make