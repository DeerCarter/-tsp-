// test1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include<iostream>
//#include<string>
//#include<set>
//#include<algorithm>
//using namespace std;
//
//int main()
//{
//	string input_s;
//	string high_string=NULL, mid_string = NULL, low_string = NULL;
//	string high_m = "bdfhkl";
//	string mid_m = "aceimnorstuvwxz";
//	string low_m = "gjpqy";
//	set<char> high_set;
//	set<char> mid_set;
//	set<char> low_set;
//	for (int i = 0; i < high_m.size(); i++)
//	{
//		high_set.insert(high_m[i]);
//	}
//	for (int i = 0; i < mid_m.size(); i++)
//	{
//		mid_set.insert(mid_m[i]);
//	}
//	for (int i = 0; i < low_m.size(); i++)
//	{
//		low_set.insert(low_m[i]);
//	}
//
//	cin >> input_s;
//	int n = input_s.size();
//	for (int i = 0; i < n; i++) {
//		if (high_set.find(input_s[i]) != high_set.end())
//		{
//			high_string += input_s[i];
//		}
//		else if (mid_set.find(input_s[i]) != mid_set.end())
//		{
//			mid_string += input_s[i];
//		}
//		else if (low_set.find(input_s[i]) != low_set.end())
//		{
//			low_string += input_s[i];
//		}
//	}
//	sort(high_string.begin(), high_string.end());
//	sort(mid_string.begin(), mid_string.end());
//	sort(low_string.begin(), low_string.end());
//	cout << high_string << endl;
//	cout << mid_string << endl;
//	cout << low_string << endl;
//
//
//
//	return 0;
//}
// 用map 存储？
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

vector<string> read_string(string s)
{
	vector<string> result;
	int n = s.size();
	string s1;
	s1 += s[0];
	for (int i = 1; i < n; i++) {
		//s1 += s[i];
		if (s[i] == ' ') {
			result.push_back(s1);
			s1 = "";
		}
		else {
			s1 += s[i];
		}
		if (i == (n - 1)) {
			result.push_back(s1);
		}
	}
	return result;
}

string changechar(char s[])
{
	string s1;
	for (int i = 0; i < 200; i++) {
		if (s[i] == '\0') {
			return s1;
		}
		else {
			s1 += s[i];
		}
	}
}
class music {
private:
	string s1;
	string s2;
	int num;
public:
	music(string s1, string s2, int num) {
		this->s1 = s1;
		this->s2 = s2;
		this->num = num;
	}
	string getS1() {
		string s = this->s1;
		return s;
	}
	string getS2() {
		string s = this->s2;
		return s;
	}
	int getNum() {
		int s = this->num;
		return s;
	}
};

string leixing(map<string,int>m1, map<string,int>m2, map<string,int>m3, string song) {
	string leixing;
	for (auto it = m1.begin(); it != m1.end(); it++) {
		if ((*it).first == song) {
			leixing = "Pop";
			return leixing;
		}
	}
	for (auto it = m2.begin(); it != m2.end(); it++) {
		if ((*it).first == song) {
			leixing = "Blue";
			return leixing;
		}
	}
	for (auto it = m3.begin(); it != m3.end(); it++) {
		if ((*it).first == song) {
			leixing = "Rock";
			return leixing;
		}
	}
}

