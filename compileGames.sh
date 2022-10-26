#!/bin/bash
CWD=$(pwd)
echo "Writing in: $CWD"

rm -rf $CWD/compiled
mkdir $CWD/compiled
mkdir $CWD/compiled/Hephaestus/
mkdir $CWD/compiled/GameOfLife/
mkdir $CWD/compiled/LowData/
mkdir $CWD/compiled/PhysicsDemo/
mkdir $CWD/compiled/Olympus/

echo "CMAKE Hephaestus $CWD/compiled/Hephaestus"
cmake -B$CWD/compiled/Hephaestus/ -S$CWD/Hephaestus/
echo "Compiling Hephaestus $CWD/compiled/Hephaestus"
cd $CWD/compiled/Hephaestus/
make 
cd $CWD

echo "CMAKE Game of Life $CWD/compiled/GameOfLife/"
cmake -B$CWD/compiled/GameOfLife/ -S$CWD/Games/GameOfLife/
echo "Compiling Game Of Life $CWD/compiled/GameOfLife/"
cd $CWD/compiled/GameOfLife/
make 
cd $CWD

echo "CMAKE Low Data $CWD/Games/LowData/"
cmake -B$CWD/compiled/LowData/ -S$CWD/Games/LowData/
echo "Compiling Low Data $CWD/Games/LowData/"
cd $CWD/compiled/LowData/
make 
cd $CWD

echo "CMAKE Physics Demo $CWD/Games/PhysicsDemo/"
cmake -B$CWD/compiled/PhysicsDemo/ -S$CWD/Games/PhysicsDemo/
echo "Compiling Physics Demo $CWD/Games/PhysicsDemo/"
cd $CWD/compiled/PhysicsDemo/
make 
cd $CWD

echo "CMAKE Olympus $CWD/Games/Olympus/"
cmake -B$CWD/compiled/Olympus/ -S$CWD/Games/Olympus/
echo "Compiling Olympus $CWD/Games/Olympus/"
cd $CWD/compiled/Olympus/
make
cd $CWD
