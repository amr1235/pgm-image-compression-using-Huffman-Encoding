#ifndef __HuffmanTree__
#define __HuffmanTree__
#include "priority_queue.hpp"


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
    heapNode<valueType> * buildHuffManTree(min_heap<valueType> * Qu);
     
};

template<class valueType>
heapNode<valueType> *  huffman_tree<valueType>::buildHuffManTree(min_heap<valueType> * Qu){  // [{'a',2},{'b',5},{'c',12},{'d',20},{'e',30},{'f',40}]

    while (Qu->size() > 1)
    {
        //first extract node from the min heap and make it the left child
        heapNode<valueType> f = Qu->Extraction();
        // then extrach node from the heap and make it second Child 
        heapNode<valueType> s = Qu->Extraction();
        //creat new node of sum last two nodes 
        heapNode<valueType> sumNode = {
            NULL,
            (f.frequancy + s.frequancy),
            &f,
            &s
        };
        //insert the new node to the heap 
        Qu->Insertion(sumNode);
    }
    
}


#endif