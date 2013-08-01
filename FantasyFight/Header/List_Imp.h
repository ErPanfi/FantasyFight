#ifndef FANTASYFIGHT_LIST_CPP
#define FANTASYFIGHT_LIST_CPP

#include "List.h"

//Iterator Class
template <typename T, unsigned int PoolSize>
void List<T,PoolSize>::Iterator::initFromNode (Node* node, const List<T, PoolSize> *owner, Node* prev = nullptr)
{
	if(prev)
	{
		m_prevNode = prev;
	}
	else if(node == owner -> head)
	{
		m_prevNode = nullptr;
	}
	else if(node)
	{
		for(prev = owner -> head; prev && (prev->next != node); prev = prev->next);
	}	
	else
	{
		m_prevNode = nullptr;
	}

	m_owner = const_cast<List<T, PoolSize>*>(owner);

	m_currentNode = node;
}

template <typename T, unsigned int PoolSize>
void inline List<T,PoolSize>::Iterator::initFromIterator (const Iterator* inIterator)
{
	initFromNode( inIterator->m_currentNode, inIterator -> m_owner, inIterator->m_prevNode);
}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::Iterator::Iterator()
{
}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::Iterator::Iterator(List<T, PoolSize> *owner, Node* node)
{
	initFromNode(node, owner);
}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::Iterator::Iterator(Iterator& rhv)
{
	initFromIterator(&rhv);
}

template <typename T, unsigned int PoolSize>
T* List<T,PoolSize>::Iterator::current()
{
	return m_currentNode ? &(m_currentNode -> object) : nullptr;
}

template <typename T, unsigned int PoolSize>
void List<T,PoolSize>::Iterator::advance()
{
	if(m_currentNode)
	{
		m_prevNode = m_currentNode;
		m_currentNode = m_currentNode -> next;
	}
}

template <typename T, unsigned int PoolSize>
void List<T,PoolSize>::Iterator::advance(unsigned int val)
{
	for ( ;val > 0; --val)
		advance();
}

template <typename T, unsigned int PoolSize>
typename List<T,PoolSize>::Iterator& List<T,PoolSize>::Iterator::operator=(const Iterator& rhv)
{
	if (this != &rhv)
	{
		unInit();
		initFromIterator(&rhv);
	}

	return *this;
	

}

template <typename T, unsigned int PoolSize>
bool List<T,PoolSize>::Iterator::operator==(const Iterator& rhv) const
{
	return m_currentNode == rhv.m_currentNode;
}

template <typename T, unsigned int PoolSize>
bool List<T,PoolSize>::Iterator::operator!=(const Iterator& rhv) const
{
	return !operator==(rhv);
}

template <typename T, unsigned int PoolSize>
typename List<T,PoolSize>::Iterator& List<T,PoolSize>::Iterator::operator++()
{
	advance();
	return *this;
}

template <typename T, unsigned int PoolSize>
typename List<T,PoolSize>::Iterator List<T,PoolSize>::Iterator::operator++(int)
{
	Iterator ret(*this);
	advance();
	return ret;
}

template <typename T, unsigned int PoolSize>
List<T, PoolSize>::Iterator::operator bool() const
{
	return m_currentNode || m_prevNode;
}

template <typename T, unsigned int PoolSize>
typename List<T,PoolSize>::Iterator& List<T,PoolSize>::Iterator::remove()
{
	if(m_currentNode && m_owner -> counter)
	{
		if(m_owner -> last == m_currentNode)
			m_owner -> last = m_prevNode;

		m_owner->counter--;
		Node* toFree = m_currentNode;

		if(m_prevNode)
		{
			m_prevNode -> next = m_currentNode->next;
			initFromNode(m_prevNode->next, m_owner, m_prevNode);
		}
		else if(m_owner -> counter)
		{
			m_owner -> head = m_currentNode->next;
			initFromNode(m_owner -> head, m_owner, m_prevNode);
		}
		else
		{
			m_owner -> head = nullptr;
			initFromNode(nullptr, m_owner);	//this will return end iterator
		}

		m_owner->nodePool.free(toFree);
	}

	return *this;
}


//List Class

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::List()
	: head(nullptr)
	, last(nullptr)
	, counter(0)
{

}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::~List()
{
	if(head)
	{
		//release all pool resources
		for(Node *currNode = head, *nextNode = currNode -> next; currNode; currNode = nextNode, nextNode = nextNode? nextNode -> next : nullptr)
			nodePool.free(currNode);
	}
}

template <typename T, unsigned int PoolSize>
T* List<T,PoolSize>::getNewObject()
{
	Node* newNode = nodePool.getNew();
	if(last)
		last->next = newNode;//valutare funzione
	else
		head = newNode;
	last = newNode;
	counter++;
	return &(newNode -> object);
	
}

template <typename T, unsigned int PoolSize>
void List<T, PoolSize>::push_back(const T& item)
{
	*(getNewObject()) = item;
}

template <typename T, unsigned int PoolSize>
bool List<T,PoolSize>::empty() const
{
	return (head == last) && (head == nullptr);
}

template <typename T, unsigned int PoolSize>
unsigned int List<T,PoolSize>::size() const
{
	return counter;
}

template <typename T, unsigned int PoolSize>
typename List<T, PoolSize>::Iterator List<T, PoolSize>::begin()  const
{
	List<T, PoolSize>::Iterator ret;		

	ret.initFromNode(head, this);

	return ret;		
}

template <typename T, unsigned int PoolSize>
typename List<T, PoolSize>::Iterator List<T, PoolSize>::end() const
{
	List<T, PoolSize>::Iterator ret;

	ret.initFromNode(nullptr, this);

	return ret;
}

template <typename T, unsigned int PoolSize>
typename List<T, PoolSize>::Iterator List<T, PoolSize>::find(T* item) const
{
	//this is a good search, independent from data structure
	/*		
	Iterator iter = begin();

	while(iter != end() || iter.current() == item))
		iter.advance();

	return iter;
	*/

	//but this is faster, and the find it's called many time in game flow
	Node* curr = head;
	Node* prev = nullptr;

	for(;curr && curr -> object != *item; prev = curr, ++curr);

	Iterator ret;

	ret.initFromNode(curr, this, prev);

	return ret;
}

template <typename T, unsigned int PoolSize>
T* List<T, PoolSize>::selectedElement( unsigned int selected )
{
	List<T, PoolSize>::Iterator tempIterator = begin();
    tempIterator.advance(selected);
	return tempIterator.current();

}

#endif