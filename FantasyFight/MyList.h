

template < typename T>
class MyList
{
protected:

	MyNode* root;
	MyNode* previus;
	MyNode* current;

	class MyNode
	{
	private:
		T object;
		MyNode* next;

	public:
		MyNode();
		MyNode(T newObject);
		~MyNode();

		T getObject () { return object };
		void setObject (T newObject) {};

		MyNode* getNext () { return next };
	}

public:

	MyList();
	~MyList();

	int count();
	void pushBack(T &object);
	void pushFront(T &object);

};
