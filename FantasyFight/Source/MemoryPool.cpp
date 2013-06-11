#ifndef FANTASYFIGHT_MEMORYPOOL_CPP
#define FANTASYFIGHT_MEMORYPOOL_CPP

#include "MemoryPool.h"
#include <new>

template <typename T, unsigned int Size>
MemoryPool<T,Size>::MemoryPool()
	:next(nullptr)
	,firstFree(0)
	,elemPool(new T[Size])
{

	T* cell;
	int* counter;
	for ( int i = 1; i < Size; i++)
	{
		cell = &elemPool[i-1];
		counter = reinterpret_cast <int*> (cell);
		*counter = i;
	}
	cell = &elemPool[Size-1];
	counter = reinterpret_cast <int*> (cell);
	*counter = -1;
}

template <typename T, unsigned int Size>
MemoryPool<T,Size>::~MemoryPool()
{
	delete [] elemPool;
}

template <typename T, unsigned int Size>
T* MemoryPool<T,Size>::getNew()
{
	void* targetMemory = returnFreePool()->returnFreeCell();
	return new (targetMemory) T();
}

template <typename T, unsigned int Size>
void MemoryPool<T,Size>::free(T* item)
{

	MemoryPool<T, Size>* actualPool;
	actualPool = returnItemPool(item);

	assert(actualPool); //"L'elemento non � nel pool"

	item->~T(); 

	int* counter = reinterpret_cast <int*> (item);
	*counter = firstFree;

	firstFree = (item - actualPool);
}

template <typename T, unsigned int Size>
T* MemoryPool<T,Size>::returnFreeCell()
{
	T* cell = &elemPool[firstFree];
	int* counter = reinterpret_cast <int*> (cell);
	firstFree = *counter;
	return cell;
}

template <typename T, unsigned int Size>
MemoryPool<T, Size>* MemoryPool<T,Size>::returnFreePool()
{
	MemoryPool<T, Size>* freePool = this;
	while(freePool->next && freePool->firstFree < 0)
	{
		freePool = freePool->next;
	}

	if(freePool->firstFree < 0)
	{
		freePool->next = new MemoryPool<T, Size>();
		freePool = freePool->next;
	}

	return freePool;
}

template <typename T, unsigned int Size>
bool MemoryPool<T,Size>::isInThePool (T* item)
{
	return (item >= elemPool && item < elemPool + Size);
}

template <typename T, unsigned int Size>
MemoryPool<T, Size>* MemoryPool<T,Size>::returnItemPool (T* item)
{
	MemoryPool<T, Size>* actualPool = this;

	while (actualPool->next && !actualPool->isInThePool())
	{
		actualPool = actualPool->next
	}

	if(actualPool->isInThePool())
	{
		return actualPool;
	}
	else
	{
		return nullptr; 
	}

}

#endif