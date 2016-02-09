# COP3530-Data-structure-and-Algorithms

Description
-----------------------
Algorithm development using pseudo languages, basic program structures, program design techniques, storage and manipulation of basic data structures like arrays, stacks, queues, sorting and searching and string processing. Linked linear lists. Trees and multilinked structures.

HomeWork
-----------------------

Project
-----------------------
All programming assignments are to be tested using the g++ (GNU C++) compiler v4.8.2 running on OpenBSD 5.5 (i386).

+ Project 1:
  - Part I: Lists - Design, implement, and thoroughly test all four varieties of list classes:
    * The List varieties
      * Simple Singly-Linked List (SSLL)
      * Pool-using Singly-Linked List (PSLL)
      * Simple Dynamic Array-based List (SDAL)
      * Chained Dynamic Array-based List (CDAL)
    * List operations
      * replace( element, position )
      * insert( element, position )
      * push_back( element )
      * push_front( element )
      * remove( position )
      * pop_back()
      * pop_front()
      * item_at( position )
      * is_empty()
      * size() 
      * clear()
      * contains( element, equals_function )
      * print( ostream )
  - Part II: Extend the list implementations to support new members and include support for iterators.
    * begin()
    * end()
    * List iterators (SSLL_Const_Iter, SSLL_Iter)
  - Part III: Extend the list implementations to support the subscript operator, throw appropriate exceptions, and develop a comprehensive set of unit tests.
    * Overload the subscript operator
      * T& operator[](int i)
      * T const& operator[](int i) const
    * Unit Tests - CATCH unit testing framework

+ Project 2: 
  - Part I: Hash map with open addressing: Design, implement, and thoroughly test an open addressing hash map. At this time, the map need handle only keys of type int and values of type char.
    * bool insert( key, value )
    * bool remove( key, &value )
    * bool search( key, &value )
    * void clear()
    * is_empty()
    * std::size_t capacity()
    * std::size_t size()
    * double load()
    * print( ostream )
  
  - Part II: Hash map with buckets: Design, implement, and thoroughly test an bucket-based hash map. At this time, the map need handle only keys of type int and values of type char.
    * bool insert( key, value )
    * bool remove( key, &value )
    * bool search( key, &value )
    * void clear()
    * is_empty()
    * std::size_t capacity()
    * std::size_t size()
    * double load()
    * print( ostream& )
    
  - Part III: Hash map with open addressing: Design, implement, and thoroughly test a hash map that supports all three of the open addressing techniques we discussed and handle multiple key types.
    * Open addressing techniques
      * hash( key, i ) = hash( key ) + i * probe( key )
        linear probing: probe( key ) = 1
        quadratic probing: probe( key ) = i
        rehashing: probe( key ) = hash2( key )
    * Hash functions
      * signed int
      * double
      * c-string — a char *
      * std::strin
    * Equality functions
  Map key & value types
    * Key types
      * signed int
      * double
      * c-string — a char *.
      * std::string
    * Revised hash map operations
      * int insert( key, value )
      * int remove( key, &value)
      * int search( key, &value )
    * New hash map operations
      * ??? cluster_distribution()
      * Key remove_random()

  - Part IV: Compare the performance of different hash functions, capacity effects, collision avoidance methods, open addressing vs randomized binary search tree. These performance were tested with real statistics data, GNUPLOT was used to generate graphs.
