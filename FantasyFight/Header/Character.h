#ifndef FANTASYFIGHT_CHARACTER_H
#define FANTASYFIGHT_CHARACTER_H

enum g_AttributesEnum
{
	STR = 0,
	DEX,
	INT,
	COUNT_ATTRIB,
};

static const int MIN_ATTRIB_VALUE = 8;



class Character
{
private:


	int m_attributes[g_AttributesEnum::COUNT_ATTRIB];
	int m_fatigue;
public:

	//attributes getter & setters
	int inline getAttrib(g_AttributesEnum attrib) const;
	int inline getAttribModifier(g_AttributesEnum attrib) const;
	void inline setAttrib(g_AttributesEnum attrib, int value);

	//fatigue getter & setter
	int inline getFatigue() const { return m_fatigue; }
	void inline setFatigue(int newValue) { m_fatigue = newValue; }
	//function for arbiter heap comparison
	static bool inline compareFatigue(Character* &lesser, Character* &greater);	
};

#endif