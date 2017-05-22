#include "GA.h"

using namespace std;

//TODO: 对每个函数进行函数说明
//TODO: 输入参数更换成模板

/*按照降序排列*/
bool operator<(const node &a, const node &b)
{
	return a.date > b.date;
}

double sum(vector<double> RFun, int i, int j)
{
	double result = 0;
	for (int index = i; index <= j; index++)
	{
		result = result + RFun[index];
	}
	return result;
}

//ranking 函数
vector<double> ranking(vector<int> ObjV)
{
	int Nind = ObjV.size();
	//为了排序方便返回索引, 构造一个结构体

	vector<node> ObjVSub(Nind);
	for (int i = 0; i < Nind; i++)
	{
		ObjVSub[i].date = ObjV[i];
		ObjVSub[i].No = i;
	}

	vector<double> RFun(Nind);
	vector<int> FitnVIndex;

	//计算适应度的中间变量
	for (int i = 0; i < Nind; i++)
	{
		RFun[i] = 2 * (double)(i) / (double)(Nind - 1);
	}
	//降序排列
	sort(ObjVSub.begin(), ObjVSub.end());

	vector<node> ix(Nind);
	for (int i = 0; i < Nind; i++)
	{
		ix[i].date = ObjVSub[i].No;
		ix[i].No = i;
	}
	vector<node> Sorted = ObjVSub;

	//计算不相同元素的索引
	for (int i = 0; i < Nind - 1; i++)
	{
		if (Sorted[i].date != Sorted[i + 1].date)
		{
			FitnVIndex.push_back(i);
		}
	}
	FitnVIndex.push_back(Nind - 1);

	//double sumRFun = 0;
	//for (int i = 0; i <= FitnVIndex[0]; i++)
	//{
	//	sumRFun = sumRFun + RFun[i];
	//}
	vector<double> FitnVSub(Nind);
	//for (int i = 0; i <= FitnVIndex[0]; i++)
	//{
	//	FitnVSub[i] = sumRFun / (double)(FitnVIndex[0] + 1);
	//}

	//int i = FitnVIndex[0] + 1;

	int index = 0;
	int iWhile = 0;
	while (iWhile <= FitnVIndex.size() - 1)
	//for (int j = FitnVIndex[0]; j <= FitnVIndex[FitnVIndex.size() - 1];j++)
	{
		int j = FitnVIndex[iWhile++];
		FitnVSub[j] = sum(RFun, index, j) / (double)(j - index + 1);
		if (index != j)
		{
			for (int i = index; i < j; i++)
			{
				FitnVSub[i] = FitnVSub[j];
			}
		}
		double sumLook = sum(RFun, index, j);
		index = j + 1;
	}

	sort(ix.begin(), ix.end());
	vector<double> FitnV(Nind);
	for (int i = 0; i < Nind; i++)
	{
		FitnV[i] = FitnVSub[ix[Nind - i - 1].No];
	}
	return FitnV;
}

//select函数
vector<double> cumsum(vector<double> FitnV)
{
	for (int i = 1; i < FitnV.size(); i++)
	{
		FitnV[i] = FitnV[i - 1] + FitnV[i];
	}
	return FitnV;
}

//矩阵转置
vector<vector<double>> transpose(vector<vector<double>> Matrix)
{
	vector<vector<double>> MatrixRes(Matrix[0].size(), vector<double>(Matrix.size()));
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix[0].size(); j++)
		{
			MatrixRes[j][i] = Matrix[i][j];
		}
	}
	return MatrixRes;
}

