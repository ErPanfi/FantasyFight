#ifndef FANTASYFIGHT_LIST_CPP
#define FANTASYFIGHT_LIST_CPP

#include "List.h"

//Iterator Class
template <typename T, unsigned int PoolSize>
void inline List<T,PoolSize>::Iterator::initFromNode (Node* node, Node* prev = nullptr)
{
	if(prev)
	{
		prevNode = prev;
	}
	else if(node == head)
	{
		prev = nullptr;
	}
	else if(node)
	{
		for(prev = head; prev && (prev->next != node); prev = prev->next);
	}	

	currentNode = node;
}

template <typename T, unsigned int PoolSize>
void inline List<T,PoolSize>::Iterator::initFromIterator (Iterator* inIterator)
{
	initFromNode( inIterator->currentNode, inIterator->prevNode);
}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::Iterator::Iterator()
{
	initFromNode(head);
}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::Iterator::Iterator(Node* node)
{
	initFromNode(node);
}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::Iterator::Iterator(Iterator& rhv)
{
	initFromIterator(rhv);
}

template <typename T, unsigned int PoolSize>
T* List<T,PoolSize>::Iterator::current()
{
	return currentNode;
}

template <typename T, unsigned int PoolSize>
void List<T,PoolSize>::Iterator::advance()
{
	if(currentNode->next)
	{
		initFromNode(currentNode->next, currentNode);
	}
}

template <typename T, unsigned int PoolSize>
typename List<T,PoolSize>::Iterator& List<T,PoolSize>::Iterator::operator=(const Iterator& rhv)
{
	if (this != rhv)
	{
	unInit();
	initFromIterator(rhv);
	}

	return *this;
	

}

template <typename T, unsigned int PoolSize>
bool List<T,PoolSize>::Iterator::operator==(const Iterator& rhv) const
{
	return currentNode == rhv.currentNode;
}

template <typename T, unsigned int PoolSize>
void List<T,PoolSize>::Iterator::operator++()
{
	advance();
}

template <typename T, unsigned int PoolSize>
typename List<T,PoolSize>::Iterator& List<T,PoolSize>::Iterator::remove()
{
	prevNode->next = currentNode->next;

	delete currentNode;
	
	initFromNode(prevNode->next, prevNode);

	return *this;
}


//List Class

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::List()
{

}

template <typename T, unsigned int PoolSize>
List<T,PoolSize>::~List()
{
	
}

template <typename T, unsigned int PoolSize>
T* List<T,PoolSize>::getNewObject()
{
	Node* newNode = nodePool.getNew();
	last->next = newNode;//valutare funzione
	last = newNode;
	counter++;
	return &(newNode -> object);
	
}

template <typename T, unsigned int PoolSize>
bool List<T,PoolSize>::empty()
{
	return (head == last) && (head == nullptr);
}

template <typename T, unsigned int PoolSize>
unsigned int List<T,PoolSize>::size()
{
	return counter;
}

template <typename T, unsigned int PoolSize>
typename List<T, PoolSize>::Iterator& List<T, PoolSize>::begin()
{
	//Iterator ret = head;

	return head;
}

template <typename T, unsigned int PoolSize>
typename List<T, PoolSize>::Iterator& List<T, PoolSize>::end()
{
	//Iterator ret = nullptr;

	return nullptr;
}

template <typename T, unsigned int PoolSize>
typename List<T, PoolSize>::Iterator& List<T, PoolSize>::find(T* item)
{
	Iterator iter = begin();

	while(!(iter == end() || iter.current() == item))
		iter.advance();

	return iter;
}

/*
template <typename T, unsigned int PoolSize>
typename List<T, PoolSize>::Iterator& List<T, PoolSize>::find(FindPredicate predicate)
{
	Iterator iter = begin();

	while(iter != end() && !FindPredicate(
}
*/

#endif