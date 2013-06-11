#ifndef FANTASYFIGHT_HEAP_CPP
#define FANTASYFIGHT_HEAP_CPP

#include "Heap.h"

//init methods
template <typename T, int maxSize>
void Heap<T, maxSize>::initFromOtherHeap(const Heap<T, maxSize>& other)	//init from other heap with same template params
{
	m_heapContent = malloc(maxSize * sizeof(T));
	memcpy(m_heapContent, other -> m_heapContent, maxSize);
	m_currentSize = other -> m_currentSize;
};

template <typename T, int maxSize>
void Heap<T, maxSize>::unInit()		//un-initialize all variables, leaving a blank instance, and handle dynamic memory correctly
{
	m_currentSize = 0;
	free(m_heapContent);
	m_heapContent = nullptr;
}

//ctors & dtors & =
template <typename T, int maxSize>
Heap<T, maxSize>::Heap(int size = maxSize, LessOperator less = T::operator<())	//
	: m_heapContent(malloc(size * sizeof(T)))
	, m_currentSize = size
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
	return m_lo ? m_lo(a, b) : a < b;
}

//bubbling methods
template <typename T, int maxSize>
bool inline Heap<T, maxSize>::exchangeNodesByIdx(int& currIdx, const int newIdx)
{
	Debug.Assert(currIdx < 0 || currIdx >= currentSize || newIdx < 0 || newIdx >= currentSize, "Heap index out of range.");

	T temp = heapContent[currIdx];
	m_heapContent[currIdx] = m_heapContent[newIdx];
	m_heapContent[newIdx] = temp;
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

		if(left_children_idx(currIdx) < currentSize && compare(m_heapContent[left_children_idx(currIdx)], m_heapContent[currIdx]))
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
		else if(right_children_idx(currIdx) < currentSize && compare(m_heapContent[right_children_idx(currIdx)], m_heapContent[currIdx]))
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

		if(father_idx(currIdx) < currentSize && compare(m_heapContent[father_idx(currIdx)], m_heapContent[currIdx]))
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
		m_heapContent[currentSize] = obj;
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
		m_heapContent[idx] = heapContent[--currentSize];
		bubbleDown(idx);
	}
}


#endif