vector<int> sus(vector<double> FitnV, int NSel)
{
	int Nind = FitnV.size();
	vector<double> cumfit = cumsum(FitnV);
	vector<double> trials(Nind);
	for (int i = 0; i < Nind; i++)
	{
		trials[i] = cumfit[i] / (double)NSel * ((double)rand() / RAND_MAX + i);
	}
	vector<vector<double>> Mf, Mt;
	for (int i = 0; i < Nind; i++)
	{
		Mf.push_back(cumfit);
		Mt.push_back(trials);
	}
	Mf = transpose(Mf);

	vector<vector<bool>> MtandMf1(Nind, vector<bool>(Nind));
	vector<vector<bool>> MtandMf2(Nind, vector<bool>(Nind));
	vector<vector<double>> MfFind(Nind, vector<double>(Nind));
	vector<vector<bool>> ans(Nind, vector<bool>(Nind));
	vector<int> NewChrIx;
	for (int i = 0; i < Nind; i++)
	{
		for (int j = 0; j < Nind; j++)
		{
			if (Mt[i][j] < Mf[i][j])
			{
				MtandMf1[i][j] = true;
			}
			else
			{
				MtandMf1[i][j] = false;
			}

			if (i == 0)
			{
				MfFind[i][j] = 0;
			}
			else
			{
				MfFind[i][j] = Mf[i - 1][j];
			}

			if (MfFind[i][j] <= Mt[i][j])
			{
				MtandMf2[i][j] = true;
			}
			else
			{
				MtandMf2[i][j] = false;
			}

			if (MtandMf1[i][j] && MtandMf2[i][j])
			{
				ans[i][j] = true;
			}
			else
			{
				ans[i][j] = false;
			}

			if (ans[i][j] == true)
			{
				NewChrIx.push_back(i);
			}
		}
	}
	vector<node> sortRand(NSel);
	for (int i = 0; i < NSel; i++)
	{
		sortRand[i].date = (double)rand() / RAND_MAX;
		sortRand[i].No = i;
	}
	sort(sortRand.begin(), sortRand.end());
	vector<int> NewChrIxRes(NSel);
	for (int i = 0; i < NewChrIx.size(); i++)
	{
		NewChrIxRes[i] = NewChrIx[sortRand[NSel - i - 1].No];
	}
	return NewChrIxRes;
}

vector<vector<int>> select(vector<vector<int>> Chrom, vector<double> FitnV)
{
	int Nind = Chrom.size();
	int Length = Chrom[0].size();
	int GGAP = 1;
	int NSel = Nind;
	vector<vector<int>> SelCh(Nind, vector<int>(Length));
	vector<int> ChrIx = sus(FitnV, NSel);
	for (int i = 0; i < Nind; i++)
	{
		for (int j = 0; j < Length; j++)
		{
			SelCh[i][j] = Chrom[ChrIx[i]][j];
		}
	}
	return SelCh;
}

//交叉函数
vector<int> cumsumInt(vector<int> FitnV)
{
	for (int i = 1; i < FitnV.size(); i++)
	{
		FitnV[i] = FitnV[i - 1] + FitnV[i];
	}
	return FitnV;
}

