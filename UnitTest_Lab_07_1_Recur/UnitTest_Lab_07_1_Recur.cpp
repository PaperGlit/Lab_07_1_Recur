#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07_1_Recur/Lab_07_1_Recur.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void TestLoop(int** a, int** b, const int rowCount, const int colCount, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			Assert::AreEqual(a[i][j], b[i][j]);
			TestLoop(a, b, rowCount, colCount, i, j + 1);
		}
		else
			TestLoop(a, b, rowCount, colCount, i + 1, 0);
	}
}

void TestChange(int** a, const int col1, const int col2, const int rowCount, int tmp, int j)
{
	if (j < rowCount)
	{
		tmp = a[j][col1];
		a[j][col1] = a[j][col2];
		a[j][col2] = tmp;
		TestChange(a, col1, col2, rowCount, tmp, j + 1);
	}
}

void TestSort(int** a, const int rowCount, const int colCount, int i0, int i1)
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
				TestChange(a, i1, i1 + 1, rowCount, 0, 0);
			TestSort(a, rowCount, colCount, i0, i1 + 1);
		}
		else
			TestSort(a, rowCount, colCount, i0 + 1, 0);
	}
}

void TestCalc(int** a, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			if (a[i][j] % 2 == 0 && i + j % 8 != 0)
			{
				S += a[i][j];
				k++;
			}
			TestCalc(a, rowCount, colCount, S, k, i, j + 1);
		}
		else
			TestCalc(a, rowCount, colCount, S, k, i + 1, 0);
	}
}

namespace UnitTestLab071Recur
{
	TEST_CLASS(UnitTestLab071Recur)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			srand((unsigned)time(NULL));
			int Low = 7;
			int High = 62;
			int w, x, y, z;
			int rowCount = 7;
			int colCount = 6;
			int** a = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				a[i] = new int[colCount];
			Create(a, rowCount, colCount, Low, High, 0, 0);
			int** b = a;
			TestSort(a, rowCount, colCount, 0, 0);
			Sort(b, rowCount, colCount, 0, 0);
			TestLoop(a, b, rowCount, colCount, 0, 0);
			TestCalc(a, rowCount, colCount, w, x, 0, 0);
			Calc(b, rowCount, colCount, y, z, 0 , 0);
			Assert::AreEqual(w, y);
			Assert::AreEqual(x, z);
		}
	};
}
