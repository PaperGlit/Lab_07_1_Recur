#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			a[i][j] = Low + rand() % (High - Low + 1);
			Create(a, rowCount, colCount, Low, High, i, j + 1);
		}
		else
			Create(a, rowCount, colCount, Low, High, i + 1, 0);
	}
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			cout << setw(4) << a[i][j];
			Print(a, rowCount, colCount, i, j + 1);
		}
		else
		{
			cout << endl;
			Print(a, rowCount, colCount, i + 1, 0);
		}
	}
}

void Change(int** a, const int col1, const int col2, const int rowCount, int tmp, int j)
{
	if (j < rowCount)
	{
		tmp = a[j][col1];
		a[j][col1] = a[j][col2];
		a[j][col2] = tmp;
		Change(a, col1, col2, rowCount, tmp, j + 1);
	}
}

void Sort(int** a, const int rowCount, const int colCount, int i0, int i1)
{
	if (i0 < colCount - 1)
	{
		if (i1 < colCount - i0 - 1)
		{
			if ((a[0][i1] < a[0][i1 + 1])
				||
				(a[0][i1] == a[0][i1 + 1] &&
					a[1][i1] > a[1][i1 + 1])
				||
				(a[0][i1] == a[0][i1 + 1] &&
					a[1][i1] == a[1][i1 + 1] &&
					a[2][i1] > a[2][i1 + 1]))
				Change(a, i1, i1 + 1, rowCount, 0, 0);
			Sort(a, rowCount, colCount, i0, i1 + 1);
		}
		else
			Sort(a, rowCount, colCount, i0 + 1, 0);
	}
}

void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			if (a[i][j] % 2 == 0 && i + j % 8 != 0)
			{
				S += a[i][j];
				k++;
				a[i][j] = 0;
			}
			Calc(a, rowCount, colCount, S, k, i, j + 1);
		}
		else
			Calc(a, rowCount, colCount, S, k, i + 1, 0);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int Low = 7;
	int High = 62;
	int rowCount = 7;
	int colCount = 6;
	int** Q = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		Q[i] = new int[colCount];
	Create(Q, rowCount, colCount, Low, High, 0, 0);
	Print(Q, rowCount, colCount, 0, 0);
	cout << endl;
	Sort(Q, rowCount, colCount, 0, 0);
	Print(Q, rowCount, colCount, 0, 0);
	cout << endl;
	int S = 0;
	int k = 0;
	Calc(Q, rowCount, colCount, S, k, 0, 0);
	cout << "S = " << S << endl;
	cout << "k = " << k << endl;
	cout << endl;
	Print(Q, rowCount, colCount, 0, 0);
	cout << endl;
	for (int i = 0; i < rowCount; i++)
		delete[] Q[i];
	delete[] Q;
	return 0;
}