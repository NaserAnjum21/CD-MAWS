#!/bin/sh

#### ------------------------------------------------------------------ #####
# This is a sample script to run all the commands necessary for
# carrying out the whole process- from installing libraries to run the codes.
# You can change the input parameters here according to your needs

# Give permission and run the MAW installation script

chmod +x installMAW.sh
./installMAW.sh

# Give permission and run the Armadillo installation script

chmod +x installArmadillo.sh 
./installArmadillo.sh

# Install the DendroPy library

python3 -m pip install -U dendropy


# Remove any file having same name as the output file of MAW operation, as it appends to the file by default
# Run MAW with the input parameters.
# k -> minimum MAW length, K -> maximum MAW length, r -> use reverse complement or not

rm -f Data/input.maw.fasta
maw/maw -a DNA -i Data/input.fasta -o Data/input.maw.fasta -k 2 -K 10 -r 0


# Compile and run the Distance Matrix computation file
# i -> input file name, o -> output file name, f -> output file format

g++ -O2 main.cpp -std=c++0x -o main -larmadillo  
./main -i Data/input.maw.fasta -o Data/dist_matrix.csv -f csv

# Produce Newick tree file from distance matrix
# i -> input file name, o -> output file name, a -> algorith name folder
python3 distToNewick.py -i Data/dist_matrix.csv -o Data/tree.txt -a UPGMA
