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
		Node(); 
	}; 

	typedef MemoryPool< Node , PoolSize > NodePool; 
	
	class Iterator
	{
	private: 
		Node* prevNode;
		Node* currentNode; 
		void inline  initFromNode ( Node* node, Node* prev = null );
		void inline  initFromIterator ( Iterator* inIterator );
		void inline  unInit (){}
	public: 	
		Iterator(); 
		Iterator(Node* node); 
		Iterator(Iterator& rhv); 
		~Iterator(){unInit();}
		T* current(); 
		void advance(); 
		Iterator& remove(); 
		Iterator& operator=(const Iterator& rhv); 
		bool operator==(const Iterator& rhv) const; 
		void operator++();
	}; 


	typedef bool(*FindPredicate)(T*); 

protected: 
	Node* head; 
	Node* last;
	NodePool nodePool; 
	unsigned int counter;
public: 
	List(); 
	~List();

	T* getNewObject(); 
	bool empty(); 
	unsigned int size(); 
	Iterator& begin(); 
	Iterator& end(); 
	Iterator& find(T* item); 
	Iterator& find(FindPredicate predicate); 
}; 

#endif