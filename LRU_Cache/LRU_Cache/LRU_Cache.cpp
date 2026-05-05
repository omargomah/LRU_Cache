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
			if (temp->data == item)
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
			if (temp->data == item)
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
			if (temp->data == item)
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
	K key;
	V value;
public:
	KeyValuePair(K key ,V value)
	{
		this->key = key;
		this->value = value;
	}
	bool operator==(const KeyValuePair& other) const {
		return key == other.key;
	}
	int GetValue()
	{
		return key;
	}
	int GetKey()
	{
		return key;
	}
	void PutValue(V value)
	{
		this->value = value;
	}

	
};

template <typename K, typename V>
class HashMap 
{
private:
	LinkedList<KeyValuePair<K, V>>* table;
	int capacity;

	int hashFunction(K key) {
		return (int)key % capacity;
	}

public:
	HashMap(int cap) {
		capacity = cap;
		table = new LinkedList<KeyValuePair<K, V>>[capacity];
	}


	void Put(K key, V value) {
		int index = hashFunction(key);
		KeyValuePair<K, V> kv( key, value );

		KeyValuePair<K, V> SearchResult = table[index].GetItemIfExist(kv);
		if (SearchResult != NULL) {
			SearchResult.PutValue(value);
			return;
		}
		table[index].Push(kv);
	}

	V* Get(K key) {
		int index = hashFunction(key);
		if(table[index] == NULL)
			return NULL;
		KeyValuePair<K, V> searchKey;
		searchKey.key = key;
		KeyValuePair<K, V> kv = table[index].GetItemIfExist(searchKey);
		return kv; 
	}

	void Remove(K key) {
		int index = hashFunction(key);
		KeyValuePair<K, V> kv;
		kv.key = key;
		int pos = table[index].GetIndexOfItem(kv);
		if (pos != -1) {
			table[index].RemoveAt(pos);
		}
	}
	~HashMap() {
		delete[] table;
	}
};
int main()
{
    cout << "Hello World!\n";
}
