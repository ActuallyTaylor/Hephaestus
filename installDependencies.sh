#!/bin/bash
sudo apt install -y software-properties-common
sudo apt update --allow-releaseinfo-change
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt -y install build-essential
sudo apt update --allow-releaseinfo-change
sudo apt -y install cmake
sudo apt -y install libglfw3
sudo apt -y install libglfw3-dev
sudo apt -y install libglew-dev
sudo apt -y install libfreetype6-dev
sudo apt -y install libglm-dev
sudo apt -y install libalut-dev
sudo apt-get install libopenal-dev
git clone https://github.com/ActuallyZach/Hephaestus.git