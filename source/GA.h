#ifndef GA_H
#define GA_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

typedef struct
{
	double date;
	int No;
} node;

double sum(vector<double> RFun, int i, int j);
vector<double> ranking(vector<int> ObjV);
vector<double> cumsum(vector<double> FitnV);
vector<vector<double>> transpose(vector<vector<double>> Matrix);
vector<int> sus(vector<double> FitnV, int NSel);
vector<vector<int>> select(vector<vector<int>> Chrom, vector<double> FitnV);
vector<int> cumsumInt(vector<int> FitnV);
vector<vector<int>> xovmp(vector<vector<int>> OldChrom, double Px, int Npt, int Rs);
vector<vector<int>> xovsp(vector<vector<int>> OldChrom, double XOVR);
vector<vector<int>> recombin(vector<vector<int>> Chrom, double px);
vector<vector<int>> mut(vector<vector<int>> OldChrom, double pm);
int minNum(int a, int b);
int maxNum(int a, int b);
pair<vector<vector<int>>, vector<int>> reins(vector<vector<int>> Chrom, vector<vector<int>> SelCh, vector<int> ObjVCh, vector<int> ObjVSel);


class GA
{

};

#endif
