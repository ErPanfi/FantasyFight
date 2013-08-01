#ifndef FANTASYFIGHT_IOMANAGER_H
#define FANTASYFIGHT_IOMANAGER_H

#include "OutputManager.h"
#include "InputManager.h"
#include "Entity.h"

class IOManager
{
public:
	static IOManager& instance ()
	{
		static IOManager istanceOPMan;
		return istanceOPMan;
	}

	~IOManager();

	//output management
	void manageOutput(Entity::EntityList& list, bool prefixNumbers = false);
	inline void manageOutput(Entity& entity)		{ manageOutput(entity.printEntity()); }
	void manageOutput(Printable* toPrint);
	inline void manageOutput(MyString &string)		{ manageOutput(new Printable(string)); }

	//input management
	void manageInput(Entity::EntityList& list, Entity** selection);
	void pressEnter();

private:

	IOManager();
	IOManager(const IOManager& copyOPMan );
	IOManager& operator= (const IOManager& copyOPMan );

	void unInit();
	void initFromOther(const IOManager& other);

	//IO spool implementation

	//output data structure
	struct OutputRecord
	{
		Printable* toPrint;
		OutputRecord(Printable* _toPrint) 
			: toPrint(_toPrint)
		{}
	};

	//input data structure
	struct InputRecord
	{
		Entity::EntityList choices;
		Entity**	selection;
		InputRecord(Entity::EntityList &_choices, Entity* &_selection)
			: selection(&_selection)
		{
			//copy the list content
			for(Entity::EntityList::Iterator iter = _choices.begin(); iter != choices.end(); ++iter)
			{
				choices.push_back(*iter.current());
			}
		}
		InputRecord()
			: selection(nullptr)
		{}
	};

	//uniform spooler data structure
	struct SpoolerRecord
	{
		bool isOutput;
		union _InOutRecordUnion
		{
			InputRecord* inputData;
			OutputRecord* outputData;
		} data;

		SpoolerRecord(OutputRecord* toOut)
			: isOutput(true)
		{
			data.outputData = toOut;
		}

		SpoolerRecord(InputRecord* toIn)
			: isOutput(false)
		{
			data.inputData = toIn;
		}

		SpoolerRecord()
			: isOutput(false)
		{
			data.inputData = nullptr;
		}
	};

	//define the spool queue
	static const unsigned int SPOOL_QUEUE_SIZE = 255;
	typedef List<SpoolerRecord, SPOOL_QUEUE_SIZE> SpoolQueue;
	
	SpoolQueue m_spoolQueue;

public:
	//spooler methods
	void flush();
};


#endif