int main()
{
	map<string, int>Pop;
	map<string, int>Blue;
	map<string, int>Rock;
	map<string, int>UnkownStyle;
	string input_s;
	vector<string> result;
	char s[200];
	vector<string> P;
	vector<string> B;
	vector<string> R;
	while (gets_s(s))
	{
		if (s[0] == '\0')
		{
			break;
		}
		/*else {
			cout << "hello " << endl;
		}*/
		// 分割字符串
		input_s = changechar(s);
		cout << input_s << endl;
		result = read_string(input_s);
	/*	for (int i = 0; i < result.size(); i++) {
			
			cout << result[i] <<" size: "<<result[i].size()<<endl;
		}*/
		if (result[0] == "I") {
			// 添加到map
			if (result[2] == "Pop") {
				Pop[result[1]] = 0;
			}
			else if (result[2] == "Blue")
			{
				Blue[result[1]] = 0;
			}
			else if (result[2] == "Rock")
			{
				Rock[result[1]] = 0;
			}
			else if (result[2] == "UnkownStyle")
			{
				UnkownStyle[result[1]] = 0;
			}
		}
		// 播放完一首歌曲
		else if (result[0] == "P")
		{
			if (Pop.find(result[1]) != Pop.end()) {
				for (auto it = Pop.begin(); it != Pop.end(); it++) {
					if ((*it).first == result[1]) {
						(*it).second += 3;
					}
					else {
						if (!P.empty() && leixing(Pop, Blue, Rock, P[P.size() - 1]) == "Pop") {
							(*it).second += 1;
						}
					}
					P.push_back(result[1]);
				}
			}
			else if (Blue.find(result[1]) != Blue.end()) {
				for (auto it = Blue.begin(); it != Blue.end(); it++) {
					if ((*it).first == result[1]) {
						(*it).second += 3;
					}
					else {
						if (!P.empty() && leixing(Pop,Blue,Rock,P[P.size() - 1]) == "Blue") {
							(*it).second += 1;
						}
					}
					P.push_back(result[1]);
				}
			}
			else if (Rock.find(result[1]) != Rock.end()) {
				for (auto it = Rock.begin(); it != Rock.end(); it++) {
					if ((*it).first == result[1]) {
						(*it).second += 3;
					}
					else {
						if (!P.empty() && leixing(Pop, Blue, Rock, P[P.size() - 1]) == "Rock") {
							(*it).second += 1;
						}
					}
					P.push_back(result[1]);
				}
			}
			else if (UnkownStyle.find(result[1]) != UnkownStyle.end()) {
				UnkownStyle[result[1]] += 3;
			}
		}
		// 中断一首歌曲
		else if (result[0] == "B") {

			if (Pop.find(result[1]) != Pop.end()) {
				for (auto it = Pop.begin(); it != Pop.end(); it++) {
					if ((*it).first == result[1]) {
						(*it).second -= 2;
					}
					else {
						if (!B.empty() && leixing(Pop, Blue, Rock, B[B.size() - 1]) == "Pop") {
							(*it).second -= 1;
						}
					}
					B.push_back(result[1]);
				}
			}
			else if (Blue.find(result[1]) != Blue.end()) {
				for (auto it = Blue.begin(); it != Blue.end(); it++) {
					if ((*it).first == result[1]) {
						(*it).second -= 2;
					}
					else {
						if (!B.empty() && leixing(Pop, Blue, Rock, B[B.size() - 1]) == "Blue") {
							(*it).second -= 1;
						}
					}
					B.push_back(result[1]);
				}
			}
			else if (Rock.find(result[1]) != Rock.end()) {
				for (auto it = Rock.begin(); it != Rock.end(); it++) {
					if ((*it).first == result[1]) {
						(*it).second -= 2;
					}
					else {
						if (!B.empty() && leixing(Pop, Blue, Rock, B[B.size() - 1]) == "Rock") {
							(*it).second -= 1;
						}
					}
					B.push_back(result[1]);
				}
			}
			else if (UnkownStyle.find(result[1]) != UnkownStyle.end()) {
				UnkownStyle[result[1]] -= 1;
			}
		}
	}
	// 对所有的MAP 进行排序？
	// 
	vector<music*> musicresult;
	for (auto it = Pop.begin(); it != Pop.end(); it++) {
		music* popmusic = new music("Pop", (*it).first, (*it).second);
		musicresult.push_back(popmusic);
	}
	for (auto it = Blue.begin(); it != Blue.end(); it++) {
		music* popmusic = new music("Blue", (*it).first, (*it).second);
		musicresult.push_back(popmusic);
	}
	for (auto it = Rock.begin(); it != Rock.end(); it++) {
		music* popmusic = new music("Rock", (*it).first, (*it).second);
		musicresult.push_back(popmusic);
	}
	for (auto it = UnkownStyle.begin(); it != UnkownStyle.end(); it++) {
		music* popmusic = new music("UnkownStyle", (*it).first, (*it).second);
		musicresult.push_back(popmusic);
	}
	cout << musicresult.size() << endl;
	for (int i = 0; i < musicresult.size(); i++) {
		cout << musicresult[i]->getS2() << " " << musicresult[i]->getS1() << " "<< musicresult[i]->getNum()<<endl;
	}
	int count = 0;
	set<int> countindex;
	while (count< musicresult.size()) {
		int max_value = INT_MIN;
		int max_index = -1;
		for (int i = 0; i < musicresult.size(); i++) {
			if (countindex.find(i) == countindex.end()) {
				if (musicresult[i]->getNum() > max_value) {
					max_value = musicresult[i]->getNum();
					max_index = i;
				}
			}
			else {
				continue;
			}
		}
		cout << musicresult[max_index]->getS2() << " " << musicresult[max_index]->getS1() << endl;
		count++;
		countindex.insert(max_index);
		
	}
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
