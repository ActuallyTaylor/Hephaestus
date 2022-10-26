#!/bin/bash
sudo apt-get -y install build-essential
sudo apt-get update --allow-releaseinfo-change
sudo apt-get -y install cmake
sudo apt-get -y install libglfw3
sudo apt-get -y install libglfw3-dev
sudo apt-get -y install libglew-dev
sudo apt-get -y install libfreetype6-dev
sudo apt-get -y install libglm-dev
sudo apt-get -y install libalut-dev
sudo apt-get -y install libopenal-dev
git clone https://github.com/ActuallyZach/Hephaestus.git
cd ./Hephaestus/
./compileGames.sh