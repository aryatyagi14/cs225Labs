/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
    elems = elems + 1;
    bool b = shouldResize();
    if (b) {
        resizeTable();
    }
    unsigned int hash = hashes::hash(key,size);
    while(should_probe[hash]) {
        hash++;
        hash= hash% size;
    }
    if (table[hash] == NULL) {
        table[hash] = new std::pair<K,V>(key,value);
    }
    else {
        table[hash]-> first = key;
        table[hash] -> second= value;
    }
    should_probe[hash] = true;
    //(void) key;   // prevent warnings... When you implement this function, remove this line.
//(void) value; // prevent warnings... When you implement this function, remove this line.
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
    should_probe[findIndex(key)] = 0;
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    unsigned int hash = hashes::hash(key,size);
    unsigned int start = hashes::hash(key,size);
    while(true) {
        if (should_probe[hash] && table[hash]-> first == key) {
            return hash;
        }
        hash++;
        hash= hash% size;
        if (!(hash != start) )                   {
            return -1;
        }

    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
   size_t temp_size = findPrime(2*size);
	 std::pair<K,V>** temp_table = new std::pair<K,V>*[temp_size];
	 delete[] should_probe;
	 should_probe = new bool[temp_size];
	 size_t i = 0;
	 while(i<temp_size)
	 {
	 should_probe[i] = false;
	 temp_table[i] = NULL;
	 i++;
	 }
	 size_t i2 = 0;
	 while(i2<size)
	 {
	 //bool temp3 = table[i] != NULL;
	 if(table[i2] != NULL)
	 {
	 size_t idx = hashes::hash(table[i2]->first, temp_size);
	 //bool temp4 = temp_table[idx] != NULL;
	 while(temp_table[idx] != NULL)
	 {
	 idx += 1;
	 idx %= temp_size;
	 }
	
	 temp_table[idx] = table[i2];
	 should_probe[idx] = true;
	 }
	
	 i2++;
	 }
	 delete[] table;
	 table = temp_table;
	 size = temp_size;
}
