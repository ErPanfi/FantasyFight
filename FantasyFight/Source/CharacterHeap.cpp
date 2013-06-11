#ifndef FANTASYFIGHT_HEAP_CPP
#define FANTASYFIGHT_HEAP_CPP

#include "Heap.h"
#include <assert.h>
//init methods
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
void Heap<T, maxSize, LessOperator>::initFromOtherHeap(const Heap<T, maxSize, LessOperator>& other)	//init from other heap with same template params
{
	m_heapContent = malloc(maxSize * sizeof(T));
	memcpy(m_heapContent, other -> m_heapContent, maxSize);
	m_currentSize = other -> m_currentSize;
};

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
void Heap<T, maxSize, LessOperator>::unInit()		//un-initialize all variables, leaving a blank instance, and handle dynamic memory correctly
{
	m_currentSize = 0;
	delete[] m_heapContent;
	m_heapContent = nullptr;
}

//ctors & dtors & =
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
Heap<T, maxSize, LessOperator>::Heap(int size = maxSize)
	: m_heapContent(new T[size])
	, m_currentSize(size)
{
}

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
Heap<T, maxSize, LessOperator>::Heap(const Heap<T, maxSize, LessOperator>& other)
{
	initFromOtherHeap(other);
}

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
Heap<T, maxSize, LessOperator>::~Heap()
{
	unInit();
}

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
Heap<T, maxSize, LessOperator>& Heap<T, maxSize, LessOperator>::operator=(const Heap& other)
{
	if(this != other)
	{
		unInit();
		initFromOtherHeap(other);
	}

	return *this;
}

//indexing methods
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
int inline Heap<T, maxSize, LessOperator>::father_idx(int idx)  const
{
	int ret = (idx + 1) / 2 - 1;

	return ret >= 0 ? ret : -1;
}

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
int inline Heap<T, maxSize, LessOperator>::left_children_idx(int idx)  const
{
	int ret = (idx + 1) * 2 - 1;

	return ret < currentSize ? ret : -1;
}

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
int inline Heap<T, maxSize, LessOperator>::right_children_idx(int idx)  const
{
	int ret = (idx + 1) * 2;

	return ret < currentSize ? ret : -1;
}

//compare method
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
bool inline Heap<T, maxSize, LessOperator>::compare(T& a, T&b)
{
	return LessOperator(a, b);
}

//bubbling methods
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
bool inline Heap<T, maxSize, LessOperator>::exchangeNodesByIdx(int& currIdx, const int newIdx)
{
	assert(currIdx < 0 || currIdx >= m_currentSize || newIdx < 0 || newIdx >= m_currentSize);	//Heap index out of range

	T temp = m_heapContent[currIdx];
	m_heapContent[currIdx] = m_heapContent[newIdx];
	m_heapContent[newIdx] = temp;
	currIdx = newIdx;

	return true;
}

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
void Heap<T, maxSize, LessOperator>::bubbleDown(int startIdx)
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

template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
void Heap<T, maxSize, LessOperator>::bubbleUp(int startIdx)
{
	int currIdx = startIdx;
	bool exchanged;

	do
	{
		exchanged = false;

		if(father_idx(currIdx) < m_currentSize && compare(m_heapContent[father_idx(currIdx)], m_heapContent[currIdx]))
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
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
void Heap<T, maxSize, LessOperator>::add(const T& obj)
{
	if(m_currentSize < maxSize)
	{
		m_heapContent[m_currentSize] = obj;
		bubbleUp(m_currentSize++);
	}
}

//top object
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
const T& Heap<T, maxSize, LessOperator>::top() const
{
	return heapContent[0];
}

//remove object
template <typename T, int maxSize, bool (*LessOperator)(T&, T&)>
void Heap<T, maxSize, LessOperator>::remove(int idx)
{
	if(m_currentSize)
	{
		m_heapContent[idx] = heapContent[--m_currentSize];
		bubbleDown(idx);
	}
}


#endif