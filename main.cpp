#include <iostream>
#include <time.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "GA.h"

using namespace std;

int main()
{
    srand(time(NULL));
    vector<vector<int>> Chrom = {{0, 1, 1, 0, 0}, {1, 0, 0, 1, 0}, {1, 1, 0, 0, 1}, {1, 0, 0, 0, 1}};
    vector<int> ObjV = {1, 2, 3, 4};
    double px = 0.1;
    double pm = 0.1;

    cout << "Chrom" << endl;
    for (int i = 0; i < Chrom.size(); i++)
    {
        for (int j = 0; j < Chrom[0].size(); j++)
        {
            cout << Chrom[i][j] << " ";
        }
        cout << endl;
    }

    //ranking函数测试
    vector<double> FitnV = ranking(ObjV);
    cout << "ranking" << endl;
    for (int i = 0; i < FitnV.size(); i++)
    {
        cout << FitnV[i] << " ";
    }
    cout << endl
         << endl;
    cout << "select" << endl;
    vector<vector<int>> SelCh = select(Chrom, FitnV);
    for (int i = 0; i < SelCh.size(); i++)
    {
        for (int j = 0; j < SelCh[0].size(); j++)
        {
            cout << SelCh[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "recombin" << endl;
    SelCh = recombin(SelCh, px);
    for (int i = 0; i < SelCh.size(); i++)
    {
        for (int j = 0; j < SelCh[0].size(); j++)
        {
            cout << SelCh[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "mut" << endl;
    SelCh = mut(SelCh, pm);
    for (int i = 0; i < SelCh.size(); i++)
    {
        for (int j = 0; j < SelCh[0].size(); j++)
        {
            cout << SelCh[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "reins" << endl;
    vector<int> ObjVSel = {4, 3, 2, 1};
    pair<vector<vector<int>>, vector<int>> res = reins(Chrom, SelCh, ObjV, ObjVSel);
    for (int i = 0; i < res.first.size(); i++)
    {
        for (int j = 0; j < res.first[0].size(); j++)
        {
            cout << res.first[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < res.second.size(); i++)
    {
        cout << res.second[i] << " ";
    }
    cout << endl;

    return 0;
}
