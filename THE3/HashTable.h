#include<iostream>
#include<string>
using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H



template<class Item>
class HashTable{

public:
    explicit HashTable(int capacity);
    Item & find( const Item & item ) const;
    void makeEmpty( );
    void insert( const Item & item);
    void remove( const Item & item );

    int getHashTableCapacity() const;
    int getHashTableSize() const;
    double getCurrentLoadFactor() const;


private:

    int size;
    int capacity;
    Item * hashTableArray;
    int findPosition(const Item & item) const;
    void rehash( );
};

//#include "HashTable.cpp"
double MAX_LOAD_FACTOR = 0.5;

template<class Item>
HashTable<Item>::HashTable(int initialCapacity){
    size = 0;
    capacity = initialCapacity;
    hashTableArray = new Item[capacity];
    for(int i=0; i<initialCapacity; i++){
        hashTableArray[i] = Item();
    }
}

template<class Item>
double HashTable<Item>::getCurrentLoadFactor() const {
    double currentLoadFactor = double(size) / double(capacity);
    return currentLoadFactor;
}

template<class Item>
int HashTable<Item>::getHashTableCapacity() const {
    return capacity;
}

template<class Item>
int HashTable<Item>::getHashTableSize() const {
    return size;
}


template<class Item>
Item & HashTable<Item>::find(const Item & item) const {
    int position = findPosition(item);
    return hashTableArray[position];
}

template<class Item>
void HashTable<Item>::remove(const Item &item) {
    int position = findPosition(item);
    hashTableArray[position] = NULL;
}

template<class Item>
int HashTable<Item>::findPosition(const Item & item) const {
    int collisionCount = 0;
    int position = item.hash(capacity);
    while ((! hashTableArray[position].empty()) && hashTableArray[position] != item){
        position = position + 2*++collisionCount-1;
        if(position >= capacity){
            position = position - capacity;
        }
    }
    return position;
}

template<class Item>
void HashTable<Item>::insert(const Item & item){
    int position = findPosition(item);
    hashTableArray[position] = item;
    size += 1;
    if(size >= (capacity*MAX_LOAD_FACTOR)){
        rehash();
    }
}

template<class Item>
void HashTable<Item>::makeEmpty() {
    for(int i = 0; i<capacity; i++){
        hashTableArray[i] = Item();
    }
}

int power(int x, unsigned int y, int p)
{
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
    // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns false if n is
// probably prime.
// d is an odd number such that  d*2<sup>r</sup> = n-1
// for some r >= 1
bool miillerTest(int d, int n)
{
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);

    // Compute a^d % n
    int x = power(a, d, n);

    if (x == 1  || x == n-1)
        return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)      return false;
        if (x == n-1)    return true;
    }

    // Return composite
    return false;
}

// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k)
{
    // Corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Iterate given nber of 'k' times
    for (int i = 0; i < k; i++)
        if (!miillerTest(d, n))
            return false;

    return true;
}
int nextPrime(int n)
{
    if (n % 2 == 0 )
    {
        n++;
    }
    while(!isPrime(n,4))
    {
        n+=2;
    }
    return n;
}


template<class Item>
void HashTable<Item>::rehash() {
    int newCapacity = nextPrime(2*capacity);
    Item * newHashTableArray = new Item[newCapacity];
    int position;
    for(int i=0; i<capacity; i++){
        Item & item = hashTableArray[i];
        if(!item.empty()){
            int collisionCount = 0;
            position = item.hash(newCapacity);
            while((! newHashTableArray[position].empty()) && newHashTableArray[position] != item ){
                position = position + 2*++collisionCount-1;
                if(position >= newCapacity){
                    position = position - newCapacity;
                }
            }
            newHashTableArray[position] = item;
        }
    }
    delete [] hashTableArray;
    hashTableArray = newHashTableArray;
    double currentLoadFactor = double(size) / double(newCapacity);
    cout<<"rehashed..."<<endl;
    cout<<"previous table size:"<<capacity<<", new table size: "<<newCapacity<<", current unique word count "<<size<<", current load factor: "<<currentLoadFactor<<endl;
    capacity = newCapacity;
}




#endif //HASHTABLE_H
