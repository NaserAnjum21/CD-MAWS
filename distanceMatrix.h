#include <bits/stdc++.h>
#include <armadillo>
#include <chrono>

#include "set.h"
#include "fileHandler.h"
#include "defs.h"

using namespace std;
using namespace arma;
using cloc = chrono::system_clock;
using sec = chrono::duration<double>;

vector<frowvec> Vec;
extern double maxMAWlength;

Set GetGlobalUnion(vector<Set> &mawset, int num_of_genes)
{
    Set uset;

    for (int i = 0; i < num_of_genes; i++)
        uset = uset.Union(mawset[i]);

    //uset.Print();

    return uset;
}

void GetVectors(Set global,int num_of_genes, vector<map<string,char>>& mawmap, bool is_weighted)
{
    int N = global.Cardinality();

    for(int i = 0; i < num_of_genes; i++)
    {
        frowvec r = zeros<frowvec>(N);
        Vec.push_back(r);

        for(int j = 0; j < N; j++)
        {
            string maw = global.elements[j];
            if(mawmap[i][maw] == 99) //maw present
            {
                if(is_weighted)
                    Vec[i][j] = 1.0 * maw.size() / maxMAWlength;
                else
                    Vec[i][j] = 1;
            }
             
        }

        mawmap[i].clear();
    }
}


double GetMawCosine(int a,int b)
{
    double ret = norm_dot(Vec[a], Vec[b]);
    return 1.0 - ret;
}



void CalculateDistanceMatrix(vector<Set> &mawset, vector<map<string,char>>& mawmap, vector<vector<double>>& diffMatrix, int num_of_genes, int diffIndex)
{

    Set uSet, iSet, sdSet, a, b, c, globalSet;

    auto start = cloc::now();
    
    globalSet = GetGlobalUnion(mawset, num_of_genes);
    GetVectors(globalSet,num_of_genes,mawmap, false);
    
    sec duration = cloc::now() - start;

    cout << "Vectors created. Time taken (sec)--> " << duration.count() << endl;

    start = cloc::now();

    for (int i = 0; i < num_of_genes; i++)
    {
        for (int j = 0; j < i; j++)
        {
            
            switch (diffIndex) //more distance measures can be added
            {
            case CD_MAWS:
            {

                diffMatrix[i][j] = diffMatrix[j][i] = GetMawCosine(i,j);

                break;
            }
            }
        }
    }

    duration = cloc::now() - start;
    
    cout << "Distance matrix calculated. Time taken (sec)--> " << duration.count() << endl;
}

void printMatrix(string output_file, vector<string> taxas, vector<vector<double>>& diffMatrix, int num_of_genes, int distIndex, int formatIndex)
{
    string outFile = output_file;
    switch (formatIndex) //diferent output format for different file format
    {
    case CSV: // CSV dist matrix used as input to Dendropy's newick tree file generation
    {

        ofstream out;
        out.open(outFile);

        for (int i = 0; i < num_of_genes; i++)
            out << "," << taxas[i];
        out << endl;

        for (int i = 0; i < num_of_genes; i++)
        {
            out << taxas[i];

            for (int j = 0; j < num_of_genes; j++)
                out << "," << diffMatrix[i][j];

            out << endl;
        }

        if (out.is_open())
            out.close();

        break;
    }

    case PHYLIP:
    {

        ofstream out;
        out.open(outFile);

        out << num_of_genes << endl;

        for (int i = 0; i < num_of_genes; i++)
        {
            out << taxas[i];

            for (int j = 0; j < num_of_genes; j++)
                out << "\t" << diffMatrix[i][j];

            out << endl;
        }

        if (out.is_open())
            out.close();

        break;
    }

    case TSV:
    {

        ofstream out;
        out.open(outFile);

        for (int i = 0; i < num_of_genes; i++)
            for (int j = i + 1; j < num_of_genes; j++)
                out << taxas[i] << "\t" << taxas[j] << "\t" << diffMatrix[i][j] << endl;

        if (out.is_open())
            out.close();

        break;
    }
    }
}

