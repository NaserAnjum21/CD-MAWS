#!/bin/sh

#### ------------------------------------------------------------------ #####
# This script installs Armadillo and its pre-requisite libaries

sudo apt-get install libopenblas-dev liblapack-dev libarpack2-dev libsuperlu-dev

wget http://sourceforge.net/projects/arma/files/armadillo-9.900.1.tar.xz
tar -xvf armadillo-9.900.1.tar.xz
cd armadillo-9.900.1
./configure
make
sudo make install
echo "Armadillo Installation done.."