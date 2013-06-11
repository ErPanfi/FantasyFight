#ifndef FANTASYFIGHT_HEAP_CPP
#define FANTASYFIGHT_HEAP_CPP

#include "Heap.h"

//init methods
template <typename T, int maxSize>
void Heap<T, maxSize>::initFromOtherHeap(const Heap<T, maxSize>& other)	//init from other heap with same template params
{
	heapContent = malloc(maxSize * sizeof(T));
	memcpy(heapContent, other -> heapContent, maxSize);
	currentSize = other -> currentSize;
};

template <typename T, int maxSize>
void Heap<T, maxSize>::unInit()		//un-initialize all variables, leaving a blank instance, and handle dynamic memory correctly
{
	currentSize = 0;
	free(heapContent);
	heapContent = nullptr;
}

//ctors & dtors & =
template <typename T, int maxSize>
Heap<T, maxSize>::Heap(int size = maxSize, LessOperator less = T::operator<())	//
	: T(malloc(size * sizeof(T)))
	, currentSize = size
{
}

template <typename T, int maxSize>
Heap<T, maxSize>::Heap(const Heap<T, maxSize>& other)
{
	initFromOtherHeap(other);
}

template <typename T, int maxSize>
Heap<T, maxSize>::~Heap()
{
	unInit();
}

template <typename T, int maxSize>
Heap<T, maxSize>& Heap<T, maxSize>::operator=(const Heap& other)
{
	if(this != other)
	{
		unInit();
		initFromOtherHeap(other);
	}

	return *this;
}

//indexing methods
template <typename T, int maxSize>
int inline Heap<T, maxSize>::father_idx(int idx)  const
{
	int ret = (idx + 1) / 2 - 1;

	return ret >= 0 ? ret : -1;
}

template <typename T, int maxSize>
int inline Heap<T, maxSize>::left_children_idx(int idx)  const
{
	int ret = (idx + 1) * 2 - 1;

	return ret < currentSize ? ret : -1;
}

template <typename T, int maxSize>
int inline Heap<T, maxSize>::right_children_idx(int idx)  const
{
	int ret = (idx + 1) * 2;

	return ret < currentSize ? ret : -1;
}

//compare method
template <typename T, int maxSize>
bool inline Heap<T, maxSize>::compare(const T& a, const T&b)  const
{
	return lo ? lo(a, b) : a < b;
}

//bubbling methods
template <typename T, int maxSize>
bool inline Heap<T, maxSize>::exchangeNodesByIdx(int& currIdx, const int newIdx)
{
	Debug.Assert(currIdx < 0 || currIdx >= currentSize || newIdx < 0 || newIdx >= currentSize, "Heap index out of range.");

	T temp = heapContent[currIdx];
	heapContent[currIdx] = heapContent[newIdx];
	heapContent[newIdx] = temp;
	currIdx = newIdx;

	return true;
}

template <typename T, int maxSize>
void Heap<T, maxSize>::bubbleDown(int startIdx)
{

	int currIdx = startIdx;
	bool exchanged;

	do
	{
		exchanged = false;

		if(left_children_idx(currIdx) < currentSize && compare(heapContent[left_children_idx(currIdx)], heapContent[currIdx]))
		{
			/*
			int newIdx = left_children_idx(currIdx);
			T temp = heapContent[newIdx];
			heapContent[newIdx];
			heapContent[currIdx] = temp;
			exchanged = true;
			*/
			exchanged = exchangeNodesByIdx(currIdx, left_children_idx(currIdx));
		}
		else if(right_children_idx(currIdx) < currentSize && compare(heapContent[right_children_idx(currIdx)], heapContent[currIdx]))
		{
			exchanged = exchangeNodesByIdx(currIdx, right_children_idx(currIdx));
		}
	}
	while(exchanged);
}

template <typename T, int maxSize>
void Heap<T, maxSize>::bubbleUp(int startIdx)
{
	int currIdx = startIdx;
	bool exchanged;

	do
	{
		exchanged = false;

		if(father_idx(currIdx) < currentSize && compare(heapContent[father_idx(currIdx)], heapContent[currIdx]))
		{
			/*
			int newIdx = father_idx(currIdx);
			T temp = heapContent[newIdx];
			heapContent[newIdx];
			heapContent[currIdx] = temp;
			exchanged = true;
			*/
			exchanged = exchangeNodesByIdx(currIdx, father_idx(currIdx));
		}
	}
	while(exchanged);
}

//add object
template <typename T, int maxSize>
void Heap<T, maxSize>::add(const T& obj)
{
	if(currentSize < maxSize)
	{
		heapContent[currentSize] = obj;
		bubbleUp(currentSize++);
	}
}

//top object
template <typename T, int maxSize>
const T& Heap<T, maxSize>::top() const
{
	return heapContent[0];
}

//remove object
template <typename T, int maxSize>
void Heap<T, maxSize>::remove(int idx)
{
	if(currentSize)
	{
		heapContent[0] = heapContent[--currentSize];
		bubbleDown(0);
	}
}


#endif