#include <iostream>
#include<vector>
#include <queue>
#include<algorithm>
using namespace std;

int partation(vector<int>&arr, int i, int j)
{
	int k = arr[i];
	while (i < j)
	{
		while (i < j&&arr[i] >= k)
		{
			j--;
		}
		if (i < j)
		{
			arr[i++] = arr[j];
		}
		while (i < j&&arr[i] < k)
		{
			i++;
		}
		if (i < j)
		{
			arr[j--] = arr[i];
		}
	}
	arr[i] = k;
	return i;
}

/*
	params:
	1、vector<int> &arr:存储元素的容器
	2、int i:数据范围的起始下标
	3、int j:数据范围的末尾下标
	4、int k:第k个元素
	功能描述：通过快排的分割函数递归求解第k小的数字，返回它的值
*/
int selectNoK(vector<int> &arr, int i, int j, int k)
{
	int pos = partation(arr, i, j);
	if(pos==k-1)
	{
		return pos;
	}
	else if (pos < k - 1)
	{
		return selectNoK(arr, pos + 1,j, k);
	}
	else
	{
		return selectNoK(arr, i, pos - 1, k);
	}
}

int main()
{
	/*
		求Vector容器中元素值第10小的元素值
	*/
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}
	int pos = selectNoK(vec, 0, vec.size() - 1, 10);
	cout << vec[pos] << endl;	// 第10小的
	// 如果想要找前10小的 [0,pos]
	return 0;
}

/*
	有一个大文件，里面放的是整数，内存限制200M，求最大的前10个
	分治的思想
	计算一下整数文件的大小/200M = 要分的小文件的数量
	哈希映射  整数%小文件的个数  file_index
	现在每一个小文件就可以加载到内存当中了，对每一个小文件的整数topk元素
*/
