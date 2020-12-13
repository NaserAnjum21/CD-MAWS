#include <bits/stdc++.h>
#include <chrono>

#include "distanceMatrix.h"
#include "fileHandler.h"
#include "set.h"
#include "defs.h"

using namespace std;
using cloc = chrono::system_clock;
using sec = chrono::duration<double>;

vector<vector<double>> diffMatrix;
vector<map<string,char>> mawmap;
vector<Set> maws;
vector<string> taxas;

string input_file, dist_index, output_format, output_file;
double maxMAWlength;
extern int maxMAWlen;

map<string,int> formatMap = {{"CSV", CSV}, {"TSV", TSV}, {"PHYLIP", PHYLIP}};


void Init() //set default values
{
    dist_index = "1"; // CD_MAWS
    output_format = "CSV";
}

int main(int argc, char *argv[])
{
    Init();
    
    int opt;
    while((opt = getopt(argc, argv, "i:d:o:f:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'i':
                if(optarg and optarg[0]) input_file = string(optarg);
                break; 
            case 'd':
                if(optarg and optarg[0]) dist_index = string(optarg);
                break;
            case 'f':
                if(optarg and optarg[0]) output_format = string(optarg);
                break; 
            case 'o':
                if(optarg and optarg[0]) output_file = string(optarg);
                break; 
            case ':':  
                printf("Option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }

    if(input_file.size() == 0)
    {
        cout << "Input file has not been specified\n" << endl;
        return -1;
    }

    if(output_file.size() == 0)
    {
        cout << "Output file has not been specified\n" << endl;
        return -1;
    }

    //if(!working_folder.empty()) inputFile = working_folder + "/" + inputFile;


    cout << "\nExtracting MAWs from files....\n";

    auto start = cloc::now();
    
    maws = GetAllSetsFromOneFile(input_file, taxas, mawmap); //single file format

    if(maws.empty())
    {
        cout << "No data extracted. File might be non-existent" <<endl;
        exit(1);
    }

    sec duration = cloc::now() - start;

    cout << "MAWs extracted. Time taken (sec)--> " << duration.count() << endl;

    int num_of_genes = maws.size();

    vector<double> emptyVec(num_of_genes,0.0);
    for (int i = 0; i < num_of_genes; i++)
    {
        diffMatrix.push_back(emptyVec);
    }

    cout << num_of_genes << " species found\n\n";


    cout << "Calculating distance matrix.....\n\n";

    int distMethod = stoi(dist_index);

    transform(output_format.begin(), output_format.end(),output_format.begin(), ::toupper);
    int outputFileFormat = formatMap[output_format];
    maxMAWlength = maxMAWlen;

    start = cloc::now();
    CalculateDistanceMatrix(maws, mawmap, diffMatrix, num_of_genes, distMethod);
    duration = cloc::now() - start;

    cout << "Distance matrix calculated. Time taken (sec)--> " << duration.count() << endl;

    printMatrix(output_file, taxas, diffMatrix, num_of_genes, distMethod, outputFileFormat);

    cout << "Distance matrix printed...\n " << endl;

    return 0;
}
