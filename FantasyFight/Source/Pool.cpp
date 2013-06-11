#include "Pool.h"

template <typename T, unsigned int Size>
Pool<T,Size>::Pool()
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
Pool<T,Size>::~Pool()
{
	delete [] elemPool;
}

template <typename T, unsigned int Size>
T* Pool<T,Size>::getNew()
{
	return new (returnFreePool()->returnFreeCell()) T();
}

template <typename T, unsigned int Size>
void Pool<T,Size>::free(T* item)
{

	Pool<T, Size>* actualPool;
	actualPool = returnItemPool(item);

	DEBUG.assert(actualPool, "L'elemento non è nel pool");

	item->~T(); 

	int* counter = reinterpret_cast <int*> (item);
	*counter = firstFree;

	firstFree = (item - actualPool);
}

template <typename T, unsigned int Size>
T* Pool<T,Size>::returnFreeCell()
{
	T* newElem = &elemPool[firstFree];
	int* counter = reinterpret_cast <int*> (cell);
	firstFree = *counter;
	return newElem;
}

template <typename T, unsigned int Size>
Pool<T, Size>* Pool<T,Size>::returnFreePool()
{
	Pool<T, Size>* freePool = this;
	while(freePool->next && freePool->firstFree < 0)
	{
		freePool = freePool->next;
	}

	if(freePool->firstFree < 0)
	{
		freePool->next = new Pool<T, Size>();
		freePool = freePool->next;
	}

	return freePool;
}

template <typename T, unsigned int Size>
bool Pool<T,Size>::isInThePool (T* item)
{
	return (item >= elemPool && item < elemPool + Size);
}

template <typename T, unsigned int Size>
Pool<T, Size>* Pool<T,Size>::returnItemPool (T* item)
{
	Pool<T, Size>* actualPool = this;

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