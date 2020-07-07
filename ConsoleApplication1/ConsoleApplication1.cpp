// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include<cmath>
#include <random>
#include <cassert>
#include <ctime>
using namespace std;

vector<vector<double> > loction;   // 城市之间的坐标

// 131 个城市 
// 迭代500次 初温100000  每次下降*0.98

// berlin18 
// 迭代100次  初温50000

// 31个城市 迭代200次 初温100000

//131 迭代200次 初温 30000
// 迭代的次数
int diedaicount = 200;

// 模拟退火的初温
double kt = 50000;

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


// // 根据距离矩阵 贪心生成初始解
// 不是在一个已经存在的空间进行计算的 所以不能返回引用
vector<int> init(const int& n,const vector<vector<double> >& ivc)
{
	vector<int> init_result;
	set<int> index_set;
	for (unsigned int i = 0; index_set.size()< n; ) {
		index_set.insert(i);
		init_result.push_back(i+1);
		double min_value = 10000000;
		int min_index = 0;
		for (int j = 0; j < n; j++) {	
			if (i == j)
				continue;
			if (index_set.count(j) == 0) {				
				if (ivc[i][j] < min_value) {					
					min_value = ivc[i][j];
					//cout << min_value << " ";
					min_index = j;
				}
			}
		}
		i = min_index;
		//cout << endl;
	}
	return init_result;
}

// 随机获取初始解
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
	for (unsigned int i = 0; i < result.size()-1; i++)
	{		
		num += ivec[result[i] - 1][result[i + 1] - 1];
		//cout << "num: " << num << " ";
	}
	num += ivec[result[result.size() - 1] - 1][result[0] - 1];
	return num;
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

// 对当前最优解进行扰动 产生新的邻域
vector<vector<int> > disturbance_neibor(const vector<int>& cur_result,const int& num) {
	// 扰动的操作要比获取邻域的操作要大  交换一半？
	int n = cur_result.size();
	int change_number = n/2;
	change_number = (change_number % 2 == 0)?change_number:change_number - 1;
	vector<vector<int> > distur_result;
	// 存储要交换的下标
	vector<int> change_index;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < change_number; ++j) {
			int a = rand() % n;
			change_index.push_back(a);
		}
		vector<int> pre_result = cur_result;
		for (int k = 0; k < change_number; k+=2) {
			swap(pre_result[change_index[k]], pre_result[change_index[k + 1]]);
		}
		distur_result.push_back(pre_result);
	}
	return distur_result;
}


// 遍历二维数组 查看结果
void displayer(const vector<vector<int> >& erweivector) {
	
	for (unsigned int i = 0; i < erweivector.size(); i++) {
		for (unsigned int j = 0; j < erweivector[0].size(); j++) {
			std::cout << erweivector[i][j] << " ";
		}
		std::cout << endl;
	}
}

// 遍历一维数组 查看结果
void display_single(const vector<int>& vec) {
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << endl;
}

