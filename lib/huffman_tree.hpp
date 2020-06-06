#ifndef __HuffmanTree__
#define __HuffmanTree__
#include "priority_queue.hpp"
#include "map"
#include "vector"




template<class valueType>   
class huffman_tree
{
private:
public:
    huffman_tree();
    heapNode<valueType> * buildHuffManTree(min_heap<valueType> * Qu);
    voidhufmaanEncoding(map<valueType,vector<int>> object,heapNode<valueType> * root,vector<int> * array); // this function will take root of the tree and return a map with valuse and its binary code as map 
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
        heapNode<valueType> sumNode ;
        sumNode.frequancy = (f.frequancy + s.frequancy);
        sumNode.value = -1;
        sumNode.leftChild = &f;
        sumNode.rightChild = &s;
        //insert the new node to the heap 
        Qu->Insertion(sumNode);
    }
    heapNode<valueType> * root = &(Qu->Extraction()); 
    return root;
    
}

template<class valueType>
void hufmaanEncoding(map<valueType,vector<int>> object ,heapNode<valueType> * root,vector<int> * array){
    if(root->leftChild != nullptr){
        array->push_back(0);
        hufmaanEncoding(root->leftChild,array);
    }
    if (root->rightChild != nullptr) { 
  
        array->push_back(1); 
        hufmaanEncoding(root->rightChild,array); 
    } 
    if( !(root->leftChild) && !(root->rightChild) ){
        object->insert(pair<valueType,vector<int>>(root->value,array));
    }
}




#endif