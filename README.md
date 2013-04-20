# CHashTable
Basic implementation of hashtable in C++ and QT. Convenient for testing families of hash functions.

Allows to change hash functions easily. Hash functions allow setting their parameters in run-time. It is written to allow easy addition of new hash functions. Only djb2 is provided.

## Usage example
    // Incluse these in header
    #include <hashfunction.h>
    #include "hashtable.cpp"

    // Initialize hash functions and hash table
    uint tableSize = 757;
    CHashFunction::djb2_factor = 31;
    CHashFunction::djb2_initial_hash = 5831; 
    CHashtable<QString> table(tableSize);

    // Optionaly, set default hash function:
    table.setHashFunction(CHashFunction::djb2_hashFunction);

    // Then use it. If hash function is given, the given one takes precedence before default one.
    table.insert(item);
    table.insert(item,CHashFunction::djb2_hashFunction);

## Licensing
CHashTable is distributed under MIT licence as stated on http://opensource.org/licenses/MIT, which is very permissive. You can do anything you like with this code. Commercial use is allowed. See LICENCE file for details.

## Copyright
Copyright (c) 2013 Matej Zavrsnik <matejzavrsnik.com>