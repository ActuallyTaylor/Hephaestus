#!/bin/bash
CWD=$(pwd)
echo "Writing in:"
echo $CWD

rm -rf $CWD/compiled
mkdir $CWD/compiled
mkdir $CWD/compiled/GameOfLife/
mkdir $CWD/compiled/LowData/
mkdir $CWD/compiled/PhysicsDemo/
mkdir $CWD/compiled/Olympus/

cd $CWD
cd ./compiled/GameOfLife/
cmake $CWD/Games/GameOfLife/CMakeLists.txt
make

cd $CWD
cd ./compiled/LowData/
cmake $CWD/Games/LowData/CMakeLists.txt
make

cd $CWD
cd ./compiled/PhysicsDemo/
cmake $CWD/Games/PhysicsDemo/CMakeLists.txt
make

cd $CWD
cd ./compiled/Olympus/
cmake $CWD/Olympus/CMakeLists.txt
make