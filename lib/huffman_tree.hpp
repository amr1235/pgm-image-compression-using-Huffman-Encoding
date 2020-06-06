#ifndef __HuffmanTree__
#define __HuffmanTree__
#include "priority_queue.hpp"
#include <unordered_map>
#include <vector>
#include <string>



template<class valueType>   
class huffman_tree
{
private:
    heapNode<valueType> * Root; 
    void hufmaanEncoding(heapNode<valueType> * root,string str,unordered_map<valueType, string> &huffmanCode);
public:
    huffman_tree();
    void buildHuffManTree(min_heap<valueType> * Qu);
    void encode(unordered_map<valueType, string> &map);  // this function will take root of the tree and return a map with valuse and its binary code as map 
};

template<class valueType>
void huffman_tree<valueType>::buildHuffManTree(min_heap<valueType> * Qu){  // [{'a',2},{'b',5},{'c',12},{'d',20},{'e',30},{'f',40}]

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
    Root = &root;
    
}

template<class valueType>
void huffman_tree<valueType>::hufmaanEncoding(heapNode<valueType> * root,string str,unordered_map<valueType, string> &huffmanCode){
    if(root == nullptr) return;

    if(root->leftChild != nullptr){
        str.push_back('0');
        hufmaanEncoding(root->leftChild, str, huffmanCode);
    }
    if(root->leftChild != nullptr){
        str.push_back('1');
        hufmaanEncoding(root->rightChild, str, huffmanCode);
    }
	
    if (!root->leftChild && !root->rightChild) {
		huffmanCode[root->value] = str;
	}

}

template<class valueType>
void huffman_tree<valueType>::encode(unordered_map<valueType, string> &map){
    hufmaanEncoding(Root,"",map);
}


#endif