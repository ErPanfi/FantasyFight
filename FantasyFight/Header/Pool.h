template <typename T, unsigned int Size = 10> class Pool
{
private:
	T* elemPool;
	Pool<T, Size>* next; 
	int firstFree;

public: 
	Pool();
	~Pool();

	T* getNew();
	void free(T* item);

private:
	T* returnFreeCell();
	Pool<T, Size>* returnFreePool();
	bool isInThePool (T* item);
	Pool<T, Size>* returnItemPool ( T* item );

}; 