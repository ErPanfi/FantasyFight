#ifndef FANTASYFIGHT_LIST_H
#define FANTASYFIGHT_LIST_H

#include "MemoryPool.h"

template <typename T, unsigned int PoolSize> class List
{
protected: 
	
	struct Node
	{
	public: 
		T object; 
		Node* next; 
	}; 

public: 
	typedef MemoryPool< Node , PoolSize > NodePool; 

protected:

	Node* head; 
	Node* last;
	NodePool nodePool; 
	unsigned int counter;

public:	
	class Iterator
	{
	private: 
		Node* m_prevNode;
		Node* m_currentNode; 
		void  initFromNode ( Node* node, List<T, PoolSize> *owner, Node* prev = nullptr );
		void inline  initFromIterator ( Iterator* inIterator );
		void inline  unInit (){}

		List<T, PoolSize> *m_owner;

	public: 	
		Iterator(); 
		Iterator(List<T, PoolSize> *owner, Node* node); 
		Iterator(Iterator& rhv); 
		~Iterator(){unInit();}
		T* current(); 
		void advance(); 
		Iterator& remove(); 
		Iterator& operator=(const Iterator& rhv); 
		bool operator==(const Iterator& rhv) const; 
		bool operator!=(const Iterator& rhv) const; 
		void operator++();

		friend class List<T, PoolSize>;
	};


	List(); 
	~List();

	T* getNewObject(); 
	bool empty(); 
	unsigned int size() const; 
	Iterator begin(); 
	Iterator end(); 
	Iterator find(T* item); 

	friend Iterator& List<T, PoolSize>::Iterator::remove();

	//typedef bool(*FindPredicate)(T*); 
	//Iterator& find(FindPredicate predicate); 
}; 

#include "List_Imp.h"

#endif