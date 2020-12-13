#!/bin/sh

#### ------------------------------------------------------------------ #####
# This script installs MAW and its pre-requisite libaries

if [ ! -d "maw" ]; then

    while true; do
        read -p "You don't seem to have MAW here. Do you wish to install it? (Y/N) : " yn
        case $yn in
            [Yy]* ) break;;
            [Nn]* ) exit;;
            * ) echo "Please answer yes or no.";;
        esac
    done

    echo "MAW Installation starts.."
    git clone https://github.com/solonas13/maw.git
    cd maw
    ./pre-install.sh
    sudo make -f Makefile.64-bit.gcc     #this makefile doesn't compile without sudo
    echo "MAW Installation done.."
    cd ..

fi
