#!/bin/bash

sudo apt update -y
sudo apt upgrade -y
sudo apt-get install -y build-essential wget git tmux pkg-config cmake python3 python3-dev libssl-dev libmodbus-dev libgtest-dev
mkdir ~/temp
cd ~/temp
wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz
tar -xf cmake-3.18.4.tar.gz
cd cmake-3.18.4 && cmake . && make && sudo make install
cd ~/temp
wget https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz
tar -xf boost_1_76_0.tar.gz
cd boost_1_76_0
./bootstrap.sh --with-python=/usr/bin/python3 
sudo ./b2
sudo ./b2 install
sudo ./b2 --with-filesystem install
sudo ./b2 --with-python install
cd ~/temp
wget https://dlcdn.apache.org//xerces/c/3/sources/xerces-c-3.2.4.tar.gz
tar -xf xerces-c-3.2.4.tar.gz
cd xerces-c-3.2.4 && ./configure --prefix=/usr && make && sudo make install
cd
rm -rf ~/temp
sudo apt update -y
sudo apt upgrade -y

