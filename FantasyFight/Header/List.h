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
	T* getNewObject();
	unsigned int counter;

public:	
	class Iterator
	{
	private: 
		Node* m_prevNode;
		Node* m_currentNode; 
		void  initFromNode ( Node* node,const List<T, PoolSize> *owner, Node* prev = nullptr );
		void inline  initFromIterator (const Iterator* inIterator );
		void inline  unInit (){}

		List<T, PoolSize> *m_owner;

	public: 	
		Iterator(); 
		Iterator(List<T, PoolSize> *owner, Node* node); 
		Iterator(Iterator& rhv); 
		Iterator endIterator() const { return m_owner -> end(); }
		~Iterator(){unInit();}
		T* current(); 
		void advance(); 
		void advance(unsigned int val);
		Iterator& remove(); 
		Iterator& operator=(const Iterator& rhv); 
		bool operator==(const Iterator& rhv) const; 
		bool operator!=(const Iterator& rhv) const; 
		Iterator& operator++();	//prefix operator return reference to self
		Iterator operator++(int);	//postfix operator return copy of the iterator
		operator bool() const;


		friend class List<T, PoolSize>;
	};


	List(); 
	~List();

	Iterator begin() const;			//note that these 3 methods return iterators *BY VALUE*, so there's a 
	Iterator end() const;			//serie of copy constructor call here. This is done in order to mantain memory ownership inside the list.
	Iterator find(T* item) const;	//Ideal solution would be the use of smart pointers to allow returning the iterators by reference
									//while assuring automatic destruction of any iterator on the loose.
	T* selectedElement ( unsigned int selected ); //return element at "selected" position. luca

	bool empty(); 
	unsigned int size() const; 
	void push_back(const T& item);
	friend Iterator& List<T, PoolSize>::Iterator::remove();

	//typedef bool(*FindPredicate)(T*); 
	//Iterator& find(FindPredicate predicate); 
}; 

#include "List_Imp.h"

#endif