#!/bin/bash
CWD=$(pwd)
echo "Writing in: $CWD"

rm -rf $CWD/compiled
mkdir $CWD/compiled
mkdir $CWD/compiled/GameOfLife/
mkdir $CWD/compiled/LowData/
mkdir $CWD/compiled/PhysicsDemo/
mkdir $CWD/compiled/Olympus/

echo "CMAKE Game of Life $CWD"
cmake -B$CWD/compiled/GameOfLife/ -S$CWD/Games/GameOfLife/
echo "Compiling Game Of Life $CWD"
cd $CWD/compiled/GameOfLife/
make 
cd $CWD

echo "CMAKE Low Data $CWD"
cmake -B$CWD/compiled/LowData/ -S$CWD/Games/LowData/
echo "Compiling Low Data $CWD"
cd $CWD/compiled/LowData/
make 
cd $CWD

echo "CMAKE Physics Demo $CWD"
cmake -B$CWD/compiled/PhysicsDemo/ -S$CWD/Games/PhysicsDemo/
echo "Compiling Physics Demo $CWD"
cd $CWD/compiled/PhysicsDemo/
make 
cd $CWD

echo "CMAKE Olympus $CWD"
cmake -B$CWD/compiled/Olympus/ -S$CWD/Games/Olympus/
echo "Compiling Olympus $CWD"
cd $CWD/compiled/Olympus/
make
cd $CWD
