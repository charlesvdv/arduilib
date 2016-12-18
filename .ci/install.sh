#!/bin/bash

set -e

# Set python3.5 as default version
sudo mv /usr/bin/python3.5 /usr/bin/python

# Install ninja
wget https://github.com/ninja-build/ninja/releases/download/v1.7.2/ninja-linux.zip
unzip ninja-linux.zip && sudo cp ninja /usr/bin && sudo chmod +x /usr/bin/ninja

# Install meson
pip3 install meson

# Install cmocka
wget https://cmocka.org/files/1.1/cmocka-1.1.0.tar.xz
tar xf cmocka-1.1.0.tar.xz
cd cmocka-1.1.0 && mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
cd ../..

# Install jansson
wget http://www.digip.org/jansson/releases/jansson-2.9.tar.gz
tar xvf jansson-2.9.tar.gz && cd jansson-2.9
mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=/usr .. && make && sudo make install
cd ../..
