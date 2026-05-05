#include <iostream>
using namespace std;
template <class T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* Next;
	};
	Node* Head;
public:
	LinkedList()
	{
		Head = NULL;
	}
	bool IsEmpty()
	{
		return Head == NULL;
	}
	int Count()
	{
		int i = 0;
		Node* temp = Head;
		while (temp != NULL)
		{
			i++;
			temp = temp->Next;
		}
		return i;
	}
	void InsertAtFirst(T item)
	{
		Node* newNode = new Node;
		newNode->data = item;
		newNode->Next = Head;;
		Head = newNode;
	}
	void InsertAtLast(T item)
	{
		if (IsEmpty())
		{
			InsertAtFirst(item);
			return;
		}
		Node* temp = Head, * newNode = new Node;
		newNode->data = item;
		newNode->Next = NULL;
		while (temp->Next != NULL)
			temp = temp->Next;
		temp->Next = newNode;
	}
	void InsertAtAnyPosition(int pos, T item)
	{
		int size = Count();
		if (pos < 0 || pos > size)
			cout << "the index out of range" << endl;
		else if (pos == 0)
			InsertAtFirst(item);
		else if (pos == size)
			InsertAtLast(item);
		else
		{
			Node* temp = Head, * newNode = new Node;
			newNode->data = item;
			for (int i = 0; i < pos - 1; i++)
				temp = temp->Next;
			newNode->Next = temp->Next;
			temp->Next = newNode;
		}
	}
	void Display()
	{
		Node* temp = Head;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->Next;
		}
		cout << endl;
	}
	T GetItemIfExist(T item)
	{
		Node* temp = Head;
		while (temp != NULL)
		{
			if (*(temp->data) == *item)
				return temp->data;
			temp = temp->Next;
		}
		return NULL;
	}
	int GetIndexOfItem(T item)
	{
		Node* temp = Head;
		int pos = 0;
		while (temp != NULL)
		{
			if (*(temp->data) == *item)
				return pos;
			temp = temp->Next;
			pos++;
		}
		return -1;
	}
	bool IsExist(T item)
	{
		Node* temp = Head;
		while (temp != NULL)
		{
			if (*(temp->data) == *item)
				return true;
			temp = temp->Next;
		}
		return false;
	}

	void DeleteAtFirst()
	{
		if (IsEmpty())
		{
			cout << "the LinkedList is empty" << endl;
			return;
		}
		Node* deleted = Head;
		Head = Head->Next;
		delete deleted;
	}
	void DeleteAtLast()
	{
		if (IsEmpty())
		{
			cout << "the LinkedList is empty" << endl;
			return;
		}
		Node* deleted = Head, * prev = NULL;
		while (deleted->Next != NULL)
		{
			prev = deleted;
			deleted = deleted->Next;
		}
		if (prev == NULL)
			DeleteAtFirst();
		else
		{
			prev->Next = NULL;
			delete deleted;
		}
	}
	void DeleteAtAnyPosition(int pos)
	{
		int size = Count();
		if (pos < 0 || pos >(size - 1))
			cout << "the index out of range" << endl;
		else if (pos == 0)
			DeleteAtFirst();
		else if (pos == size - 1)
			DeleteAtLast();
		else
		{
			Node* prev = Head, * deleted = NULL;
			for (int i = 0; i < pos - 1; i++)
				prev = prev->Next;
			deleted = prev->Next;
			prev->Next = deleted->Next;
			delete deleted;
		}
	}
	void Reverse()
	{
		if (IsEmpty())
			return;
		Node* prev = NULL, * cur = Head, * next = Head;
		while (cur != NULL)
		{
			next = cur->Next;
			cur->Next = prev;
			prev = cur;
			cur = next;
		}
		Head = prev;
	}
};

template <typename K, typename V>
class KeyValuePair 
{
public:
	K key;
	V value;
	KeyValuePair(K key ,V value)
	{
		this->key = key;
		this->value = value;
	}
	bool operator==(KeyValuePair other) const {
		return key == other.key;
	}
};

template <typename K, typename V>
class HashMap 
{
private:
	LinkedList<KeyValuePair<K, V>*>* table;
	int capacity;

	int hashFunction(K key) {
		return (int)key % capacity;
	}

public:
	HashMap(int cap) {
		capacity = cap;
		table = new LinkedList<KeyValuePair<K, V>*>[capacity];
	}


	void Put(K key, V value) {
		int index = hashFunction(key);
		KeyValuePair<K, V>* kv  = new KeyValuePair<K,V>( key, value);

		KeyValuePair<K, V>* SearchResult = table[index].GetItemIfExist(kv);
		if (SearchResult != NULL) {
			SearchResult->value = value;
			return;
		}
		table[index].InsertAtLast(kv);
	}

	V Get(K key) {
		int index = hashFunction(key);
		if(table[index].IsEmpty())
			return NULL;
		KeyValuePair<K, V>* searchKey = new KeyValuePair<K,V>(key,0); 
		KeyValuePair<K, V>* kv = table[index].GetItemIfExist(searchKey);
		return (kv != NULL) ? kv->value : NULL;
	}

