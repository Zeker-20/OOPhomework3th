#include <iostream>
#include <cstdlib>
#include <cmath>
#include <windows.h>
using namespace std;
double maxArea = 0.0;
double maxPerimeter = 0.0;
double area_a = 0.0;
double area_b = 0.0;
double area_c = 0.0;
double perim_a = 0.0;
double perim_b = 0.0;
double perim_c = 0.0;
//【编程设计题】 给定m根木棍，每根木棍的长度记为L_i, (3 <= i <= m), 
//下面欲从这m根木棍中选择3根木棍组成周长尽可能最长的三角形、面积尽可能最大的三角形，
//分别输出最大的周长和面积。如果怎么选都无法构成三角形，请直接输出0。
//要求：
//算法具有良好的可读性、稳健性和通用性（适合整数长度，浮点数长度）。
//给出算法的复杂度分析，算法复杂度尽可能越低越好。
//算法设计时采用指针，引用，重载函数，及动态内存申请等C++核心特性。
//输入：
//m = 5
//L = 2 3 4 5 10
//输出：最大周长12，最大面积6(选择3, 4, 5)
//【教材思考题】 结合教材第2章所有案例代码（点击查看），分析解答各案例程序后面的 思考与练习 题目，
//给出必要的Visual Studio程序执行结果，并解释问题原因。


//判断是否为三角形的函数
 int JudgeTriangle(const double &a, const double & b, const double &c)
{
	 if ((a + b > c) && (a + c > b) && (b + c > a))
	 {
		 return 1;
	 }
	 else
		 return 0;
}
double perimeter(const double &a, const double &b, const double&c)
{
	 return (a + b + c);
}
//排序的函数
//int SortBig2Small(int &a, int &b, int &c)//使用引用，并且a>b>c；
//{
//	int *max = new int;
//	int *min = new int;
//	int *mid = new int;
//	if (a > b)
//	{
//		if (a > c)
//		{
//			*max = a;
//			if (b > c)
//			{
//				*min = c;*mid = b;
//			}
//			else
//			{
//				*min = b;*mid = c;
//			}
//		}
//		else
//		{
//			*max = c; *mid = a; *min = b;
//		}
//	}
//	else
//	{
//		if (b > c)
//		{
//			*max = b;
//			if (a > c)
//			{
//				*mid = a; *min = c;
//			}
//			else
//			{
//				*mid = c; *min = a;
//			}
//		}
//		else
//		{
//			*max = c; *mid = b; *min = a;
//		}
//	}
//	a = *max; b = *mid; c = *min;
//	delete max; delete mid; delete min;
//	return 0;
//}
//计算面积的函数
double area(const double &a, const double &b, const double&c)
{
	double p = 0.5*(a + b + c);
	return sqrt(p*(p - a)*(p - b)*(p - c));
}
int cmpfunc(const void* a, const void* b)
{
	return ((*(double*)b) - (*(double*)a));
}
//需要使用指针，引用，重载函数，及动态内存申请
//主程序 输入三角形三边
int searchMaxLength_nlogn(double *len, const int num)
{
	//1. 按照木棍长度从大到小排序
	qsort(len, num, sizeof(len[0]), cmpfunc);
	//2. 构建三角形,输出最大周长
	int flag = 0;
	int i = 0, j = 1, k = 2;
	while (k < num)
	{
		if (JudgeTriangle(len[i], len[j], len[k]))
		{
			double tempPerimeter = perimeter(len[i],len[j],len[k]);
			if (tempPerimeter > maxPerimeter)
			{
				maxPerimeter = tempPerimeter;
				//记录当前边长
				perim_a = len[i];
				perim_b = len[j];
				perim_c = len[k];
			}
			flag= 1;//存在构成三角形的木棍
			break;//找到第一个即可停止搜索

		}
		i++;
		j++;
		k++;
	}
	if (flag== 0)
	{
		return 0;
	}
	else
		return 1;
}
int searchMaxArea_nlogn(double* len, const int num)
{
	//1. 按照木棍长度从大到小排序
	qsort(len, num, sizeof(len[0]), cmpfunc);
    //2. 构建三角形,输出最大面积
	int flag = 0;
	int i = 0, j = 1, k = 2;
	while (k < num)
	{
		if (JudgeTriangle(len[i], len[j], len[k]))
		{
			double tempArea = area(len[i], len[j], len[k]);
			if (tempArea > maxArea)
			{
				maxArea = tempArea;
				area_a = len[i];
				area_b = len[j];
				area_c = len[k];
			}
			flag = 1;//存在构成三角形的木棍
		}
		i++;
		j++;
		k++;
	}
	if (flag == 0)
	{
		return 0;
	}
	else
		return 1;
}

int main()
{
	int m;
	cin >> m;
	// 动态分配内存空间，存储木棍长度
	double *len = new double[m];
	cout << "请依次输入木棍的长度" << endl;
	for (int i = 0; i < m; i++)
	{
		cin >> len[i];
	}

	//SortBig2Small(a, b, c);
	/*if (JudgeTriangle(a, b, c))
	{
	}
	else
		cout << "0" << endl;*/
	int length_success = searchMaxLength_nlogn(len, m);
	if (length_success == 1)
	{
		cout << "最大周长: " << maxPerimeter << " (边长为: " << perim_a << "," << perim_b << "," << perim_c << ")" << endl;
	}
	else
	{
		cout << 0 << endl;
		cout << "当前木棍长度无法构成三角形" << endl;
	}
	int area_success = searchMaxArea_nlogn(len, m);
	if (area_success == 1)
	{
		cout << "最大面积: " << maxArea << " (边长为: " << area_a << "," << area_b << "," << area_c << ")" << endl << endl;
	}
	else
	{
		cout << 0 << endl;
		cout << "提示: 当前木棍长度无法构成任何三角形!" << endl;
	}
	delete[] len;
	system("pause");
	return 0;
}








