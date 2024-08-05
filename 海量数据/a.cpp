#include <iostream>
#include<vector>
#include <queue>
#include<algorithm>
using namespace std;

/*
	海量数据求TOP K的问题
	1、求最大的/最小的前k个元素
	2、求最大的/最小的第k个元素

	10000个整数，找值前10大的元素

	解法1、大根堆/小根堆 =》优先级队列priority_queue
	先用前10个整数创建一个小根堆（最小值就在堆顶），然后遍历剩下的整数，如果整数比堆定元素大，
	那么删除堆顶元素（出堆），然后再把整数入堆，遍历完所有的整数，小根堆里面放的就是值最大的
	前10个元素了；如果找的是第k小（大根堆堆顶）或者第k大（小根堆堆顶），
	只需要访问堆顶一个元素就可以了
	大根堆 =》找topk小的
	小根堆=》找topk大的

	解法2、快排分割函数
	经过快排分割函数，能够在O(log2n)时间内，把小于基准数的整数调整到左边，把大于基准数的整数
	调整到右边，基准数（index）就可以认为是第index+1小的整数，[0,(index)]就是前index+1小的整数了
*/

int main() {
	/*
		求Vector容器中元素值最大的前10个数字
	*/
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand()+i);
	}

	// 时间复杂度：O(n)

	// 定义小根堆
	priority_queue<int, vector<int>, greater<int>>minHeap;
	// 先往小根堆放入10个原色
	int k = 0;
	for (; k < 10; k++)
	{
		minHeap.push(vec[k]);
	}
	/*
		遍历剩下的元素依次和堆顶元素进行比较，如果比堆顶元素大，那么删除堆顶元素
		把当前元素添加到小根堆中，元素遍历完成，堆中剩下的10个元素，就是最大的10个元素
	*/
	for (; k < vec.size(); ++k)
	{
		if (vec[k] > minHeap.top())
		{
			minHeap.pop();
			minHeap.push(vec[k]);
		}
	}

	// 打印结果
	while(!minHeap.empty())
	{
		cout << minHeap.top()<<" ";
		minHeap.pop();
	}
	cout << endl;
	sort(vec.rbegin(),vec.rend());
	for (int i = 0; i < 10; i++)
	{
		cout << vec[i] << " ";
	}
}
