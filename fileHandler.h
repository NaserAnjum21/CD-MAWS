#pragma once

#include <bits/stdc++.h>

#include "set.h"
#include "defs.h"

using namespace std;

int maxMAWlen;

vector<Set> GetAllSetsFromOneFile(string fileName, vector<string> &taxas,vector<map<string,char>>& mawmap)
{
    ifstream file(fileName);
    vector<Set> sets;
    string line;

    Set set, emptySet;

    maxMAWlen = 0;

    while (getline(file, line))
    {
        if (line[0] == '>') //line with taxa names as in FASTA format
        {
            line.erase(line.begin());
            set = emptySet;
            set.SetTaxaName(line);
            taxas.push_back(line);
            sets.push_back(set);

            map<string,char> emptyMap;
            mawmap.push_back(emptyMap);

        }
        else if (line.size() > 0 and !sets.empty())
        {
            sets.back().AddElements(line);
            mawmap[mawmap.size()-1][line] = 99;
            maxMAWlen = max(maxMAWlen, (int)line.size());
        }
        
    }

    //MAWs need to be sorted for the set operations to work
    for(int i = 0 ; i < sets.size(); i++)
    {
        sets[i].SortElements();
    }

    return sets;
}