int main()
{
	string s = "berlin18.txt";
	read_txt(s);
	
	//readtxt("simple.txt");
	int n = loction.size();  // n个城市
	/*int des2[10][10] = { {0,5,2,7,8,10,9,2,5,1},{5,0,5,6,7,8,10,2,1,8},{2,5,0,19,18,18,9,6,2,7},{7,6,19,0,17,16,17,15,23,10},{8,7,18,17,0,15,12,11,10,9},
	{10,8,18,16,15,0,15,23,28},{9,10,9,17,12,18,0,10,11,8},{2,2,6,15,11,15,10,0,20,25},{5,1,2,23,10,23,11,20,0,5},{1,8,7,10,9,28,8,25,5,0} };*/
	// ivec 是距离矩阵
	vector<vector<double> > ivec = calculate_distance(loction);
	assert(ivec.size() == ivec[0].size());
	// 每次生成的邻域的大小
	int neibor_number = 500;

	// 判断如果连续多少次邻域内的最优解没发生变化，则得到了局部最优 需要进行扰动
	int local_same_count = 20;

	// 全局最优解
	vector<int> global_best_result;


	// TSP问题 生成初始解 
	vector<int> init_result;
	init_result = init(n,ivec);
	// 随机生成初始解
	//init_result = get_init_result(n);
	// 查看初始解
	std::cout << " The init result： " << endl;
	display_single(init_result);
	// 计算初始解的适应度
	double first_num = fitness(init_result, ivec);
	std::cout << "初始解的路径长度是： " << first_num << endl;
	// 全局最优解 初始为初始解
	vector<int> final_result;
	final_result = init_result;

	// 程序开始时间和结束时间
	clock_t startTime, endTime;

	startTime = clock();
	// 开始迭代
	for (int count = 0; count < diedaicount; ++count)
	{
		//// 计算每次迭代开始的解的距离
		//double first_num = fitness(init_result, ivec);
		//std::cout << "本次迭代初始解的适应度是： " << first_num << endl;

		// 这应该有一层循环 判断是否找到该解的局部最优 
		int same_count = 0; // 这个参数是计算同一个解出现的次数  如果连续多次出现， 说明进入局部最优
		
		vector<int> neibor_best_result;  //局部最优解
		double local_fit;  // 局部最优解的适应度

		while (same_count < local_same_count) {
			// 本次迭代的初始解的适应度
			double init_fit = fitness(init_result, ivec);
			// 根据本次迭代的初始解 生成邻域
			vector<vector<int> > neibor_result = generate_neibor(init_result, neibor_number);
			neibor_result.push_back(init_result);
			// 查看邻域的内容
			/*cout << " The neibour results: " << endl;
			displayer(neibor_result);*/

			// 对邻域内的每个解 计算适应度？
			int num_neibor_result = neibor_result.size();
			vector<double> neibor_fit(num_neibor_result, -1);
			for (int i = 0; i < num_neibor_result; ++i)
			{
				neibor_fit[i] = fitness(neibor_result[i], ivec);
			}
			// 查看邻域内每个解的适应度
			/*cout << " The each neibor result's fitness: " << endl;
			display_single(neibor_fit);*/

			// 对于邻域内的每个解 找到邻域内的局部最优
			int min_index = 0;
			for (int i = 0; i < num_neibor_result; i++)
			{
				if (neibor_fit[i] < neibor_fit[min_index]) {
					min_index = i;
				}
			}
			//  局部最优解找到了
			neibor_best_result = neibor_result[min_index];
			// 局部最优解的路径长度
			local_fit = neibor_fit[min_index];
			if (local_fit == init_fit) {
				// 局部最优的路径和初始解的路径相同，说明本次迭代没有变化
				same_count++;
			}
			else {
				same_count = 0;
			}
			init_result = neibor_best_result;	
			/*if (count != 0 && count % 50 == 0) {
				std::cout << "No： " << count << "   本次迭代的局部最优路径长度是： " << local_fit << endl;
			}*/
		}
		// 执行到这里就说明已经得到局部最优了  这时候需要添加扰动
		//std::cout << " 这时候需要添扰动" << endl;
		//display_single(neibor_best_result);
		double final_fit = fitness(final_result, ivec);
		local_fit = fitness(neibor_best_result, ivec);
		if ( final_fit> local_fit) {
			// 如果当前的全局最优的路径长度 大于 得到的局部最优的路径的长度
			// 更新全局最优路径
			final_result = neibor_best_result;
			final_fit = local_fit;
		}
		// 每五十次输出当前的最优解
		if (count != 0 && count % 50 == 0) {
			std::cout << "No： " << count << "   本次迭代的最优路径长度是： " << final_fit << endl;
		}

		//cout << "本次的局部最优解路径长度是： " << local_fit << endl;
		//cout << "本次的局部最优解是： " << endl;
		//display_single(neibor_best_result);*/
		
		// 多次进行局部之后解不变化了之后才进行扰动？
	
		//// 对局部最优解进行扰动 生成新的解群
		vector<vector<int> > disturbance_result = disturbance_neibor(neibor_best_result, neibor_number);
		// 在扰动生成的解群中找到最优的 
		vector<double>disturbance_fit(neibor_number, -1);
		for (int i = 0; i < neibor_number; ++i)
		{
			disturbance_fit[i] = fitness(disturbance_result[i], ivec);
		}
		int distur_min_index = 0;
		for (int i = 0; i < neibor_number; ++i)
		{
			if (disturbance_fit[i] < disturbance_fit[distur_min_index]) {
				distur_min_index = i;
			}
		}
		vector<int> distur_best_result = disturbance_result[distur_min_index];
		// 
		/*if (local_fit < disturbance_fit[distur_min_index])
		{
			distur_best_result = neibor_best_result;
			
		}
		else {
			local_fit = disturbance_fit[distur_min_index];
		}
		cout << "本次的扰动最优解路径长度是： " << local_fit << endl;*/
		

		//init_result = distur_best_result;

		// 扰动后的解 如果好于局部最优 则一定接受，作为下次迭代的新解，否则按照模拟退火 初始接受差解概率大，后面慢慢接受差解概率小
		if (local_fit > disturbance_fit[distur_min_index])
		{
			init_result = distur_best_result;
		}
		else {
			//一定的概率接受差解
			// init_result = neibor_best_result;
			// 模拟退火
			double deltE = local_fit - disturbance_fit[distur_min_index];
			// 		
			double p = exp((deltE / kt));
			//cout << "接受差解的概率是" << p << endl;
			// 生成0-1之间的随机数
			std::random_device e;
			std::uniform_real_distribution<double> u(0, 1);
			double suiji = u(e);
			if (suiji < p) {
				init_result = distur_best_result;
			}
			else {
				init_result = neibor_best_result;
			}
			kt = kt * 0.98; // 更新温度
			// 当模拟退火的概率小于0.1的时候只在全局最优附近搜索？
			/*if (p < 0.1) {
				init_result = final_result;6   
			}*/
		}
		// 再加个判断 多少次之后只在全局最优解的附近搜索？
		//扰动后的解也就是下一次迭代的开始的解
		// 计算每次迭代开始的解的距离
	/*	double first_num = fitness(init_result, ivec);
		std::cout << "本次扰动后得到的下次迭代初始解的适应度是： " << first_num << endl;*/

		
	}
	// 查看最终解
	endTime = clock();
	std::cout << " The 最终 result： " << endl;
	display_single(final_result);
	
	std::cout << "最终解的距离是： " << fitness(final_result, ivec)<< endl;
	std::cout << "运行时间是： " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
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
 