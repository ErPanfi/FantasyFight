#ifndef FANTASYFIGHT_MEMORYPOOL_H
#define FANTASYFIGHT_MEMORYPOOL_H

template <typename T, unsigned int Size = 10> class MemoryPool
{
private:
	T* elemPool;
	MemoryPool<T, Size>* next; 
	int firstFree;

public: 
	MemoryPool();
	~MemoryPool();

	T* getNew();
	void free(T* item);

private:
	T* returnFreeCell();
	MemoryPool<T, Size>* returnFreePool();
	bool isInThePool (T* item);
	MemoryPool<T, Size>* returnItemPool ( T* item );
}; 

#endif 