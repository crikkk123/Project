#include <iostream>
#include<vector>
#include <queue>
#include<algorithm>
#include<unordered_map>
#include<functional>
using namespace std;

/*
	有一个大文件，没存限制200M，求文件中重复次数最多的前10个
	大文件=》小文件
	大文件里面的数据=》哈希映射=》把数据离散的放入小文件当中
*/

// 大文件划分小文件（哈希映射）+哈希统计+小根堆（需要遍历所有元素）（快排分割）
int main()
{

	FILE* pf1 = fopen("data.dat","wb");
	for(int i=0;i<20000;++i)
	{
		int data = rand();
		fwrite(&data,4,1,pf1);
	}
	fclose(pf1);

	FILE* pf = fopen("data.dat","rb");
	if (pf == nullptr)
	{
		return 0;
	}

	// 这里由于原始数据量缩小，所以这里文件划分的个数也变小了，11个小文件
	const int FILE_NO = 11;
	FILE* pfile[FILE_NO] = { nullptr };

	for (int i = 0; i < FILE_NO; ++i)
	{
		char filename[20];
		sprintf(filename,"data%d.dat",i+1);
		pfile[i] = fopen(filename,"wb+");
	}
	// 哈希映射，把大文件中的数据，映射到各个小文件当中
	int data;
	while (fread(&data, 4, 1, pf) > 0)
	{
		int findex = data % FILE_NO;
		fwrite(&data,4,1,pfile[findex]);
	}

	// 定义一个链式哈希表
	unordered_map<int, int> numMap;
	// 先定一个小根堆
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto &a, auto &b)->bool {
		return a.second > b.second;
	});

	// 分段求解小文件的top 10大的数字，并求出最终结果
	for (int i = 0; i < FILE_NO; ++i)
	{
		// 恢复小文件的文件指针到起始为止
		fseek(pfile[i],0,SEEK_SET);
		while (fread(&data, 4, 1, pfile[i]) > 0)
		{
			numMap[data]++;
		}
		int k = 0;
		auto it = numMap.begin();
		// 如果堆是空的，先往堆放10个数据
		if (minheap.empty())
		{
			// 先从map表中读10个数据到小根堆中，建立top 10的小根堆，最小的元素在堆顶
			for (; it != numMap.end() && k < 10; ++it, ++k)
			{
				minheap.push(*it);
			}
		}

		// 把k+1到末尾的元素进行遍历，和堆顶元素比较
		for (; it != numMap.end(); ++it)
		{
			// 如果map表中当前元素重复次数大于堆顶元素的重复次数，则替换
			if (it->second > minheap.top().second)
			{
				minheap.pop();
				minheap.push(*it);
			}
		}
		// 清空哈希表，进行下一个小文件的数据统计
		numMap.clear();
	}
	// 堆中剩下的就是重复次数最大的前k个
	while(!minheap.empty())
	{
		auto &pair = minheap.top();
		cout << pair.first << " : " << pair.second << endl;
		minheap.pop();
	}
	return 0;
}
