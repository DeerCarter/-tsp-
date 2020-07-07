// 模拟退火.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include<cmath>
#include <random>
#include <cassert>
using namespace std;

// 城市之间的坐标
vector<vector<double> > loction;   

// 外层循环的次数
int out_count = 500;

// 内层循环的次数
int in_count = 10;

// 距离矩阵
vector<vector<double> > distance_matrix;

// 设置初始温度 
double init_tem = 50000;

// 解的邻域的大小
int neibor_numbers = 500;

// 读取记录城市之间坐标的txt文件
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

// 根据坐标得到距离矩阵
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

// 初始解的获取
vector<int> get_init_result(int n) {
	vector<int> init_result;
	set<int> set1;
	int count = 0;
	while (count < n) {
		int a = rand() % n;
		if (set1.find(a) == set1.end()) {
			init_result.push_back(a + 1);
			set1.insert(a);
			count++;
		}
	}
	return init_result;
}

// 计算适应度， 参数是某条路径 和 距离矩阵  TSP问题 以路径和最短为最优
double fitness(const vector<int>& result, const vector<vector<double> >& ivec)
{
	double num = 0;
	for (unsigned int i = 0; i < result.size() - 1; i++)
	{
		num += ivec[result[i] - 1][result[i + 1] - 1];
		//cout << "num: " << num << " ";
	}
	num += ivec[result[result.size() - 1] - 1][result[0] - 1];
	return num;
}
void display_single(const vector<int>& vec) {
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << endl;
}


// 根据初始解生成邻域  邻域的大小为neibor_n
vector<vector<int> > generate_neibor(vector<int> result, const int& neibor_n)
{

	// 随机交换某两个位置 得到新的解
	// 产生两个0到 n-1 的 随机数作为下标  交换这两个下标的位置 
	int n = result.size();

	vector <vector<int> > neibor_result;
	for (int i = 0; i < neibor_n; i++) {
		int a1 = rand() % n;
		int a2 = rand() % n;
		vector<int> cur_result = result;
		swap(cur_result[a1], cur_result[a2]);
		neibor_result.push_back(cur_result);
	}

	return neibor_result;
}

int main()
{
	std::cout << "Hello World!\n";
	string s = "data.txt";
	read_txt(s);
	//
	distance_matrix = calculate_distance(loction);
	vector<int> init_result = get_init_result(distance_matrix.size());
	display_single(init_result);
	// 初始的适应度
	double init_fit = fitness(init_result, distance_matrix);

    std::cout << "Hello World!\n";
	// 随机选择一个解i 计算适应度  设置迭代次数 初始温度 
	// 刚开始的最优解是初始解
	vector<int> best_result = init_result;

	for (int i = 0; i < out_count; ++i) {
		
		int same_count = 0;
		std::cout << fitness(init_result, distance_matrix) << endl;
		while (same_count < in_count) {
			// 生成大小为500 的初始解的邻域
			vector<vector<int> > result_neibor = generate_neibor(init_result, neibor_numbers);
			// 当前解的适应度
			double start_fit = fitness(init_result, distance_matrix);
			// 小于 内层循环没有达到平衡  在邻域中随机选择一个解
			vector<int>  next_result = result_neibor[rand() % neibor_numbers];
			double next_fit = fitness(next_result, distance_matrix);
			if (next_fit < fitness(best_result, distance_matrix)) {
				//更新当前最优解
				best_result = next_result;
				same_count = 0;
			}
			if (next_fit < start_fit)
			{
				//std::cout << "小于： " << next_fit << endl;
				init_result = next_result;
				
			}
			// 大于 按照准则的概率接受
			else if (next_fit > start_fit)
			{
				double deltE = start_fit - next_fit;
				// 		
				double p = exp((deltE / init_tem));
				//cout << "接受差解的概率是" << p << endl;
				// 生成0-1之间的随机数
				std::random_device e;
				std::uniform_real_distribution<double> u(0, 1);
				double suiji = u(e);
				if (suiji < p) {
					init_result = next_result;
				}
				same_count++;
			}
		}
		// 在该温度下达到平衡
		cout << init_tem << "：  " << fitness(best_result, distance_matrix);
		init_tem = init_tem * 0.95;
	}
	// 进入外层循环

	// 是否再内层循环中达到平衡

	// 否 在邻域中选择一个解j 计算 适应度

	// 如果 
	cout << "最终 ：  " << fitness(best_result, distance_matrix);
	return 0;
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