	void Remove(K key) {
		int index = hashFunction(key);
		KeyValuePair<K, V>* kv = new KeyValuePair<K, V>(key,0);
		kv->key = key;
		int pos = table[index].GetIndexOfItem(kv);
		if (pos != -1) {
			table[index].DeleteAtAnyPosition(pos);
		}
	}
	~HashMap() {
		delete[] table;
	}
};


class DoubleNode {
public:
	int val;
	int key;
	DoubleNode* next;
	DoubleNode* prev;

	DoubleNode(int val = 0, int key = 0, DoubleNode* next = nullptr, DoubleNode* prev = nullptr) {
		this->val = val;
		this->key = key;
		this->next = next;
		this->prev = prev;
	}
};

class LRUCache {
private:
	HashMap<int, DoubleNode*> Dict;
	DoubleNode* head, * back;
	int cap, count;

	void Track(int key) {
		if (count > 1) {
			DoubleNode* temp = Dict.Get(key);
			if (temp == head) {
				head = head->next;
				head->prev = NULL;
				temp->next = NULL;
				back->next = temp;
				temp->prev = back;
				back = temp;
			}
			else if (temp != back) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->prev = back;
				back->next = temp;
				temp->next = NULL;
				back = temp;
			}
		}
	}

public:
	LRUCache(int capacity) :Dict(capacity)
	{
		cap = capacity;
		count = 0;
		head = back = nullptr;
	}


	int Get(int key) {
		DoubleNode* nodePtr = Dict.Get(key);
		if (nodePtr != NULL) {
			Track(key);
			return nodePtr->val;
		}
		return -1;
	}

	void Put(int key, int value) {
		DoubleNode* existingNode = Dict.Get(key);
		if (existingNode != NULL) 
		{
			existingNode->val = value;
			Track(key);
		}
		else 
		{
			DoubleNode* node = new DoubleNode(value, key);
			if (count == cap) 
			{
				Dict.Remove(head->key);
				DoubleNode* toDelete = head;
				if (count == 1) 
					back = head = NULL;
				else 
				{
					head = head->next;
					head->prev = NULL;
				}
				delete toDelete;
				count--;
			}

			if (back == NULL) {
				back = head = node;
			}
			else {
				back->next = node;
				node->prev = back;
				back = node;
			}
			Dict.Put(key, node);
			count++;
		}
	}

	~LRUCache() {
		DoubleNode* current = head;
		while (current != nullptr) {
			DoubleNode* next = current->next;
			delete current;
			current = next;
		}
	}
};


int main()
{

#pragma region First Test Case
	
	// LRUCache lruCache = new LRUCache(2);
	//LRUCache cache(2);

	//cout << "put(1, 10): "; cache.Put(1, 10);
	//// Cache state: {1=10} (head=1, back=1)
	//cout << "null" << endl;

	//cout << "get(1): ";
	//cout << cache.Get(1) << endl; // Returns 10
	//// Cache state: {1=10} (head=1, back=1)

	//cout << "put(2, 20): "; cache.Put(2, 20);
	//// Cache state: {1=10, 2=20} (head=1, back=2)
	//cout << "null" << endl;

	//cout << "put(3, 30): "; cache.Put(3, 30);
	//// Cache state: {2=20, 3=30}, Key 1 evicted (head=2, back=3)
	//cout << "null" << endl;

	//cout << "get(2): ";
	//cout << cache.Get(2) << endl; // Returns 20
	//// Cache state: {3=30, 2=20} (head=3, back=2)

	//cout << "get(1): ";
	//cout << cache.Get(1) << endl; // Returns -1 (not found)

#pragma endregion

#pragma region Second Test Case

	LRUCache cache(3);

	cout << "--- Starting Large Test Case ---" << endl;

	// 1. Fill the cache to capacity
	cout << "Put(1, 10), Put(2, 20), Put(3, 30)" << endl;
	cache.Put(1, 10);
	cache.Put(2, 20);
	cache.Put(3, 30);
	// State: [1, 2, 3] (3 is MRU)

	// 2. Access the oldest element (1) to make it the newest
	cout << "Get(1): " << cache.Get(1) << " (Expected: 10)" << endl;
	// State: [2, 3, 1] (1 is now MRU)

	// 3. Add a new element to trigger eviction
	cout << "Put(4, 40) - Should evict Key 2" << endl;
	cache.Put(4, 40);
	// State: [3, 1, 4]

	// 4. Verify Key 2 is gone
	cout << "Get(2): " << cache.Get(2) << " (Expected: -1)" << endl;

	// 5. Update an existing value (Key 3)
	cout << "Put(3, 300) - Updates 3 and makes it MRU" << endl;
	cache.Put(3, 300);
	// State: [1, 4, 3]

	// 6. Rapid additions to test sequential eviction
	cout << "Put(5, 50), Put(6, 60)" << endl;
	cache.Put(5, 50); // Evicts 1. State: [4, 3, 5]
	cache.Put(6, 60); // Evicts 4. State: [3, 5, 6]

	// 7. Final Verification
	cout << "\n--- Final State Check ---" << endl;
	cout << "Get(3): " << cache.Get(3) << " (Expected: 300)" << endl;
	cout << "Get(4): " << cache.Get(4) << " (Expected: -1)" << endl;
	cout << "Get(5): " << cache.Get(5) << " (Expected: 50)" << endl;
	cout << "Get(6): " << cache.Get(6) << " (Expected: 60)" << endl;

#pragma endregion


}
