# CD-MAWS
A phylogenetic tree construction tool using Cosine Distance on Minimal Absent Word (MAW).

## Pre-requisites
You need to have C++ and Python 3 installed. Some source codes and libraries are also required to be compiled and installed at first.
Install the [MAW suite](https://github.com/solonas13/maw), the [Armadillo library](http://arma.sourceforge.net/) and the [DendroPy library](https://dendropy.org/) by the following commands:
```
./installMAW.sh
./installArmadillo.sh
python3 -m pip install -U dendropy
```

## Usage
### 1. Producing MAW
Firstly, produce the MAW sets from a input file of sequences in FASTA format by doing the following :
```
maw/maw -a DNA -i <input_file_name> -o <output_file_name> -k <min_maw_length> -K <max_maw_length> -r <reverse_complement_or_not>
```
A sample command would be:
```
maw/maw -a DNA -i Data/input.fasta -o Data/input.maw.fasta -k 4 -K 10 -r 0
```
Check the Github of the [MAW suite](https://github.com/solonas13/maw) to see more on its usage.

### 2. Computing Distance Matrix
This is the most significant part of our tool. Compute the distance matrix from the file containing all the MAWs by the following:
```
g++ -O2 main.cpp -std=c++0x -o main -larmadillo  
./main -i <input_file_name> -o <output_file_name>
```
A sample run command would be:
```
./main -i input.maw.fasta -o dist_matrix.csv
```

The default output format is in CSV. However, there is an option of producing different distance matrix file format. The eligible output file formats are given in the [defs.h](https://github.com/NaserAnjum21/MAW-based-Phylogenetics/blob/master/defs.h) file.
For example, to output distance matrix in PHYLIP format, one should run the following :

```
./main -i input.maw.fasta -o dist_matrix.phy -f phylip
```

### 3. Constructing Tree
Lastly, produce the newick representation of the phylogenetic tree constructed from the distance matrix by the following:
```
python3 distToNewick.py -i <input_file_name> -o <output_file_name> -a <algorithm_name>
```
A sample command would be:
```
python3 distToNewick.py -i Data/dist_matrix.csv -o Data/tree.txt -a UPGMA
```
Two tree construction algorithms are used here - NJ and UPGMA.

### Additional Info
If you want to perform all the installation and running steps all at once, there is a script with sample commands and parameters. Run the following:
```
./sample_runAll.sh
```
There are few shell scripts in this repository which might need permissions before running them. In that case, do the following for each:
```
chmod +x <script_file_name>
```

N.B. : The MAW suite by default appends content to exisiting file. So beware of this while using the same output file name repeatedly. 

