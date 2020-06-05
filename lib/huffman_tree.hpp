#ifndef __HuffmanTree__
#define __HuffmanTree__
#include "priority_queue.hpp"




template<class valueType>
struct node{
        valueType value;
        int frequancy;
        node* left;
        node* right;
    };

template<class valueType>   
class huffman_tree
{
private:
    node<valueType> minheap[10];
    node<valueType> * root;
    node<valueType> * creatNode(valueType value,int frequancy); // using this function to creat a node to insert it to the tree 
    void insert(node<valueType>* root,node<valueType>* leftChild,node<valueType> rightChild); // to insert you need the root and left and right child
public:
    huffman_tree(); // accepts frequancy table(min heap) like this [{'a',2},{'b',5},{'c',12},{'d',20}]
    void buildHuffManTree(min_heap<valueType> * Qu);
     
};

template<class valueType>
huffman_tree <valueType>::huffman_tree() // constructor of the class
{
    root = nullptr;
}

template<class valueType>
node<valueType> * huffman_tree<valueType>::creatNode(valueType value,int frequancy){
    node<valueType> n;
    n.value = value;
    n.frequancy = frequancy;
    n.left = nullptr;
    n.right = nullptr;
    return &n;
}

template<class valueType>
void huffman_tree<valueType>::insert(node<valueType>* sumNode,node<valueType>* leftChild,node<valueType> rightChild){
    root = sumNode;
    root->left = leftChild;
    root->right = rightChild;
}

template<class valueType>
void huffman_tree<valueType>::buildHuffManTree(min_heap<valueType> * Qu){  // [{'a',2},{'b',5},{'c',12},{'d',20},{'e',30},{'f',40}]
    //first extract node from the min heap and make it the left child
    
    // then extrach node from the heap and make it second Child 
    
}


#endif