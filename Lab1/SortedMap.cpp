#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

//Constructor
SortedMap::SortedMap(Relation r) {
    this->relation = r; //Assign the relation to the SortedMap object
    this->capacity = 2; //Assign the initial capacity to 2
    this->elements = new TElem[this->capacity]; //Allocate memory for an array of TElem with length capacity
    this->length = 0; //Assign the initial length to 0
}

//Add an element to the sorted map
//this function looks for the key in the map, and if it finds it,
//save the old value in oldValue, replace the value and return the old value
//if the length is equal to the capacity, we increase the capacity by resize
//if the key is not found, go to the place where it should be, shift to the right of the next key
// and add the key to its place and increase the length
//Best-case complexity: theta(1) - when the element to be added is already at the beginning of the array
//Average-case complexity: O(n) - when the element to be added is somewhere in the middle of the array
//Worst-case complexity: theta(n) - when the element to be added is at the end of the array
TValue SortedMap::add(TKey k, TValue v) {
    TElem e(k, v); //Create a new TElem object with key k and value v
    int i = 0; //Initialize index i to 0
    while (i < length && relation(elements[i].first, k))
    {
        //If the current element's key is equal to k, update its value and return the old value
        if (elements[i].first == k)
        {
            TValue oldValue = elements[i].second;
            elements[i].second = v;
            return oldValue;
        }
        i++; //Move to the next element
    }
    if (length == capacity)
    {
        resize_up(); //Double the capacity of the array if it is full
    }
    for (int j = length; j > i; j--)
    {
        elements[j] = elements[j - 1]; //Shift all elements to the right starting from the end of the array
    }
    elements[i] = e; //Insert the new TElem object at index i
    length++; //Increment the length of the array
    return NULL_TVALUE; //Return NULL_TVALUE as there was no old value to return
}

//Search for an element in the sorted map
//if the key is found, the value is returned
//Best-case complexity: theta(1) - when the element to be searched is at the beginning of the array
//Average-case complexity: O(n) - when the element to be searched is somewhere in the middle of the array
//Worst-case complexity: theta(n) - when the element to be searched is at the end of the array
TValue SortedMap::search(TKey k) const {
    int i = 0; //Initialize index i to 0
    while (i < length && k!=elements[i].first) {
        i++; //Move to the next element
    }
    if (i < length && elements[i].first == k) {
        return elements[i].second; //Return the value of the element if its key matches k
    }
    return NULL_TVALUE; //Return NULL_TVALUE if no element with key k is found
}

//Remove an element from the sorted map
//this function looks for the key in the map, and if it finds it,
//save the old value in oldValue, delete the key with the value and return the old value
//if the length is equal with 25%, we decrease the capacity by resize
//if the key is found, delete it, shift to the left of the next key
// and add the key to its place and increase the length
//Best-case complexity: theta(1) - when the element to be removed is at the beginning of the array
//Average-case complexity: O(n) - when the element to be removed is somewhere in the middle of the array
//Worst-case complexity: theta(n) - when the element to be removed is at the end of the array
TValue SortedMap::remove(TKey k) {
    // Start at the beginning of the elements array and iterate through it until k is found
    int i = 0;
    while (i < length && k != elements[i].first) {
        i++;
    }
    // If k is found, remove the element from the array and return its value
    if (i < length && elements[i].first == k) {
        TValue oldValue = elements[i].second;
        for (int j = i; j < length - 1; j++) {
            elements[j] = elements[j + 1];
        }
        length--;
        // If the length of the array is now 25% of its capacity, resize it down
        if (length == (capacity/4))
        {
            resize_down();
        }
        return oldValue;
    }
    // If k is not found, return NULL_TVALUE
    return NULL_TVALUE;
}

// Return the number of elements in the map
//Complexity: theta(n)
int SortedMap::size() const {
    return length;
}

// Return true if the map is empty (i.e., length is 0), false otherwise
//Complexity: theta(n)
bool SortedMap::isEmpty() const {
    if(length == 0)
        return true;
    return false;
}

// Return an iterator for the map
//Complexity: theta(1)
SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

// Destructor: delete the elements array
//Complexity: theta(n) - deleting an array
SortedMap::~SortedMap() {
    delete[] elements;
}

// Double the capacity of the elements array and copy all elements to the new array
//Complexity: theta(n) - copying all elements to a new array
void SortedMap::resize_up() {
    capacity *= 2;
    TElem* newElements = new TElem[capacity];
    for (int i = 0; i < size(); i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
}

// Halve the capacity of the elements array and copy all elements to the new array
//Complexity: theta(n) - copying all elements to a new array
void SortedMap::resize_down() {
    capacity /= 2;
    TElem* newElements = new TElem[capacity];
    for (int i = 0; i < size(); i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
}



// BONUS

//vector<TKey> SortedMap::keysInRange(TKey lo, TKey hi) const {
//    vector<TKey> keys;
//    for (int i = 0; i < length; i++) {
//        if (relation(lo, elements[i].first) && relation(elements[i].first, hi)) {
//            keys.push_back(elements[i].first);
//        }
//    }
//    return keys;
//}
//subalgorithm keysInRange(lo, hi)
//keys ← new vector of TKey
//for i ← 0 to length - 1 do
//if relation(lo, elements[i].first) and relation(elements[i].first, hi) then
//keys.push_back(elements[i].first)
//end if
//end for
//return keys
//end subalgorithm
