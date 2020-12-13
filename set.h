#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

class Set
{

public:
    vector<string> elements;
    string taxaName;

    Set();
    ~Set();
    Set(const Set &B);
    Set(vector<string> &V);
    Set operator=(const Set &B);

    void SortElements();
    void AddElements(string str);

    void Print();
    void MakeFromFile(string fileName);
    void MakeFromString(vector<string> vec);

    void SetTaxaName(string str);
    string GetTaxaName();

    Set Union(Set &B);
    Set Intersection(Set &B);
    Set Difference(Set &B);
    Set SymmetricDifference(Set &B);

    int Cardinality();
};

Set::Set(const Set &B)
{
    elements.assign(B.elements.begin(), B.elements.end());
    //assign works for any type of vector unlike the assignment operator "="
}

Set::Set(vector<string> &V)
{
    elements.assign(V.begin(), V.end());
}

Set::Set() {}

Set::~Set()
{
    elements.clear();         //still some finite capacity left
    elements.shrink_to_fit(); //underlying storage is removed i.e. no capacity left for the vector
}

Set Set::operator=(const Set &B)
{
    elements.assign(B.elements.begin(), B.elements.end());
    return *this;
}

void Set::SortElements()
{
    sort(elements.begin(), elements.end());
}

void Set::AddElements(string str)
{
    elements.push_back(str);
}

void Set::Print()
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << elements[i] << endl;
    }
}

int Set::Cardinality()
{
    return elements.size();
}

void Set::MakeFromFile(string fileName)
{
    string line;
    ifstream file(fileName);
    int count = 0;
    //while(getline(file,line))
    while (file.peek() != EOF)
    {
        getline(file, line);
        if (count != 0) //ignoring the first line which is the taxa name
        {
            AddElements(line);
        }
        count = 1;
    }
}

void Set::MakeFromString(vector<string> vec)
{
    elements.assign(vec.begin(), vec.end());
}

void Set::SetTaxaName(string str)
{
    taxaName = str;
}

string Set::GetTaxaName()
{
    return taxaName;
}

Set Set::Union(Set &B)
{
    int length = elements.size() + B.elements.size();
    vector<string> uSet(length);
    vector<string>::iterator it;
    it = set_union(elements.begin(), elements.end(), B.elements.begin(), B.elements.end(), uSet.begin());

    uSet.resize(it - uSet.begin());

    Set result(uSet);

    return result;
}

Set Set::Intersection(Set &B)
{
    int length = elements.size() + B.elements.size();
    vector<string> iSet(length);
    vector<string>::iterator it;
    it = set_intersection(elements.begin(), elements.end(), B.elements.begin(), B.elements.end(), iSet.begin());
    iSet.resize(it - iSet.begin());

    Set result(iSet);

    return result;
}

Set Set::Difference(Set &B)
{
    int length = elements.size() + B.elements.size();
    vector<string> dSet(length);
    vector<string>::iterator it;
    it = set_difference(elements.begin(), elements.end(), B.elements.begin(), B.elements.end(), dSet.begin());
    dSet.resize(it - dSet.begin());

    Set result(dSet);

    return result;
}

Set Set::SymmetricDifference(Set &B)
{
    int length = elements.size() + B.elements.size();
    vector<string> sdSet(length);
    vector<string>::iterator it;
    it = set_symmetric_difference(elements.begin(), elements.end(), B.elements.begin(), B.elements.end(), sdSet.begin());
    sdSet.resize(it - sdSet.begin());

    Set result(sdSet);

    return result;
}
