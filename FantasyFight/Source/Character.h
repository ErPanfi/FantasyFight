#ifndef FANTASYFIGHT_CHARACTER_H
#define FANTASYFIGHT_CHARACTER_H

class Character
{
public:
	enum AttributesEnum
	{
		STR = 0,
		DEX,
		INT,
		COUNT,
	};

	static const int MIN_ATTRIB_VALUE = 8;

private:

	int m_attributes[AttributesEnum::COUNT];
	int m_fatigue;
public:

	//attributes getter & setters
	int inline getAttrib(AttributesEnum attrib) const;
	int inline getAttribModifier(AttributesEnum attrib) const;
	void inline setAttrib(AttributesEnum attrib, int value);

	//fatigue getter & setter
	int inline getFatigue() const { return m_fatigue; }
	void inline setFatigue(int newValue) { m_fatigue = newValue; }
	//function for arbiter heap comparison
	static bool inline compareFatigue(const Character& lesser, const Character& greater);
};

#endif