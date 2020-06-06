#ifndef __HuffmanTree__
#define __HuffmanTree__
#include "priority_queue.hpp"
#include <map>
#include <vector>
#include <string>
#include <fstream>


template<class valueType>   
class huffman
{
private:
    heapNode<valueType> * Root; 
    void hufmaanEncoding(heapNode<valueType> * root,string str,map<valueType, string> &huffmanCode);
    void decode(heapNode<valueType> * root, int &index, string str);
public:
    huffman();
    void buildHuffManTree(min_heap<valueType> * Qu);
    void creatEncodedFile(string fileName,vector<valueType> Data,min_heap<valueType> * Qu);
    void encode(map<valueType, string> &map);  // this function will take root of the tree and return a map with valuse and its binary code as map 
};

template<class valueType>
void huffman<valueType>::buildHuffManTree(min_heap<valueType> * Qu){  // [{'a',2},{'b',5},{'c',12},{'d',20},{'e',30},{'f',40}]

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
void huffman<valueType>::hufmaanEncoding(heapNode<valueType> * root,string str,map<valueType, string> &huffmanCode){
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
void huffman<valueType>::creatEncodedFile(string fileName,vector<valueType> Data,min_heap<valueType> * Qu){
    buildHuffManTree(Qu);
    map<valueType,string> map ;
    encode(map);
    string totalBits = "";
    for (size_t i = 0; i < Data.size(); i++)
    {
        valueType px = Data[i];
        string bits = map[px];
        totalBits += bits;
    }
    //now we have the encoded bits in string like this "1110110101010111001111000"
    ofstream output(fileName + ".enc", ios::out | ios::binary );
    
}

template<class valueType>
void huffman<valueType>::encode(map<valueType, string> &map){
    hufmaanEncoding(Root,"",map);
}


#endif