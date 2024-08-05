#include <iostream>
#include<vector>
#include <queue>
#include<algorithm>
#include<unordered_map>
#include<functional>
using namespace std;

/*
	海量数据求查重和topk问题的综合应用
	查重：数据是否有重复，以及数据重复的次数
	topk：元素的值前k大/小，第k大/小
	题目：数据的重复次数最大/最小的前k个/第k个
	
	题目：数据的重复次数最大/最小的前k个/第k个
	哈希统计（map）+堆/快排
*/

// 在一组数字中，找出重复次数最多的前10个
int main()
{
	// 用vec存储要处理的数字
	vector<int> vec;
	for (int i = 0; i < 200000; ++i)
	{
		vec.push_back(rand());
	}

	// 统计所有数字的重复次数，key：数字的值，value：数字重复次数
	unordered_map<int, int> numMap;
	for(int val:vec)
	{
		/*
			拿val数字在map中查找，如果val不存在，numMap[val]会插入一个[val,0]
			这么一个返回值，然后++，得到一个[val,1]这么一组新数据
			如果val存在，numMap[val]刚好返回的是val数字对应的second重复的次数，直接++
		*/
		numMap[val]++;
	}

	// 先定义一个小根堆   数字=》重复次数
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto &a, auto &b)->bool{
		return a.second > b.second;		// 自定义小根堆元素的大小比较方式
	});

	// 先往堆放k个数据
	int k = 0;
	auto it = numMap.begin();

	// 先从map表中读10个数据到小根堆中，建立top 10的小根堆，最小的元素在堆顶
	for (; it != numMap.end() && k < 10; ++it, ++k)
	{
		minheap.push(*it);
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
	// 堆中剩下的就是重复次数最大的前k个
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << " : " << pair.second << endl;
		minheap.pop();
	}
	return 0;
}