vector<vector<int>> xovmp(vector<vector<int>> OldChrom, double Px, int Npt, int Rs)
{
	int Nind = OldChrom.size();
	int Lind = OldChrom[0].size();
	int Xops = Nind / 2;
	vector<int> DoCross(Xops);
	for (int i = 0; i < Xops; i++)
	{
		if ((double)rand() / RAND_MAX < Px)
		{
			DoCross[i] = 1;
		}
		else
		{
			DoCross[i] = 0;
		}
	}
	vector<int> odd;
	vector<int> even;
	int i = 0;
	while (i < Nind - 1)
	{
		odd.push_back(i);
		even.push_back(i + 1);
		i = i + 2;
	}
	vector<vector<int>> Mask(odd.size(), vector<int>(Lind, 1));
	for (int i = 0; i < Mask.size(); i++)
	{
		Mask[i] = cumsumInt(Mask[i]);
	}
	vector<vector<int>> xsites(Mask.size(), vector<int>(2));
	for (int i = 0; i < Mask.size(); i++)
	{
		xsites[i][0] = Mask[i][Lind - 1];
	}
	for (int i = 0; i < Mask.size(); i++)
	{
		xsites[i][1] = (xsites[i][0] + ((int)(Mask[i][Nind] * (double)rand() / RAND_MAX + 1) * DoCross[i] - 1)) % (Mask[i][Lind - 1]) + 1;
	}
	vector<vector<int>> index1(Nind, vector<int>(Lind));
	vector<vector<int>> index2 = index1;
	for (int i = 0; i < odd.size(); i++)
	{
		for (int j = 0; j < Lind; j++)
		{
			if (xsites[i][0] < Mask[i][j])
			{
				index1[i][j] = 1;
			}
			else
			{
				index1[i][j] = 0;
			}

			if (xsites[i][1] < Mask[i][j])
			{
				index2[i][j] = 1;
			}
			else
			{
				index2[i][j] = 0;
			}
			if (index1[i][j] == index2[i][j])
			{
				Mask[i][j] = 1;
			}
			else
			{
				Mask[i][j] = 0;
			}
		}
	}
	vector<vector<int>> NewChrom = OldChrom;
	for (int i = 0; i < odd.size(); i++)
	{
		for (int j = 0; j < Lind; j++)
		{
			NewChrom[odd[i]][j] = OldChrom[odd[i]][j] * Mask[i][j] + OldChrom[even[i]][j] * (1 - Mask[i][j]);
			NewChrom[even[i]][j] = OldChrom[odd[i]][j] * (1 - Mask[i][j]) + OldChrom[even[i]][j] * (Mask[i][j]);
		}
	}
	if (Nind % 2)
	{
		NewChrom = OldChrom;
	}

	return NewChrom;
}

vector<vector<int>> xovsp(vector<vector<int>> OldChrom, double XOVR)
{
	return xovmp(OldChrom, XOVR, 1, 0);
}

vector<vector<int>> recombin(vector<vector<int>> Chrom, double px)
{
	int Nind = Chrom.size();
	Chrom = xovsp(Chrom, px);
	return Chrom;
}

//变异函数
vector<vector<int>> mut(vector<vector<int>> OldChrom, double pm)
{
	int Nind = OldChrom.size();
	int Lind = OldChrom[0].size();
	vector<vector<int>> BaseM(Nind, vector<int>(Lind, 2));
	vector<vector<int>> NewChrom = OldChrom;
	int randNum = 0;
	for (int i = 0; i < Nind; i++)
	{
		for (int j = 0; j < Lind; j++)
		{
			if ((double)rand() / RAND_MAX < pm)
			{
				randNum = 1;
			}
			else
			{
				randNum = 0;
			}
			NewChrom[i][j] = (OldChrom[i][j] + randNum * (int)(((double)rand() / RAND_MAX) + 1)) % (BaseM[i][j]);
		}
	}
	return NewChrom;
}
int minNum(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}
int maxNum(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

pair<vector<vector<int>>, vector<int>> reins(vector<vector<int>> Chrom, vector<vector<int>> SelCh, vector<int> ObjVCh, vector<int> ObjVSel)
{
	int NIND = Chrom.size();
	int NvarP = Chrom[0].size();
	int NSEL = SelCh.size();
	int NvarO = SelCh[0].size();
	int INSR = 1;
	int NIns = minNum(maxNum((int)(INSR * NSEL + .5), 1), NIND);
	vector<node> sortObjVCh(ObjVCh.size());
	vector<node> sortObjVSel(ObjVSel.size());
	for (int i = 0; i < ObjVCh.size(); i++)
	{
		sortObjVCh[i].date = ObjVCh[i];
		sortObjVSel[i].date = ObjVSel[i];
		sortObjVCh[i].No = i;
		sortObjVSel[i].No = i;
	}
	sort(sortObjVCh.begin(), sortObjVCh.end());
	for (int i = 0; i < NIND; i++)
	{
		for (int j = 0; j < NvarP; j++)
		{
			Chrom[sortObjVCh[i].No][j] = SelCh[i][j];
		}
		ObjVCh[sortObjVCh[i].No] = ObjVSel[i];
	}

	pair<vector<vector<int>>, vector<int>> result;
	result.first = Chrom;
	result.second = ObjVCh;
	return result;
}
