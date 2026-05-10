#include <iostream>
#include <thread>
using namespace std;
#pragma region Single Linked List Implementation

template <typename T>
class SingleLinkedList
{
	struct Node
	{
		T data;
		Node* Next;
	};
	Node* Head;
public:
	SingleLinkedList()
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
	T* GetItemIfExist(int Key)
	{
		Node* temp = Head;
		while (temp != NULL)
		{
			if (temp->data.key == Key)
				return &(temp->data);
			temp = temp->Next;
		}
		return NULL;
	}
	int GetIndexOfItem(int key)
	{
		Node* temp = Head;
		int pos = 0;
		while (temp != NULL)
		{
			if (temp->data.key == key)
				return pos;
			temp = temp->Next;
			pos++;
		}
		return -1;
	}
	bool IsExist(int key)
	{
		Node* temp = Head;
		while (temp != NULL)
		{
			if (temp->data.key == key)
				return true;
			temp = temp->Next;
		}
		return false;
	}
	void DeleteAtFirst()
	{
		if (IsEmpty())
		{
			cout << "the SingleLinkedList is empty" << endl;
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
			cout << "the SingleLinkedList is empty" << endl;
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

#pragma endregion


#pragma region HashMap Implementation 

template <typename K, typename V>
class KeyValuePair 
{
public:
	K key;
	V value;
	KeyValuePair() { }
	KeyValuePair(K key ,V value)
	{
		this->key = key;
		this->value = value;
	}
};

template <typename K, typename V>
class HashMap 
{
private:
	SingleLinkedList<KeyValuePair<K, V>>* table;
	int capacity;
	int hashFunction(K key) {
		return (int)key % capacity;
	}

public:
	HashMap(int cap) 
	{
		capacity = cap;
		table = new SingleLinkedList<KeyValuePair<K, V>>[capacity];
	}
	 
	void Put(K key, V value) {
		int index = hashFunction(key);
		KeyValuePair<K, V>* SearchResult = table[index].GetItemIfExist(key);
		if (SearchResult != NULL) {
			SearchResult->value = value;
			return;
		}
		KeyValuePair<K, V> kv( key, value);
		table[index].InsertAtLast(kv);
	}

	V Get(K key) 
	{
		int index = hashFunction(key);
		if(table[index].IsEmpty())
			return NULL; 
		KeyValuePair<K, V>* kv = table[index].GetItemIfExist(key);
		return (kv != NULL) ? kv->value : NULL;
	}

	void Remove(K key) 
	{
		int index = hashFunction(key);
		if(table[index].IsEmpty())
			return; 
		int pos = table[index].GetIndexOfItem(key);
		if (pos != -1) 
			table[index].DeleteAtAnyPosition(pos);
	}	

	~HashMap() 
	{
		delete[] table;
	}
};

#pragma endregion


#pragma region LRU Cache Implementation

struct DoubleNode 
{
	int val;
	int key;
	DoubleNode* next;
	DoubleNode* prev;

	DoubleNode(int val = 0, int key = 0, DoubleNode* next = NULL, DoubleNode* prev = NULL) 
	{
		this->val = val;
		this->key = key;
		this->next = next;
		this->prev = prev;
	}
};

class LRUCache 
{
private:
	HashMap<int, DoubleNode*> Dict;
	DoubleNode* head, * back;
	int cap, count;

	void Track(int key) 
	{
		if (count > 1) 
		{
			DoubleNode* temp = Dict.Get(key);
			if (temp == head)
			{
				head = head->next;
				head->prev = NULL;
				temp->next = NULL;
				back->next = temp;
				temp->prev = back;
				back = temp;
			}
			else if (temp != back) 
			{
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
	LRUCache(int capacity) : Dict(capacity)
	{
		cap = capacity;
		count = 0;
		head = back = NULL;
	}
	int Get(int key) 
	{
		DoubleNode* nodePtr = Dict.Get(key);
		if (nodePtr != NULL) 
		{
			Track(key);
			return nodePtr->val;
		}
		return -1;
	}
	void Put(int key, int value) 
	{
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

			if (back == NULL) 
				back = head = node;
			else 
			{
				back->next = node;
				node->prev = back;
				back = node;
			}
			Dict.Put(key, node);
			count++;
		}
	}
	void Display() 
	{
		DoubleNode* current = back;
		cout << "[ RAM Content (Top:Back/Newest -> Bottom:Head/Oldest) ]: ";
		if (current == NULL) 
			cout << "Empty";
		cout << endl;
		while (current != NULL) 
		{
			cout << "[Page " << current->key << ": " << current->val << "]";
			if (current->prev != NULL) 
				cout << endl;
			current = current->prev;
		}
		cout << endl;
	}
	~LRUCache() 
	{
		DoubleNode* current = head;
		while (current != NULL) 
		{
			DoubleNode* next = current->next;
			delete current;
			current = next;
		}
	}
};

#pragma endregion


#pragma region Simulation of Virtual Memory Management using LRU Cache

class VirtualMemoryManager 
{
	LRUCache physicalRAM;          
	HashMap<int, int> disk;        
	int ramCapacity;
	int totalRequests;
	int pageFaults;

public:
	VirtualMemoryManager(int capacity): physicalRAM(capacity), disk(200)	
	{
		ramCapacity = capacity;
		totalRequests = 0;
		pageFaults = 0;
		for (int i = 0; i < 200; ++i)
			disk.Put(i, i * 10);
	}

	void AccessPage(int pageId) 
	{
		totalRequests++;
		cout << "\n[CPU Request]: Accessing Page " << pageId << "..." <<endl;
		int data = physicalRAM.Get(pageId);

		if (data != -1)
			cout << ">> Result: PAGE HIT. Data: " << data << " (Fetched from RAM)" <<endl;
		else 
		{
			pageFaults++;
			cout << ">> Result: PAGE FAULT! Page " << pageId << " not in RAM." << endl;

			cout << "   (Simulating custom HashMap Disk Read - 200ms) ";
			for (int i = 0; i < 10;i++)
			{
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(50));
			}
			cout << endl;
			int diskData = disk.Get(pageId);
			physicalRAM.Put(pageId, diskData);
			cout << "Page " << pageId << " loaded into RAM." << endl;
		}
		DisplayStats();
	}

	void DisplayStats() 
	{
		double hitRate = 0;
		if (totalRequests > 0) 
			hitRate = ((double)(totalRequests - pageFaults) / totalRequests) * 100;
		cout << "------------------------------------------" <<endl;
		cout << "STATS | Total Requests: " << totalRequests << " | Faults: " << pageFaults << "| Hits: "<< totalRequests - pageFaults << " | Hit Rate: " << hitRate << "%" <<endl;
		cout << "------------------------------------------" << std::endl;
		physicalRAM.Display();
	}
};

#pragma endregion


int main()
{
	VirtualMemoryManager vmm(3);
	cout << "   					  Virtual Memory Simulation 					    " << endl;
	int inputPage;
	while (true) 
	{
		cout << "\nEnter Page ID (0-199) or -1 to quit: ";
		cin >> inputPage;

		if (inputPage == -1)
			break;
		if (inputPage < 0 || inputPage > 199)
		{
			cout << "Invalid ID." << endl;
			continue;
		}
		vmm.AccessPage(inputPage);
	}

}
