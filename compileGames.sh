#!/bin/bash
CWD=$(pwd)
echo "Writing in: $CWD"

rm -rf $CWD/compiled
mkdir $CWD/compiled
mkdir $CWD/compiled/GameOfLife/
mkdir $CWD/compiled/LowData/
mkdir $CWD/compiled/PhysicsDemo/
mkdir $CWD/compiled/Olympus/

cd $CWD/compiled/GameOfLife/
echo "CMAKE Game of Life $CWD"
cmake $CWD/Games/GameOfLife/
echo "Compiling Game Of Life $CWD"
make

cd $CWD/compiled/LowData/
echo "CMAKE Low Data $CWD"
cmake $CWD/Games/LowData/
echo "Compiling Low Data $CWD"
make

cd $CWD/compiled/PhysicsDemo/
echo "CMAKE Physics Demo $CWD"
cmake $CWD/Games/PhysicsDemo/
echo "Compiling Physics Demo $CWD"
make

cd $CWD/compiled/Olympus/
echo "CMAKE Olympus $CWD"
cmake $CWD/Olympus/
echo "Compiling Olympus $CWD"
make