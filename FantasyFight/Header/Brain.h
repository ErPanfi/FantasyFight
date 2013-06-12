#ifndef FANTASYFIGHT_BRAIN_H
#define FANTASYFIGHT_BRAIN_H

class Character;

class Brain
{
private:
	Character* m_owner;
public:

	//ownership management
	Character*	getOwner() const				{ return m_owner; }
	void		setOwner(Character* newOwner)	{ m_owner = newOwner; }

	friend class Character;
};

#endif