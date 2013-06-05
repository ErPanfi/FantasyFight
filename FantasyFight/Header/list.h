template <typename T, unsigned int Size> class Pool
{
	Pool<T, Size>* next; 
public: 
	Pool(); 
	~Pool(); 
	T* getNew(); 
	void free(T* item); 
}; 

template <typename T, unsigned int PoolSize> class List
{
protected: 
	typedef Pool<Node<T> , PoolSize > NodePool; 
	struct Node
	{
	public: 
		T object; 
		Node* next; 
		Node(); 
	}; 
public: 
	class Iterator
	{
	private: 
		Node* currentNode; 
	public: 	
		Iterator(); 
		Iterator(Node* node); 
		Iterator(Iterator& rhv); 
		T* current(); 
		void advance(); 
		Iterator& remove(); 
		Iterator& operator=(Iterator& rhv); 
		bool operator==(Iterator& rhv); 
	}; 
	typedef bool(*FindPredicate)(T*); 
protected: 
	Node* head; 	
	NodePool nodePool; 
public: 
	List(); 
	~List()

	T* getNewObject(); 
	bool empty(); 
	unsigned int size(); 
	Iterator& begin(); 
	Iterator& end(); 
	Iterator& find(T* item); 
	Iterator& find(FindPredicate predicate); 
}; 