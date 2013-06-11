#ifndef FANTASYFIGHT_HEAP_H
#define FANTASYFIGHT_HEAP_H

#include "Character.h"

template <int maxSize>
class CharacterHeap
{
private:
	Character* m_heapContent;
	int m_currentSize;

	void initFromOtherHeap(const Heap<T, maxSize, LessOperator>& other);
	void unInit();

	//indexing methods
	int inline father_idx(int idx) const;
	int inline left_children_idx(int idx) const;
	int inline right_children_idx(int idx) const;
	//compare method
	bool inline compare(T& a, T&b);
	//bubbling methods
	bool inline exchangeNodesByIdx(int& currIdx, const int newIdx);
	void bubbleDown(int startIdx);
	void bubbleUp(int startIdx);

public:

	//ctors
	Heap(int size = maxSize);
	Heap(const Heap<T, maxSize, LessOperator>& other);
	//dtor
	~Heap();
	//assignment
	Heap<T, maxSize, LessOperator>& operator=(const Heap<T, maxSize, LessOperator>& other);
	//add object
	void add(const T& obj);
	//top object
	const T& top() const;
	//remove object
	void remove(int idx);
	//update top position
	void updateTop() { bubbleDown(0); }
};

#include "Heap.cpp"	//barbatrucco ;)

#endif
