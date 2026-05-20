# LRU Cache

A high-performance implementation of an **LRU (Least Recently Used) Cache** in **C++** using **Microsoft Visual Studio**.

## Overview

This project demonstrates how an LRU Cache works internally using efficient data structures to achieve fast operations.

An LRU Cache removes the **least recently used** item when the cache reaches its maximum capacity.

Typical applications include:

* Operating systems
* Database systems
* Web browsers
* Memory management
* API caching

---

## Features

* Fast insertion and retrieval
* Automatic eviction of least recently used items
* O(1) average time complexity for:

  * `get()`
  * `put()`
* Implemented in modern C++
* Built with Visual Studio 2022

---

## Technologies Used

* C++
* STL (`unordered_map`, `list`)
* Visual Studio 2022

---

## Project Structure

```text
LRU_Cache/
│
├── LRU_Cache.sln                # Visual Studio solution file
│
└── LRU_Cache/
    ├── LRU_Cache.vcxproj        # Visual Studio C++ project
    ├── main.cpp                 # Main source file
    └── ...                      # Additional source/header files
```

---

## How LRU Cache Works

The cache stores recently accessed items.

When:

* An item is accessed → it becomes the most recently used
* The cache is full → the least recently used item is removed

### Data Structures Used

| Data Structure       | Purpose              |
| -------------------- | -------------------- |
| `unordered_map`      | Fast key lookup      |
| `doubly linked list` | Maintain usage order |

This combination allows all operations to work efficiently.

---

## Example

```cpp
LRUCache cache(2);

cache.put(1, 10);
cache.put(2, 20);

cache.get(1);     // returns 10

cache.put(3, 30); // removes key 2

cache.get(2);     // returns -1
```

---

## Build & Run

### Using Visual Studio

1. Open `LRU_Cache.sln`
2. Select:

   * `Debug` or `Release`
   * `x64` or `x86`
3. Press:

   * `Ctrl + F5` to run

---

## Requirements

* Visual Studio 2022
* C++17 or later

---

## Future Improvements

* Add unit testing
* Add thread-safe version
* Add TTL expiration support
* Benchmark performance
* Generic template implementation

---

## Learning Objectives

This project helps in understanding:

* Cache replacement policies
* Hash maps
* Doubly linked lists
* Time complexity optimization
* System design fundamentals

---

## Authors

**Omar Gomah**,
**Abdullah Said**,
**Abdullah Adel**,
**Essam Mohammed**

Computer & Communications Engineering Students at Benha Faculty of Engineering

