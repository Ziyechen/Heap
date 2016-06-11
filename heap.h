#pragma once

#include <vector>
#include <assert.h>

template <class T>
class Heap
{
public:
	//构造函数
	Heap()
		:_a(NULL)
	{}
	Heap(const T *a, size_t size)
	{
		_a.reserve(size);

		for (size_t i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		//建堆
		for (int i = (_a.size() - 2) / 2; i >= 0; i--)
		{
			_AdJustDown(i, size);
		}
	}
	//拷贝构造
	Heap(const Heap<T> &h)
	{
		size_t size = h._a.size();
		_a.reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			_a.push_back(h._a[i]);
		}
	}
	
public:
	//插入元素
	void Push(const T &x)
	{
		_a.push_back(x);
		//上调最后一个元素
		_AdJustUp(_a.size() - 1, _a.size());
	}
	//获取堆顶元素
	T & Top()
	{
		assert(!_a.empty());
		return _a[0];
	}
	//删除堆顶元素
	void Pop()
	{
		assert(!_a.empty());

		//交换堆顶和最后一个元素
		size_t size = _a.size();
		swap(_a[0], _a[size - 1]);
		_a.pop_back();

		//下调堆顶元素
		_AdJustDown(0, size-1);
	}
	//判空
	bool Empty()
	{
		return _a.empty();
	}
	//求堆的大小
	size_t Size()
	{
		return _a.size();
	}
	//输出堆
	void Print()
	{
		for (size_t i = 0; i < _a.size(); i++)
		{
			cout << _a[i] << " ";
		}
		cout << endl;
	}
protected:
	//下调
	void _AdJustDown(int parent, size_t size)
	{
		size_t child = parent * 2 + 1;
		
		while (child < size)
		{
			//将child置为左右孩子节点较大的
			if ((child + 1) < size && _a[child + 1] > _a[child])
				child++;
			
			//将child和parent比较
			if (_a[child] > _a[parent])
			{
				swap(_a[child], _a[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	//上调
	void _AdJustUp(int child, size_t size)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_a[child] > _a[parent])
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	vector<T> _a;
};
