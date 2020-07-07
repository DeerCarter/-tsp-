// test2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 手写快速排序
#include <iostream>
#include <vector>
using namespace std;


// 快速排序 [l,....r]
void quicksort(vector<int>& nums, int l, int r)
{
	if (l >= r) {
		return;
	}
	int temp = nums[l];
	int lt = l;
	int gt = r + 1;
	int i = l + 1;
	while (i < gt) {
		if (nums[i] == temp) {
			i++;
		}
		else if (nums[i] < temp) {
			swap(nums[++lt], nums[i++]);		
		}
		else if (nums[i] > temp) {
			swap(nums[i], nums[--gt]);
		}
	}
	swap(nums[l], nums[lt]);
	quicksort(nums, l, lt - 1);
	quicksort(nums, gt, r);
}
int main()
{
    /*std::cout << "Hello World!\n";*/
	vector<int> nums = { 10,9,8,7,6,5,4,3,2,1 };
	//vector<int> nums = { 1,6,8,10,5,9,7,3,4,2 };
	quicksort(nums, 0, nums.size() - 1);
	for (auto n : nums) {
		cout << n << " " ;
	}
	cout << endl;
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
