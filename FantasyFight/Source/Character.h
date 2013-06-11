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


private:

	int attributes[7];

public:

	int inline getAttrib(AttributesEnum attrib) const;
};

#endif