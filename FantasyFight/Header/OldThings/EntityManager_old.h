#ifndef _Classes_EntityManager__
#define  _Classes_EntityManager_

#include "Entity_old.h"

class EntityNode{
private:
	Entity* ptrEntity;
	EntityNode* prev;
	EntityNode* next;
public:
	EntityNode ();
	EntityNode ( Entity* newEntity, EntityNode* prevNode, EntityNode* nextNode );

	~EntityNode();
	
	//set
	void setPtrChar(Entity* character){ptrEntity = character;}
	void setPrev(EntityNode* node){prev = node;}
	void setNext(EntityNode* node){next = node;}

	//get
	Entity* getPtrEntity(){return ptrEntity;}
	EntityNode* getPrev(){return prev;}
	EntityNode* getNext(){return next;}
};

class EntityNodeList{
private:
	EntityNode* rootEntityNode;
	EntityNode* lastEntityNode;

public:
	EntityNodeList();
	
	void addEntityNode(EntityNode* anEntityNode);
	void removeEntityNode(EntityNode* theNodeBeingRemoved);

	//set
	void setRootEntityNode(EntityNode* node){rootEntityNode = node;}
	void setLastEntityNode(EntityNode* node){lastEntityNode = node;}

	//get
	EntityNode* getRootGen(){return rootEntityNode;}
	EntityNode* getLastChar(){return lastEntityNode;}
};


#endif