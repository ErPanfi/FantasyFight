#ifndef FANTASYFIGHT_LIST_H
#define FANTASYFIGHT_LIST_H

#include "Pool.h"

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

	typedef Pool< Node , PoolSize > NodePool; 
public: 
	
	class Iterator
	{
	private: 
		Node* currentNode; 
	public: 	
		Iterator(); 
		Iterator(Node* node); 
		Iterator(Iterator& rhv); 
		T* current(); 
		void advance(); 
		Iterator& remove(); 
		Iterator& operator=(Iterator& rhv); 
		bool operator==(Iterator& rhv); 
	}; 

	typedef bool(*FindPredicate)(T*); 
protected: 
	Node* head; 	
	NodePool nodePool; 
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