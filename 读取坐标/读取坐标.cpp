// 读取坐标.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <fstream>
#include <iostream>
#include <vector>
#include<string>
#include<cassert>
using namespace std;



void calculateDistance_(int(*loc)[2], double(*m)[10], int num) {
	for (int i = 0; i < num; i++) {
		int x1 = loc[i][0], y1 = loc[i][1];
		for (int j = 0; j < num; j++) {
			int x2 = loc[j][0], y2 = loc[j][1];
			m[i][j] = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}
	}
}

//传入坐标矩阵得到距离矩阵
vector<vector<double> > calculate_distance(const vector<vector<double> >& loction)
{
	int city_number = loction.size();
	vector<vector<double> > distance_matrix(city_number, vector<double>(city_number, -1));

	for (int i = 0; i < city_number; ++i)
	{
		double x1 = loction[i][0], y1 = loction[i][1];
		for (int j = 0; j < city_number; ++j)
		{
			double x2 = loction[j][0], y2 = loction[j][1];
			distance_matrix[i][j] = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}
	}
	return distance_matrix;
}


vector<vector<double> > loction;

void read_txt(string s) {
	ifstream file;
	vector<double> each_point(2, -1);
	file.open(s);
	for (int i = 0; !file.eof(); i++)
	{
		file >> each_point[0] >> each_point[1];
		loction.push_back(each_point);
	}
	file.close();
}

int main()
{
	//vector<vector<int> > loction;
	string s = "data.txt";
	read_txt(s);
	for (int i = 0; i < loction.size(); ++i)
	{
		cout << loction[i][0] << " , " << loction[i][1] << endl;
	}

	vector<vector<double> > ivec = calculate_distance(loction);
	assert(ivec.size() == ivec[0].size());
	for (int i = 0; i < ivec.size(); i++) {
		for (int j = 0; j < ivec[0].size(); j++) {
			cout << ivec[i][j] << " ";
		}
		cout << endl;
	}





    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
