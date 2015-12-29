#include "Heap.h"
#include <iostream>


Heap::Heap(void)
{
}


Heap::~Heap(void)
{
}

void Heap::reset(){
	_heap.clear();
	_postionIndex = 0;
}
void Heap::enqueue(int value){
	
	//_heap[_postionIndex] = value;
	_heap.push_back(value);
	sort(_postionIndex);
	_postionIndex++;
}
void Heap::sort(int childIndex){

	//���ڵ�index
	int pIndex;
	//�ӽڵ�index
	int cIndex = childIndex;
	int temp  = _heap[cIndex];
	//cIndex>0����pIndex
	while(cIndex > 0)
	{
		pIndex = (cIndex - 1) >> 1;
		//����²�������ݴ���parent�����ݣ���Ӧ����������parent����λ��
		if(compareFun(temp,_heap[pIndex]) > 0)
		{
			_heap[cIndex] = _heap[pIndex]; 
			//�����ӽڵ��λ��
			cIndex = pIndex;
		} else 
		{
			break;
		}
	}
	_heap[cIndex] = temp;
}
int Heap::compareFun(int a,int b){
	if(a > b){
		return 1;
	}else if(a < b){
		return -1;
	}
	return 0;
}
bool Heap::modify(int obj,int newObj){
	int cindex = -1;

	vector<int>::size_type  len = _heap.size();
	vector<int>::size_type i;
	for(i = 0; i < len; ++i){
		if(_heap[i] == obj){
			cindex = i;
			break;
		}
	}
	//= _heap.indexOf(obj);

	if(cindex < 0){
		return false;
	}
	_heap[cindex]= newObj;
	sort(cindex);
	return true;
}

int Heap::dequeue(void){
	int element  = _heap[0];
	int lastElement = _heap[_heap.size()-1];
	_heap.pop_back();
	_postionIndex--;
	if(_postionIndex > 0)
	{
		_heap[0] = lastElement;
		int pIndex = 0;
		int cIndex = 1;
		int temp = _heap[pIndex];
		while(cIndex <= _postionIndex-1)
		{
			//�Ƚ�2���ӽڵ�
			if(_heap[cIndex+1] && compareFun(_heap[cIndex],_heap[cIndex+1]) < 0)
			{
				cIndex++;
			}
			if(compareFun(temp,_heap[cIndex])<0)
			{
				_heap[pIndex] = _heap[cIndex];
				pIndex = cIndex;
				//�����ӽڵ��λ��
				cIndex = (cIndex << 1) + 1;
			}else
			{
				break;
			}
		}
		_heap[pIndex] = temp;
	}
	return element;
}

void Heap::toString(){
	vector<int>::size_type  len = _heap.size();
	vector<int>::size_type i;
	for(i = 0; i < len; ++i){
		std::cout << _heap[i] << std::endl;
	}
}

