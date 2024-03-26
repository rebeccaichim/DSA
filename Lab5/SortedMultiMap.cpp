#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// Constructor for the SortedMultiMap class
// Time complexity: Theta(1)
SortedMultiMap::SortedMultiMap(Relation r)
{
    this->relation = r;
    this->root = NULL;
    this->sizeOfBST = 0;
}

// Resizes the values array of a node by doubling its capacity
// Time complexity: Theta(1)
void SortedMultiMap::resize(Node *node)
{
    node->capacity *= 2;
    TValue *newValues = new TValue[node->capacity];
    for (int i = 0; i < node->size; i++)
        newValues[i] = node->values[i];
    delete[] node->values;
    node->values = newValues;
}

// Initializes a new node with the given key and value
// Time complexity: Theta(1)
void SortedMultiMap::initNode(Node *node, TKey c, TValue v)
{
    node->key = c;
    node->size = 1;
    node->capacity = 1;
    node->values = new TValue[node->capacity];
    node->values[0] = v;
    node->left = NULL;
    node->right = NULL;
}

// Adds a new key-value pair to the sorted multi-map
// Time complexity:
//   - Best case: Theta(1) (when the tree is empty)
//   - Worst case: Theta(n) (when the tree is a skewed tree and we need to traverse the entire height)
//   - Average case: Theta(n) (when the tree is balanced)
void SortedMultiMap::add(TKey c, TValue v)
{
    if (this->root == NULL)
    {
        this->root = new Node;
        this->initNode(this->root, c, v);
        this->sizeOfBST++;
        return;
    }

    Node *currentNode = this->root;
    while (currentNode->key != c)
    {
        if (this->relation(c, currentNode->key))
        {
            if (currentNode->left == NULL)
            {
                currentNode->left = new Node;
                this->initNode(currentNode->left, c, v);
                this->sizeOfBST++;
                return;
            }
            else
                currentNode = currentNode->left;
        }
        else
        {
            if (currentNode->right == NULL)
            {
                currentNode->right = new Node;
                this->initNode(currentNode->right, c, v);
                this->sizeOfBST++;
                return;
            }
            else
                currentNode = currentNode->right;
        }
    }

    if (currentNode->size == currentNode->capacity)
        this->resize(currentNode);
    currentNode->values[currentNode->size] = v;
    currentNode->size++;
    this->sizeOfBST++;
}

// Searches for all values associated with the given key and returns them in a vector
// Time complexity:
//   - Best case: Theta(1) (when the key is at the root of the tree)
//   - Worst case: O(n) (when the key is not found or when the tree is a skewed tree and we need to traverse the entire height)
//   - Average case: Theta(height of BST + number of values with key c) (when the tree is balanced)
vector<TValue> SortedMultiMap::search(TKey c) const
{
    vector<TValue> values = vector<TValue>();
    Node *currentNode = this->root;
    while (currentNode != NULL)
    {
        if (currentNode->key == c)
        {
            for (int i = 0; i < currentNode->size; i++)
                values.push_back(currentNode->values[i]);
            return values;
        }
        else if (this->relation(c, currentNode->key))
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;
    }
    return values;
}

// Deletes a node from the sorted multi map when it has no children
// Time complexity: Theta(1)
void SortedMultiMap::deleteNodeWhenNoChildren(Node *node, Node *parentNode)
{
    if (parentNode == NULL)
        this->root = NULL;
    else if (parentNode->left == node)
        parentNode->left = NULL;
    else
        parentNode->right = NULL;

    delete[] node->values;
    delete node;
}

// Deletes a node from the sorted multi map when it has one child
// Time complexity: Theta(1)
void SortedMultiMap::deleteNodeWhenOneChild(Node *node, Node *parentNode)
{
    if (node->left == NULL)
    {
        if (parentNode == NULL)
            this->root = node->right;
        else if (parentNode->left == node)
            parentNode->left = node->right;
        else
            parentNode->right = node->right;

        delete[] node->values;
        delete node;
        return;
    }

    if (parentNode == NULL)
        this->root = node->left;
    else if (parentNode->left == node)
        parentNode->left = node->left;
    else
        parentNode->right = node->left;

    delete[] node->values;
    delete node;
}

