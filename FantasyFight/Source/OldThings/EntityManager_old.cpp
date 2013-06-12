#include "EntityManager_old.h"

EntityNode::EntityNode()
{
	ptrEntity = nullptr;
	prev = nullptr;
	next = nullptr;
}

EntityNode::EntityNode(Entity* newEntity, EntityNode* prevNode, EntityNode* nextNode )
{
	ptrEntity = newEntity;
    prev = prevNode;
	next = nextNode;
}


// Di sotto implementiamo EntityNodeList

EntityNodeList::EntityNodeList()
{
	rootEntityNode = nullptr;
	lastEntityNode = nullptr;
}


void EntityNodeList::addEntityNode(EntityNode* anEntityNode)
{
	if (rootEntityNode == nullptr)
	{
		rootEntityNode = anEntityNode;
		lastEntityNode = anEntityNode;
		rootEntityNode->setPrev(nullptr);
		rootEntityNode->setNext(nullptr);
	}
	else
	{
		lastEntityNode->setNext(anEntityNode);
		anEntityNode->setPrev(lastEntityNode);
		lastEntityNode = anEntityNode;
		lastEntityNode->setNext(nullptr);
	}
	
}

void EntityNodeList::removeEntityNode(EntityNode* theNodeBeingRemoved)
{
	// se è il primo
	if (theNodeBeingRemoved == rootEntityNode)
	{
		rootEntityNode = rootEntityNode->getNext();
		//rootEntityNode->getPrev()->~EntityNode();
		rootEntityNode->setPrev(nullptr);
	}// se è l'ultimo
	else if (theNodeBeingRemoved == lastEntityNode)
	{
		lastEntityNode = lastEntityNode->getPrev();
		//lastEntityNode->getNext()->~EntityNode();
		lastEntityNode->setNext(nullptr);
	}
	else if(rootEntityNode == lastEntityNode)
	{
		rootEntityNode = nullptr;
		lastEntityNode = nullptr;
		//theNodeBeingRemoved->~EntityNode();//da vedere bug
	}
	else
	{
		theNodeBeingRemoved->getPrev()->setNext(theNodeBeingRemoved->getNext());
		theNodeBeingRemoved->getNext()->setPrev(theNodeBeingRemoved->getPrev());
		//theNodeBeingRemoved->~EntityNode();//bug
	}

	return;
}