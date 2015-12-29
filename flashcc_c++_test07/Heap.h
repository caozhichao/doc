#ifndef HEAP_H
#define HEAP_H
#include <vector>
using std::vector;

#pragma once
class Heap
{
public:
	Heap(void);
	~Heap(void);

	void reset();
	void enqueue(int value);
	bool modify(int obj,int newObj);
	int dequeue(void);
	void toString();

private:
	vector<int> _heap;
	int _postionIndex;

	void sort(int childIndex);
	int compareFun(int a,int b);
};

#endif