// Deletes a node from the sorted multi-map when it has two children
// Time complexity:
//   - Best case: Theta(1) (when the right subtree of the node has no left child)
//   - Worst case: O(n) (when the right subtree of the node is a skewed tree and we need to traverse the entire height)
//   - Average case: Theta(height of BST) (when the right subtree of the node is balanced)
void SortedMultiMap::deleteNodeWhenTwoChildren(Node *node)
{
    Node *minNode = node->right, *minParentNode = node;

    while (node->left != NULL)
    {
        minParentNode = minNode;
        minNode = minNode->left;
    }

    node->key = minNode->key;
    node->size = minNode->size;
    node->capacity = minNode->capacity;
    delete[] node->values;
    node->values = minNode->values;

    minParentNode->left = NULL;

    this->recursiveDestructor(minNode);
}

// Removes a key-value pair from the sorted multi-map
// Time complexity:
//   - Best case: Theta(1) (when the key-value pair is at the root of the tree)
//   - Worst case: O(n) (when the key-value pair is not found or when the tree is a skewed tree and we need to traverse the entire height)
//   - Average case: Theta(height of BST) (when the tree is balanced)
bool SortedMultiMap::remove(TKey c, TValue v)
{
    Node *currentNode = this->root;
    Node *parentNode = NULL;
    while (currentNode != NULL)
    {
        if (currentNode->key == c)
        {
            for (int i = 0; i < currentNode->size; i++)
                if (currentNode->values[i] == v)
                {
                    for (int j = i; j < currentNode->size - 1; j++)
                        currentNode->values[j] = currentNode->values[j + 1];
                    currentNode->size--;
                    this->sizeOfBST--;
                    if (currentNode->size == 0)
                    {
                        // Case 1: The node has no children
                        if (currentNode->left == NULL && currentNode->right == NULL)
                        {
                            this->deleteNodeWhenNoChildren(currentNode, parentNode);
                            return true;
                        }
                        // Case 2: The node has one child. In this case, the other child will take the place of its parent
                        if (currentNode->left == NULL || currentNode->right == NULL)
                        {
                            this->deleteNodeWhenOneChild(currentNode, parentNode);
                            return true;
                        }
                        // Case 3: The node has two children. In this case, we find the minimum node in the right subtree and replace the current node with it
                        this->deleteNodeWhenTwoChildren(currentNode);
                        return true;
                    }
                    return true;
                }
            return false;
        }
        else if (this->relation(c, currentNode->key))
        {
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
        else
        {
            parentNode = currentNode;
            currentNode = currentNode->right;
        }
    }
    return false;
}

// Returns the size (number of key-value pairs) of the sorted multi map
// Time complexity: Theta(1)
int SortedMultiMap::size() const
{
    return this->sizeOfBST;
}

// Checks whether the sorted multi-map is empty (contains no key-value pairs)
// Time complexity: Theta(1)
bool SortedMultiMap::isEmpty() const
{
    return this->sizeOfBST == 0;
}

// Recursively replaces all values in the sorted multi-map using a transformer function
// Time complexity: Theta(sizeOfBST)
void SortedMultiMap::recursiveReplaceAll(Node *node, Transformer t)
{
    if (node == NULL)
        return;
    for (int i = 0; i < node->size; i++)
        node->values[i] = t(node->key, node->values[i]);
    this->recursiveReplaceAll(node->left, t);
    this->recursiveReplaceAll(node->right, t);
}

// Returns an iterator for the sorted multi-map
// Time complexity: Theta(1)
SMMIterator SortedMultiMap::iterator() const
{
    return SMMIterator(*this);
}

// Recursively destroys the nodes in the sorted multi-map
// Time complexity: Theta(sizeOfBST)
void SortedMultiMap::recursiveDestructor(Node *node)
{
    if (node == NULL)
        return;
    this->recursiveDestructor(node->left);
    this->recursiveDestructor(node->right);
    delete[] node->values;
    delete node;
}

// Destroys the sorted multi map and frees the allocated memory
// Time complexity: Theta(sizeOfBST)
SortedMultiMap::~SortedMultiMap()
{
    this->recursiveDestructor(this->root);
}
