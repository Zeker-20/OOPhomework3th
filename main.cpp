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
//���������⡿ ����m��ľ����ÿ��ľ���ĳ��ȼ�ΪL_i, (3 <= i <= m), 
//����������m��ľ����ѡ��3��ľ������ܳ���������������Ρ�������������������Σ�
//�ֱ���������ܳ�������������ôѡ���޷����������Σ���ֱ�����0��
//Ҫ��
//�㷨�������õĿɶ��ԡ��Ƚ��Ժ�ͨ���ԣ��ʺ��������ȣ����������ȣ���
//�����㷨�ĸ��Ӷȷ������㷨���ӶȾ�����Խ��Խ�á�
//�㷨���ʱ����ָ�룬���ã����غ���������̬�ڴ������C++�������ԡ�
//���룺
//m = 5
//L = 2 3 4 5 10
//���������ܳ�12��������6(ѡ��3, 4, 5)
//���̲�˼���⡿ ��Ͻ̲ĵ�2�����а������루����鿴������������������������ ˼������ϰ ��Ŀ��
//������Ҫ��Visual Studio����ִ�н��������������ԭ��


//�ж��Ƿ�Ϊ�����εĺ���
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
//����ĺ���
//int SortBig2Small(int &a, int &b, int &c)//ʹ�����ã�����a>b>c��
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
//��������ĺ���
double area(const double &a, const double &b, const double&c)
{
	double p = 0.5*(a + b + c);
	return sqrt(p*(p - a)*(p - b)*(p - c));
}
int cmpfunc(const void* a, const void* b)
{
	return ((*(double*)b) - (*(double*)a));
}
//��Ҫʹ��ָ�룬���ã����غ���������̬�ڴ�����
//������ ��������������
int searchMaxLength_nlogn(double *len, const int num)
{
	//1. ����ľ�����ȴӴ�С����
	qsort(len, num, sizeof(len[0]), cmpfunc);
	//2. ����������,�������ܳ�
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
				//��¼��ǰ�߳�
				perim_a = len[i];
				perim_b = len[j];
				perim_c = len[k];
			}
			flag= 1;//���ڹ��������ε�ľ��
			break;//�ҵ���һ������ֹͣ����

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
	//1. ����ľ�����ȴӴ�С����
	qsort(len, num, sizeof(len[0]), cmpfunc);
    //2. ����������,���������
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
			flag = 1;//���ڹ��������ε�ľ��
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
	// ��̬�����ڴ�ռ䣬�洢ľ������
	double *len = new double[m];
	cout << "����������ľ���ĳ���" << endl;
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
		cout << "����ܳ�: " << maxPerimeter << " (�߳�Ϊ: " << perim_a << "," << perim_b << "," << perim_c << ")" << endl;
	}
	else
	{
		cout << 0 << endl;
		cout << "��ǰľ�������޷�����������" << endl;
	}
	int area_success = searchMaxArea_nlogn(len, m);
	if (area_success == 1)
	{
		cout << "������: " << maxArea << " (�߳�Ϊ: " << area_a << "," << area_b << "," << area_c << ")" << endl << endl;
	}
	else
	{
		cout << 0 << endl;
		cout << "��ʾ: ��ǰľ�������޷������κ�������!" << endl;
	}
	delete[] len;
	system("pause");
	return 0;
}








