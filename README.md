DSLIB
=====

Although not yet complete, Dslib, or Data Structure Library, will be a fast, easy-to-use, versatile and rich data structures library for C. Each data structure is independent from the library, so incorporating the data structures into your source code is as simple as copy-pasting the source files and configuring them in the header files.

They are a lot missing data structures yet, but the ones that are already implemented are guaranteed to work!

The following data structures are implemented:
 - Red-Black Tree

The following data structures will be implemented in the near future:
 - Bit-map Array
 - Heap
 - Linked List
 - Hash Table

#Conventions#
Influenced by the object-oriented languages, all data structures will be represented by an opaque structure and all data-manipulating functions will resemble "methods" of the said data structures. What it means is that if you are given a function of `rbtree_add`, you could expect that the function will behave like a public method of `rbtree` object. But, of course, C cannot behave in object-oriented manner, so you can reasonably expect that the function will receive a pointer to `rbtreee`, a key and a value as arguments.