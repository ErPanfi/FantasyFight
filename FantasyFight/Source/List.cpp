
#include "List.h"

//Iterator Class
template <typename T, unsigned int PoolSize>
void inline List<T,PoolSize>::Iterator::initFromNode (Node* node, Node* prev = null)
{
	if(prev)
	{
		prevNode = prev;
	}
	else if(node == head)
	{
		prev = null;
	}
	else
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
	T* actualPoll = nodePool.getNew();
	*actualPoll = Node();
	last->next = actualPoll;//valutare funzione
	last = actualPoll;
	counter++;
	return actualPoll;
	
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


