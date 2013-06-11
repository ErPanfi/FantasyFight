#ifndef FANTASYFIGHT_HEAP_H
#define FANTASYFIGHT_HEAP_H

template <class T, int maxSize = 16>
class Heap
{
public:
	typedef bool(*LessOperator)(const T&, const T&) const;

private:
	T *m_heapContent;
	int m_currentSize;
	LessOperator m_lo;

	void initFromOtherHeap(const Heap<T, maxSize>& other);
	void unInit();

	//indexing methods
	int inline father_idx(int idx) const;
	int inline left_children_idx(int idx) const;
	int inline right_children_idx(int idx) const;
	//compare method
	bool inline compare(const T& a, const T&b) const;
	//bubbling methods
	bool inline exchangeNodesByIdx(int& currIdx, const int newIdx);
	void bubbleDown(int startIdx);
	void bubbleUp(int startIdx);

public:

	//ctors
	Heap(int size = maxSize, LessOperator less = nullptr);
	Heap(const Heap<T, maxSize>& other);
	//dtor
	~Heap();
	//assignment
	Heap& operator=(const Heap& other);
	//add object
	void add(const T& obj);
	//top object
	const T& top() const;
	//remove object
	void remove(int idx);
};

#include "Heap.cpp"	//barbatrucco ;)

#endif
