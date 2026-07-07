# Data Structures & Pointers Notes (C → Java)

These notes show how C works interally

## Memory

### Stack

-   Local variables
-   Automatically managed

### Heap

-   Dynamically allocated objects
-   In C: malloc/free
-   In Java: JVM + Garbage Collector

## Pointers

A pointer stores an address, not the value.

``` c
int x = 5;
int *p = &x;
```

`p` points to `x`.

Dereferencing:

``` c
*p
```

means "go to that address and read the value."

### Multiple pointers

``` c
node *a = malloc(sizeof(node));
node *b = a;
```

Both point to the same object.

Calling `free(a)` frees the object. `b` becomes a dangling pointer too.

## Linked List

Each node contains: - data - pointer to next node

    Apple
     |
     v
    Banana
     |
     v
    Cat
     |
    NULL

Search: O(n)

Insert at head: O(1)

## Hash Tables

Pipeline:

    Key
     ↓
    Hash Function
     ↓
    Bucket

Buckets may contain linked lists when collisions occur.

Example:

    Bucket 4

    Apple
     |
    Ant
     |
    Air
     |
    NULL

Searching: 1. Hash key. 2. Jump to bucket. 3. Walk only that bucket.

Average lookup: O(1)

## Good Hash Function

Properties: - Same input → same output - Even distribution - Fast

Example:

``` c
hash = hash * 31 + tolower(c);
return hash % N;
```

## Binary Search Tree

          50
        /    \
       30     70
      / \    / \
    20 40  60 80

Left \< Current \< Right.

Average search: O(log n)

## Java Connection

### HashMap

Internally uses: - array of buckets - linked lists - tree for crowded
buckets (Java 8+)

### ArrayList

Dynamic array.

### LinkedList

Doubly linked list.

### TreeMap

Balanced red-black tree.

## Big-O

  Structure      Search     Insert
  -------------- ---------- --------------
  Array          O(n)       O(1) at end
  Linked List    O(n)       O(1) at head
  Hash Table     O(1) avg   O(1) avg
  Balanced BST   O(log n)   O(log n)

## Key Takeaways

-   Pointers store addresses.
-   free() frees memory, not pointers.
-   Linked lists connect nodes with pointers.
-   Hash tables use hash functions to jump near the data.
-   Java uses the same ideas but hides memory management.
